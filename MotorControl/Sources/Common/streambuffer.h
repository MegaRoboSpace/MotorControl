/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  streambuffer.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.14;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __STRAM_BUFFER_H
#define __STRAM_BUFFER_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/
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

//������ѹ����У�����ֻ��ȷ��һ�³��ȣ�����ʵ���Ѿ���ȥ������ReserveMemory���������ݺ���ñ�������
//ע�������u16Length���ܴ���ReserveMemoryʱ��nSize
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

//��ȡ���һ����δ������ݵ�ͷ��
#define FastGetTail(BUFFER, STREAMBUFFER, BUFFER_TYPE) \
{ \
    BUFFER = (BUFFER_TYPE)(STREAMBUFFER.pBuffer + STREAMBUFFER.tailOffset); \
}



/***************************************��������������****************************************/
typedef struct 
{
    bool bNotEmpty    :1;      //ָʾ�Ƿ�Ϊ��
    bool bRewind      :1;      //ָʾ�Ƿ����
    bool bAlmostFull  :1;      //ָʾ�Ƿ������
    u8   u8Reverse    :5;      //����
    u16  bufferSize;
    u16  headOffset;
    u16  tailOffset;
    u16  dataTailOffset;       //��Ч���ݵ�β��
    u16  reserveMemorySize;    
    u8   *pBuffer;
    
}StreamBufferStr;


/******************************************��������*******************************************/



/******************************************��������*******************************************/
void StreamBufferInit(StreamBufferStr *pStreamBuffer, u8* pBuffer, u16 bufferSize);
u8 * GetHead(StreamBufferStr *pStreamBuffer);
void Enqueue(StreamBufferStr *pStreamBuffer, u16 length);
void Dequeue(StreamBufferStr *pStreamBuffer, u16 length);
u8 * ReserveMemory(StreamBufferStr *pStreamBuffer, u16 bufferSize);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/