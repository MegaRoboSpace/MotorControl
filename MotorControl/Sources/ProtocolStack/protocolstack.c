/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  protocolstack.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.16;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "protocolstack.h"
#include "streambuffer.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
StreamBufferStr g_canRxBuffer;
StreamBufferStr g_canTxBuffer;
u8  canRxBuffer[480];
u8  canTxBuffer[480];

StreamBufferStr g_uartRxBuffer;
StreamBufferStr g_uartTxBuffer;
u8  uartRxBuffer[1024];
u8  uartTxBuffer[1024];

StreamBufferStr g_CmdParseBuffer;    //�������������
u8  CmdParseBuffer[480];

CmdParseFunc pCmdParseFunc[CMD_RESERVE];      //CANӦ�ò�ص���������



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: ProtocolStackInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void ProtocolStackInit(void)
{
    //CAN phy��Buffer��ʼ��
    StreamBufferInit(&g_canRxBuffer,  canRxBuffer,  sizeof(canRxBuffer));
    StreamBufferInit(&g_canTxBuffer,  canTxBuffer,  sizeof(canTxBuffer));
    
    //Uart phy��Buffer��ʼ��
    StreamBufferInit(&g_uartRxBuffer,  uartRxBuffer,   sizeof(uartRxBuffer));
    StreamBufferInit(&g_uartTxBuffer,  uartTxBuffer,   sizeof(uartTxBuffer));

    //����������Buffer��ʼ��
    memset(pCmdParseFunc, 0, sizeof(pCmdParseFunc));
    StreamBufferInit(&g_CmdParseBuffer, CmdParseBuffer, sizeof(CmdParseBuffer));    
}


/*********************************************************************************************
�� �� ��: CmdParseFrameRegister;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CmdParseFrameRegister(CmdTypeEnum msgType, CmdParseFunc pFunc)
{
    if (msgType < CMD_RESERVE)
    {    
        pCmdParseFunc[msgType] = pFunc;
    }
}


/*********************************************************************************************
�� �� ��: UsartAppFrameProcess;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CmdParseFrameProcess(void)
{
    CmdParseFrameStr *pCmdParseFrame = NULL;


    if (((!g_canRxBuffer.bNotEmpty) && (!g_uartRxBuffer.bNotEmpty) && g_CmdParseBuffer.bNotEmpty) || 
        g_CmdParseBuffer.bAlmostFull)
    {
        pCmdParseFrame = (CmdParseFrameStr *)GetHead(&g_CmdParseBuffer);
        
        if ((pCmdParseFrame->mainType < CMD_RESERVE) && (pCmdParseFunc[pCmdParseFrame->mainType] != NULL))
        {    
            pCmdParseFunc[pCmdParseFrame->mainType](pCmdParseFrame);
        }
        
        Dequeue(&g_CmdParseBuffer, pCmdParseFrame->GET_CMD_PARSE_FRMAE_TOTAL_SIZE);
    }
}



/*******************************************�ļ�β********************************************/