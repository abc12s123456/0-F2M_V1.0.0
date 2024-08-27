/*
 * F2M
 * Copyright (C) 2024 abc12s123456 382797263@qq.com.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://github.com/abc12s123456/F2M
 *
 */
 
#ifndef _FIFO_H_
#define _FIFO_H_


#ifdef __cplusplus
extern "C"{
#endif


#include "fw_define.h"


typedef struct
{
    u8  *Buffer;                  //缓存
    u32 Block_Num;                //块数量
    u32 Block_Size;               //块大小
//    u32 Data_Length;              //数据长度(存储了有效数据的块数量)
    
    volatile u32 Head_Index;      //FIFO头索引
    volatile u32 Tail_Index;      //FIFO尾索引
    
    u32 Full_Flag : 1;
    u32 Dynamic_Flag : 1;
    
    u32 : 30;
}FIFO_Type;


Bool FIFO_Init(FIFO_Type *fifo, u32 block_num, u32 block_size);

u32  FIFO_Get_BlockSize(FIFO_Type *fifo);
u32  FIFO_Get_BlockNum(FIFO_Type *fifo);
u8   *FIFO_Get_Buffer(FIFO_Type *fifo);

u32  FIFO_Get_BufferSize(FIFO_Type *fifo);
u32  FIFO_Get_DataLength(FIFO_Type *fifo);

u32  FIFO_Write(FIFO_Type *fifo, const void *pdata, u32 num);

u32  FIFO_Read(FIFO_Type *fifo, void *pdata, u32 num);
u32  FIFO_Read_All(FIFO_Type *fifo, void *pdata, u32 cntout);
u32  FIFO_Read_To(FIFO_Type *fifo, const char *s, void *pdata, u32 cntout);
u32  FIFO_Read_Line(FIFO_Type *fifo, void *pdata, u32 cntout);
u32  FIFO_Read_Inter(FIFO_Type *fifo, const char *s1, const char *s2, void *pdata, u32 cntout);
u32  FIFO_Read_Fisrt(FIFO_Type *fifo, const char *s, void *pdata, u32 num);
u32  FIFO_Read_HL(FIFO_Type *fifo, const u8 head, u8 length_site, u8 other_num, void *pdata, u32 cntout);

char *FIFO_Find_String(FIFO_Type *fifo, const char *s);
Bool FIFO_String_IsExist(FIFO_Type *fifo, const char *s, char *tbuffer);

void FIFO_Clear_Buffer(FIFO_Type *fifo);
void FIFO_Fill_Buffer(FIFO_Type *fifo, u8 value);








#ifdef __cplusplus
}
#endif

#endif
