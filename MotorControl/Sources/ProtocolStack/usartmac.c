/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  usartmac.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.16;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "usartmac.h"
#include "usartphy.h"
#include "streambuffer.h"
#include "msgescape.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/
extern StreamBufferStr g_uartRxBuffer;
extern StreamBufferStr g_uartTxBuffer;
extern StreamBufferStr g_CmdParseBuffer;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: UartFrameSend;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartFrameSend(u8 dataLen, u8 *pDataBuffer)
{
    UartPhyFrameStr *pUartPhyFrame = NULL;
    u8 *pPhyFrame;
    u8 xorValue = 0;
    u8 i;


    u8 sendLen = dataLen * 2 + sizeof(UartPhyFrameStr);    //��ֹת�������ռ䣬�������������ݿռ�
    pPhyFrame = ReserveMemory(&g_uartTxBuffer, sendLen);
    if (NULL != pPhyFrame)
    {
        pUartPhyFrame = (UartPhyFrameStr *)pPhyFrame;

        pPhyFrame[0] = USART1_START_OF_FRAME;

        EscapeMsg(pPhyFrame + sizeof(UartPhyFrameStr), pDataBuffer, &dataLen);
        pPhyFrame[1] = dataLen + sizeof(UartPhyFrameStr);
        pPhyFrame[2] = 0;

        //����У��ֵ
        for (i = 0;i < pUartPhyFrame->frameLen;i++)
        {
            xorValue ^= *pPhyFrame++;
        }
        pUartPhyFrame->xorValue = xorValue;
        
        Enqueue(&g_uartTxBuffer, pUartPhyFrame->frameLen);
    }
}

/*********************************************************************************************
�� �� ��: UsartFrameProcess;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UsartFrameProcess()
{
    UartPhyFrameStr *pUartPhyFrame = NULL;
    CmdParseFrameStr *pCmdPareFrame = NULL;
    u8 frameLen;

    
    //���Usart1���ջ����������ݾʹ���
    if (g_uartRxBuffer.bNotEmpty)
    {   
        pUartPhyFrame = (UartPhyFrameStr *)GetHead(&g_uartRxBuffer);
        frameLen = pUartPhyFrame->frameLen;
        if (DeescapeMsgAndXorCheck((u8 *)pUartPhyFrame, &frameLen))    //У�鷴ת�壬���ҷ������ݵ���ʵ����                              
        {
            pCmdPareFrame = (CmdParseFrameStr *)ReserveMemory(&g_CmdParseBuffer,  
                                                               pUartPhyFrame->GET_UART_PHY_FRMAE_PAYLOAD_SIZE);

            if (NULL != pCmdPareFrame)
            {
                pCmdPareFrame->mainType = (CmdTypeEnum)pUartPhyFrame->payload[0];
                pCmdPareFrame->subType = pUartPhyFrame->payload[1];
                pCmdPareFrame->dataLen = frameLen - sizeof(UartPhyFrameStr) - 2;    //CmdParse֡�ĳ��Ȳ����������ͺ������ͣ����Լ�2
                memcpy(pCmdPareFrame->payload, &pUartPhyFrame->payload[2], pCmdPareFrame->dataLen);    //����ʣ�������
                
                Enqueue(&g_CmdParseBuffer, pCmdPareFrame->GET_CMD_PARSE_FRMAE_TOTAL_SIZE);
            }
        }

        //�������ж�    (NICK MARK)
        Dequeue(&g_uartRxBuffer, pUartPhyFrame->frameLen); //������ɺ����
        //�������ж�    (NICK MARK)
    }

    //������ͻ����������ݾͷ���
    if (g_uartTxBuffer.bNotEmpty)
    {
        pUartPhyFrame = (UartPhyFrameStr *)GetHead(&g_uartTxBuffer);

        USARTSend((u8 *)pUartPhyFrame, pUartPhyFrame->frameLen);

        Dequeue(&g_uartTxBuffer, pUartPhyFrame->frameLen); //������ɺ����
    }
}



/*******************************************�ļ�β********************************************/