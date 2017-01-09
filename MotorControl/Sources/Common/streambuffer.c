/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  streambuffer.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.14;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "streambuffer.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: StreamBufferInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void StreamBufferInit(StreamBufferStr *pStreamBuffer, u8* pBuffer, u16 bufferSize)
{
    pStreamBuffer->bufferSize = bufferSize;
    pStreamBuffer->headOffset = 0;
    pStreamBuffer->tailOffset = 0;
    pStreamBuffer->reserveMemorySize = 0;
    pStreamBuffer->bRewind = false;
    pStreamBuffer->pBuffer = pBuffer;
}


/*********************************************************************************************
�� �� ��: GetHead;
ʵ�ֹ���: ��ȡ��һ�����ݵ�ͷ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 *GetHead(StreamBufferStr *pStreamBuffer)
{
    return pStreamBuffer->pBuffer + pStreamBuffer->headOffset;
}


/*********************************************************************************************
�� �� ��: ReserveMemory;
ʵ�ֹ���: ����һ�������ռ���ⲿʹ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 *ReserveMemory(StreamBufferStr *pStreamBuffer, u16 bufferSize)
{
    pStreamBuffer->reserveMemorySize = bufferSize;
    if ( (pStreamBuffer->bufferSize - pStreamBuffer->tailOffset >= bufferSize) )
    {
        if (pStreamBuffer->bRewind)
        {
            if (pStreamBuffer->tailOffset + bufferSize > pStreamBuffer->headOffset)
            {
                pStreamBuffer->reserveMemorySize = 0;
                return NULL;
            }
        }
        return (pStreamBuffer->pBuffer + pStreamBuffer->tailOffset);  
    }
    else //β���ռ��˷�һЩ�������ˣ����������
    {                
        pStreamBuffer->tailOffset = 0;
        pStreamBuffer->bRewind = true;
        if (pStreamBuffer->bNotEmpty)
        {
            if (pStreamBuffer->tailOffset + bufferSize > pStreamBuffer->headOffset)
            {
                pStreamBuffer->reserveMemorySize = 0;
                return NULL;
            }
        }
        return pStreamBuffer->pBuffer;
    }
}


/*********************************************************************************************
�� �� ��: Enqueue;
ʵ�ֹ���: ������ѹ����У�����ֻ��ȷ��һ�³��ȣ�����ʵ���Ѿ���ȥ; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void Enqueue(StreamBufferStr *pStreamBuffer, u16 length)
{   
    if (!pStreamBuffer->bNotEmpty)
    {	
        pStreamBuffer->headOffset = pStreamBuffer->tailOffset;
        pStreamBuffer->dataTailOffset = pStreamBuffer->headOffset;	
    }
    
    pStreamBuffer->tailOffset += length;
  
    if (pStreamBuffer->dataTailOffset < pStreamBuffer->tailOffset)
    {
        pStreamBuffer->dataTailOffset = pStreamBuffer->tailOffset;
    }
    
    pStreamBuffer->bNotEmpty= true;
    pStreamBuffer->reserveMemorySize = 0;

    if (pStreamBuffer->tailOffset >= pStreamBuffer->headOffset)
    {
        if ((pStreamBuffer->tailOffset - pStreamBuffer->headOffset) > (pStreamBuffer->bufferSize >> 1))
        {
            pStreamBuffer->bAlmostFull = true;
        }
        else
        {
            pStreamBuffer->bAlmostFull = false;
        }
    }
    else
    {
        if ((pStreamBuffer->dataTailOffset - pStreamBuffer->headOffset + pStreamBuffer->tailOffset) > (pStreamBuffer->bufferSize >> 1))
        {
            pStreamBuffer->bAlmostFull = true;  
        }
        else
        {
            pStreamBuffer->bAlmostFull = false; 
        }
    }
}


/*********************************************************************************************
�� �� ��: Dequeue;
ʵ�ֹ���: ���ӣ��൱�ڶ���ͷ��ָ�����ȵ�����; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void Dequeue(StreamBufferStr *pStreamBuffer, u16 length)
{   
    if ((pStreamBuffer->headOffset + length) >= pStreamBuffer->dataTailOffset)
    {        
        if (pStreamBuffer->reserveMemorySize > 0)
        {           
            pStreamBuffer->headOffset = pStreamBuffer->tailOffset;            
            pStreamBuffer->dataTailOffset = pStreamBuffer->tailOffset;
            pStreamBuffer->bNotEmpty= false; 
        }
        else
        {
            pStreamBuffer->headOffset = 0;
            if (pStreamBuffer->tailOffset == pStreamBuffer->dataTailOffset)
            {     
                pStreamBuffer->tailOffset = 0;
            }

            pStreamBuffer->dataTailOffset = pStreamBuffer->tailOffset;
            if (pStreamBuffer->tailOffset == 0)
            {    
                pStreamBuffer->bNotEmpty= false;
            }
        }
        
        pStreamBuffer->bRewind= false;
    }
    else
    {  
        pStreamBuffer->headOffset += length;
    }
    
    //���»������������

    if (pStreamBuffer->tailOffset >= pStreamBuffer->headOffset)
    {    
        if ((pStreamBuffer->tailOffset - pStreamBuffer->headOffset) > (pStreamBuffer->bufferSize >> 1))
        {
            pStreamBuffer->bAlmostFull = true;
        }
        else
        {
            pStreamBuffer->bAlmostFull = false;
        }
    }
    else
    {    
        if ((pStreamBuffer->dataTailOffset - pStreamBuffer->headOffset + pStreamBuffer->tailOffset) > (pStreamBuffer->bufferSize >> 1))
        {
            pStreamBuffer->bAlmostFull = true;
        }
        else
        {
            pStreamBuffer->bAlmostFull = false;
        }
    }
}



/*******************************************�ļ�β********************************************/
