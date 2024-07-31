#ifndef _QENCODER_H_
#define _QENCODER_H_

#ifdef __cplusplus
extern "C"{
#endif


#include "fw_device.h"


#define QENCODER_DRV_IO_NUM       0x00      //IO驱动
#define QENCODER_DRV_TIM_NUM      0x01      //Timer驱动


/* 编码器类型 */
typedef enum
{
    QEncoder_2P1P = 0,                      //2定位1脉冲
    QEncoder_1P1P = 1,                      //1定位1脉冲
}QEncoder_Enum;


/* 编码器工作方式 */
typedef enum
{
    QEncoder_Mode_Direct = 0,               //方向式(增量式)
    QEncoder_Mode_Position = 1,             //位置式
}QEncoder_Mode_Enum;


typedef struct
{
    u32 Pin_A : 16;
    u32 Pin_B : 16;
    
    /* 使用timer驱动时的通道 */
    u32 CH_A : 8;
    u32 CH_B : 8;
    
    /* 触发电平 */
    u32 VL_A : 1;
    u32 VL_B : 1;
    
    /* 编码器类型，参照QEncoder_Enum */
    u32 Type : 1;
    
    /* 编码器工作模式，参照QEncoder_Mode_Enum */
    u32 Mode : 1;
    
    /* 计数的最小值、最大值 */
    u32 Min : 12;
    u32 Max;
    
    /* 中断服务回调函数 */
    void (*IH_CB)(void *);
    void *IH_Pdata;
}QEncoder_Config_Type;


typedef struct
{
    __RO_ FW_Device_Type Device;

    QEncoder_Config_Type Config;

    /* 计数 */
    u32 Counter;
    
    /* IO驱动时的编码状态 */
    u32 State : 8;
    
    /*  */
    u32 Filter_Cnt : 8;
    
    u32 : 16;
    
    __RO_ u32 CValue;
    __RO_ u32 PValue;
    
    __RO_ u32 BK_Value;
}QEncoder_Type;


typedef struct
{
    void (*Init)(QEncoder_Type *dev);
    u32  (*Get_Counter)(QEncoder_Type *dev);
    s32  (*Get_Direct)(QEncoder_Type *dev);
    
    void (*IH_CB)(void *);
    void *IH_Pdata;
}QEncoder_Driver_Type;


void QEncoder_Init(QEncoder_Type *dev);
s32  QEncoder_Get(QEncoder_Type *dev);


#ifdef __cplusplus
}
#endif

#endif
