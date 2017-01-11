/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  canmac.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.08.22;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "canmac.h"
#include "canphy.h"
#include "softtimer.h"
#include "streambuffer.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/
extern StreamBufferStr g_CmdParseBuffer;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
StreamBufferStr g_canRxBuffer;
StreamBufferStr g_canTxBuffer;
u8  canRxBuffer[480];
u8  canTxBuffer[480];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: CanStreamBufferInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanStreamBufferInit(void)
{
    //CAN phy��Buffer��ʼ��
    StreamBufferInit(&g_canRxBuffer, canRxBuffer, sizeof(canRxBuffer));
    StreamBufferInit(&g_canTxBuffer, canTxBuffer, sizeof(canTxBuffer));  
}


/*********************************************************************************************
�� �� ��: SendCanFrame;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanFrameSend(u8 dataLen, u8 *pDataBuffer)
{
    u8 sendLen = dataLen + sizeof(CanPhyFrameStr);
    CanPhyFrameStr *pCanPhyFrame = NULL;
    

    pCanPhyFrame = (CanPhyFrameStr *)ReserveMemory(&g_canTxBuffer, sendLen);
    if (NULL != pCanPhyFrame)
    {
        pCanPhyFrame->frameLen = sendLen;
        
        if (dataLen > 0)
        {
            memcpy(&pCanPhyFrame->payload, pDataBuffer, dataLen);
        }

        Enqueue(&g_canTxBuffer, pCanPhyFrame->frameLen);
    }
}


/*********************************************************************************************
�� �� ��: CanFrameProcess;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanFrameProcess(void)
{    
    CanPhyFrameStr   *pCanPhyFrame = NULL;
    CmdParseFrameStr *pCmdPareFrame = NULL;
    u8 dataLen;
    u8 canData[8];

    
    //���CAN���ջ����������ݾʹ���
    if (g_canRxBuffer.bNotEmpty)
    {   
        pCanPhyFrame = (CanPhyFrameStr *)GetHead(&g_canRxBuffer);
        dataLen = pCanPhyFrame->GET_CAN_PHY_FRMAE_DATA_SIZE;

        //ֻ��payload�е����ݿ�����������CmdParseBuffer��
        pCmdPareFrame = (CmdParseFrameStr *)ReserveMemory(&g_CmdParseBuffer, dataLen);
        if (NULL != pCmdPareFrame)
        {
            pCmdPareFrame->mainType = (CmdTypeEnum)pCanPhyFrame->payload[0];
            pCmdPareFrame->subType = pCanPhyFrame->payload[1];
            pCmdPareFrame->dataLen = dataLen - 2;    //CmdParse֡�ĳ��Ȳ����������ͺ������ͣ����Լ�2
            memcpy(pCmdPareFrame->payload, &pCanPhyFrame->payload[2], pCmdPareFrame->dataLen);    //����ʣ�������
            Enqueue(&g_CmdParseBuffer, dataLen);
        }
        //=====================================================================================================

        //�������ж�    (NICK MARK)
        Dequeue(&g_canRxBuffer, pCanPhyFrame->frameLen); //������ɺ����
        //�������ж�    (NICK MARK)
    }

    //���������Ҫ����
    if (g_canTxBuffer.bNotEmpty)
    {
        pCanPhyFrame = (CanPhyFrameStr *)GetHead(&g_canTxBuffer);

        //Ŀǰ���������г��ȶ���������8Bytes�ڣ����Բ��÷�֡����ֱ�ӷ�������
        dataLen = pCanPhyFrame->GET_CAN_PHY_FRMAE_DATA_SIZE;
        if (dataLen <= CAN_FRAME_BYTES_MAX)
        {
            memcpy(canData, pCanPhyFrame->payload, dataLen);
            CANSend(pCanPhyFrame->canID, CAN_RTR_DATA, dataLen, canData);
            Delay(0x5FF);    //������ʱ����Ȼ�ڸ������·��ͻᶪ֡
        }

        Dequeue(&g_canTxBuffer, pCanPhyFrame->frameLen);
    }
}



/*******************************************�ļ�β********************************************/