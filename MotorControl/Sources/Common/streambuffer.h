/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  streambuffer.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.14;
历史版本:  无;
*********************************************************************************************/
#ifndef __STRAM_BUFFER_H
#define __STRAM_BUFFER_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/
#define FastReserveMemory(BUFFER, STREAMBUFFER, SIZE, BUFFER_TYPE) \
{\
    STREAMBUFFER.reserveMemorySize = SIZE;\
    if (STREAMBUFFER.bufferSize - STREAMBUFFER.tailOffset >= SIZE)\
    {\
        if (STREAMBUFFER.bRewind)\
        {\
            if (STREAMBUFFER.tailOffset + SIZE > STREAMBUFFER.headOffset)\
            {\
                STREAMBUFFER.reserveMemorySize = 0;\
                BUFFER = NULL;\
            }\
            else \
            {\
                BUFFER = (BUFFER_TYPE)(STREAMBUFFER.pBuffer + STREAMBUFFER.tailOffset);\
            }\
        }\
        else \
        {\
            BUFFER = (BUFFER_TYPE)(STREAMBUFFER.pBuffer + STREAMBUFFER.tailOffset);\
        }\
    }\
    else\
    {\
        STREAMBUFFER.tailOffset = 0;\
        STREAMBUFFER.bRewind = true;\
        if (STREAMBUFFER.bNotEmpty)\
        {\
            if (STREAMBUFFER.tailOffset + SIZE > STREAMBUFFER.headOffset)\
            {\
                STREAMBUFFER.reserveMemorySize = 0;\
                BUFFER = NULL;\
            }\
            else\
            {\
                BUFFER = (BUFFER_TYPE)STREAMBUFFER.pBuffer;\
            }\
        }\
        else\
        {\
            BUFFER = (BUFFER_TYPE)STREAMBUFFER.pBuffer;\
        }\
    }\
}

//将数据压入队列，这里只是确认一下长度，数据实际已经进去（先用ReserveMemory，填完数据后调用本函数）
//注意这里的u16Length不能大于ReserveMemory时的nSize
#define FastEnqueue(STREAMBUFFER, LENGTH) \
{ \
    {\
        STREAMBUFFER.tailOffset += LENGTH; \
        if (STREAMBUFFER.dataTailOffset < STREAMBUFFER.tailOffset) \
            STREAMBUFFER.dataTailOffset = STREAMBUFFER.tailOffset; \
        STREAMBUFFER.bNotEmpty = true; \
        STREAMBUFFER.reserveMemorySize = 0; \
    }\
}

//获取最后一包尚未入队数据的头部
#define FastGetTail(BUFFER, STREAMBUFFER, BUFFER_TYPE) \
{ \
    BUFFER = (BUFFER_TYPE)(STREAMBUFFER.pBuffer + STREAMBUFFER.tailOffset); \
}



/***************************************常数和类型声明****************************************/
typedef struct 
{
    bool bNotEmpty    :1;      //指示是否为空
    bool bRewind      :1;      //指示是否回绕
    bool bAlmostFull  :1;      //指示是否快满了
    u8   u8Reverse    :5;      //保留
    u16  bufferSize;
    u16  headOffset;
    u16  tailOffset;
    u16  dataTailOffset;       //有效数据的尾部
    u16  reserveMemorySize;    
    u8   *pBuffer;
    
}StreamBufferStr;


/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void StreamBufferInit(StreamBufferStr *pStreamBuffer, u8* pBuffer, u16 bufferSize);
u8 * GetHead(StreamBufferStr *pStreamBuffer);
void Enqueue(StreamBufferStr *pStreamBuffer, u16 length);
void Dequeue(StreamBufferStr *pStreamBuffer, u16 length);
u8 * ReserveMemory(StreamBufferStr *pStreamBuffer, u16 bufferSize);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/