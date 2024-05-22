#ifndef _MM_H_
#define _MM_H_

#ifdef __cplusplus
extern "C"{
#endif


#include "fw_define.h"


//内存池管理块
typedef struct MM_ListNodeBCT_Struct
{
    __RO_ struct MM_ListNodeBCT_Struct *Next;    //指向下一个管理块的指针
    __RO_ u32 Block_Size : 31;                   //管理的内存大小
    __RO_ u32 State : 1;                         //管理的内存状态，0：未使用；1：已使用
}MM_List_Type, MM_Node_Type, MM_BCT_Type;


//内存池
typedef struct MM_PoolNode_Struct
{
    __WM_ u32 Base;                              //内存池起始地址
    __WM_ u32 Size;                              //内存池大小
    
    __RO_ MM_List_Type **IdleList_Table;         //空闲节点链表的管理Table
    __RO_ u32 IdleList_Table_Length : 8;
    
    __RO_ u32 Init_Flag : 1;
    __RO_ u32 Lock_Flag : 1;
    
    /* 非固定申请标志，False：只申请不释放；True：申请+释放，并且无法再恢复False
       反映到具体操作上就是MM_Cut()在系统初始上电时可以执行，MM_Malloc()执行以后
       MM_Cut()将失效；并且MM_Cut()申请的内存无法进行管理 */
    __RO_ u32 Unfix_Flag : 1;

    __WS_ u32 Sleep_Time : 21;
    __WS_ void (*Sleep)(u32 time);
    
    __RO_ struct MM_PoolNode_Struct *Next;
}MM_Type, MM_Pool_Type;


void MM_Pool_Init(MM_Pool_Type *Pool);
void *MM_Pool_Cut(MM_Pool_Type *Pool, u32 size);
void *MM_Pool_Malloc(MM_Pool_Type *Pool, u32 size);
void MM_Pool_Free(void *p);

void MM_Pool_Release(MM_Pool_Type *Pool);
void MM_Pool_Dispose(MM_Pool_Type *Pool);

Bool MM_Remap(MM_Pool_Type *Pool);

void MM_Init(u32 size);
void *MM_Cut(u32 size);
void *MM_Malloc(u32 size);
void MM_Free(void *p);


#ifdef __cplusplus
}
#endif

#endif

