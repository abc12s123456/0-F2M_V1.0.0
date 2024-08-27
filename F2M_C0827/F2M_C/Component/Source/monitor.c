#include "monitor.h"


/* 默认的进程监控周期，单位：ms */
#define MONITOR_DEF_PERIOD        100


extern u32  FW_Delay_GetTick(void);
extern void FW_Lock(void);
extern void FW_Unlock(void);


static FW_SList_Type Monitor_List = {NULL};


/**
@功能: 监控标识初始化
@参数: m, 监控对象
@返回: 无
@备注: 无
*/
void Monitor_Init(Monitor_Type *m)
{
    if(m->Period == 0)  m->Period = MONITOR_DEF_PERIOD;
    m->Start_Tick = FW_Delay_GetTick();
    FW_Lock();
    FW_SList_Insert(&Monitor_List, &m->List);
    FW_Unlock();
}
/**/

/**
@功能: 设置监控标识
@参数: m, 监控对象
@返回: 无
@备注: 在被监控的进程中调用
*/
void Monitor_Set(Monitor_Type *m)
{
    FW_Lock();
    m->Start_Tick = FW_Delay_GetTick();
    FW_Unlock();
}
/**/

/**
@功能: 获取被监控进程的监控标识
@参数: m, 监控对象
       period, 被监控进程的运行周期，一般取值稍大一些
@返回: True, 被监控进程运行正常
       False, 被监控进程运行异常
@备注: 一般由高优先级进程监控低优先级进程
*/
static Bool Monitor_Get_Process(Monitor_Type *m, u32 period)
{
    u32 tick;
    
    tick = FW_Delay_GetTick();
    
    if(tick >= m->Start_Tick)
    {
        if((tick - m->Start_Tick) >= period)
        {
            return False;
        }
    }
    else
    {
        if((0xFFFFFFFF - m->Start_Tick + tick) >= period)
        {
            return False;
        }
    }
    
    return True;
}

Bool Monitor_Get(void)
{
    Monitor_Type *m;
    FW_SList_Type *l;
    Bool state;
    
    l = &Monitor_List;
    
    /* 遍历整个链表，任意一个进程异常都返回False */
    while(l != NULL)
    {
        m = Container_Of(l, Monitor_Type, List);
        if(m)
        {
            state = Monitor_Get_Process(m, m->Period);
            if(state != True)  return False;
        }
        l = FW_SList_GetNext(l);
    }
    
    return True;
}
/**/

