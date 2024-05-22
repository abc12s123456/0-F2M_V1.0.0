#ifndef _STIMING_H_
#define _STIMING_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "fw_define.h"


/* 软定时器计时模式 */
typedef enum
{
    STiming_Mode_Period = 0,      //周期模式
    STiming_Mode_Once,            //单次模式
}STiming_Mode_Enum;


/* 定时器状态 */
typedef enum
{
    STiming_State_Oning = 0,
    STiming_State_Finish,
}STiming_State_Enum;


typedef struct
{
    /* 获取软定时器的计时节拍 */
    __WM_ u32  (*Get_Tick)(void);
    
    /* 定时时间到达时执行的回调及其入参 */
    __WS_ void (*CB)(void *);
    __WS_ void *Pdata;
    
    __RO_ u32 Tick0;              //定时起始时刻
    
    __WS_ u32 Mode : 1;           //计时模式
    
    __RO_ u32 Get_Flag : 1;       //起始时刻获取标识
    __RO_ u32 Switch_Flag : 1;    //定时器开关标识
    __RO_ u32 Ignore_Flag : 1;    //定时器忽略标识
    __RO_ u32 Done_Flag : 1;      //定时完成标识
    
    __RE_ u32 RE : 28;
}STiming_Type;


void STiming_DeInit(STiming_Type *t);
void STiming_Init(STiming_Type *t, u32 (*get_tick)(void));
u32  STiming_GetTick(STiming_Type *t);
void STiming_SetCB(STiming_Type *t, void (*cb)(void *), void *pdata);
Bool STiming_Start(STiming_Type *t, u32 timing_time);
void STiming_Reset(STiming_Type *t);
void STiming_Open(STiming_Type *t);
void STiming_Close(STiming_Type *t);
void STiming_Done(STiming_Type *t);


#if __cplusplus
}
#endif

#endif

