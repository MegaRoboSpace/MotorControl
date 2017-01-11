/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  cmdparse.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "cmdparse.h"
#include "canmac.h"
#include "usartmac.h"
#include "streambuffer.h"
#include "systemcmd.h"
#include "interfacecmd.h"
#include "pvtcmd.h"
#include "motioncmd.h"
#include "calibratecmd.h"
#include "updatecmd.h"
#include "debugcmd.h"
#include "motorcmd.h"
#include "sensorcmd.h"



/****************************************�ⲿ��������*****************************************/
extern StreamBufferStr   g_canRxBuffer;
extern StreamBufferStr   g_uartRxBuffer;
extern SystemIntfcStruct g_systemIntfc;
extern SystemInfoStruct  g_systemInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
StreamBufferStr g_CmdParseBuffer;    //�������������
u8  CmdParseBuffer[480];

CmdParseFunc  pCmdParseFunc[CMD_RESERVE];      //CANӦ�ò�ص���������
SubCmdProFunc pLinkCmdFunc[LINKCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: CmdFrameSend;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CmdFrameSend(CmdTypeEnum cmdMainType, u8 cmdSubType, u8 dataLen, u8 *pData)
{
    u8 sendLen = dataLen + sizeof(CmdTypeEnum) + sizeof(cmdSubType);
    u8 *pSendBuffer;
    
    switch (g_systemIntfc.linkType)
    {
        case LINK_CAN:
            if (sendLen <= UART_FRAME_BYTES_BFESCAPE_MAX)
            {
                pSendBuffer = (u8 *)malloc(sendLen);
                if (pSendBuffer != NULL)
                {
                    pSendBuffer[0] = cmdMainType;
                    pSendBuffer[1] = cmdSubType;
                    memcpy(pSendBuffer + 2, pData, dataLen);
                    CanFrameSend(sendLen, pSendBuffer);
                }
                free(pSendBuffer);
            }
          break;
          
        case LINK_UART:
            if (sendLen <= CAN_FRAME_BYTES_MAX)
            {
                pSendBuffer = (u8 *)malloc(sendLen);
                if (pSendBuffer != NULL)
                {
                    pSendBuffer[0] = cmdMainType;
                    pSendBuffer[1] = cmdSubType;
                    memcpy(pSendBuffer + 2, pData, dataLen);
                    UartFrameSend(sendLen, pSendBuffer);
                }
                free(pSendBuffer);
            }
          break;

        default:
          break;
    }
}


/*********************************************************************************************
�� �� ��: LinkIntfcSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void LinkIntfcSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 subType;
    

    if (sizeof(LinkTypeEnum) == cmdDataLen)    //������Ҫ��ȷ
    {
        subType = *pCmdData;    
        switch (subType)
        {
            case 0:
                g_systemIntfc.linkType = LINK_CAN;
              break;
              
            case 1: 
                g_systemIntfc.linkType = LINK_UART;
              break;

            default:
                g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = PARA_VERIFY_ERROR_TYPE;
              break;
        }
    }
}


/*********************************************************************************************
�� �� ��: LinkIntfcQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void LinkIntfcQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    LinkCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_LINK;
    cmdSubType = LINKCMD_INTFCQ;
    dataLen = sizeof(g_systemIntfc.linkType);
    pData = (u8 *)&g_systemIntfc.linkType;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: LinkCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void LinkCmdInit(void)
{
    memset(pLinkCmdFunc, 0, sizeof(pLinkCmdFunc));

    pLinkCmdFunc[LINKCMD_INTFC]  = LinkIntfcSet;
    pLinkCmdFunc[LINKCMD_INTFCQ] = LinkIntfcQuery;
}


/*********************************************************************************************
�� �� ��: LinkCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void LinkCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < LINKCMD_RESERVE) && (pLinkCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pLinkCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: CmdParseInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CmdParseInit()
{
    //ע���������ģ��ص�����
    memset(pCmdParseFunc, 0, sizeof(pCmdParseFunc));
    pCmdParseFunc[CMD_LINK]       = LinkCmdProc;
    pCmdParseFunc[CMD_SYSTME]     = SystemCmdProc;
    pCmdParseFunc[CMD_UART]       = UartIntfcCmdProc;
    pCmdParseFunc[CMD_CAN]        = CanIntfcCmdProc;
    pCmdParseFunc[CMD_MOTOR]      = MotorCmdProc;
    pCmdParseFunc[CMD_ENCODER]    = EncoderCmdProc;
    pCmdParseFunc[CMD_PVT]        = PvtCmdProc;
    pCmdParseFunc[CMD_TRAPZCURVE] = TrapzCmdProc;
    pCmdParseFunc[CMD_MOTION]     = MotionCmdProc;
    pCmdParseFunc[CMD_OUTOFSTEP]  = OutOfStepCmdProc;
    pCmdParseFunc[CMD_OTP]        = OtpCmdProc;
    pCmdParseFunc[CMD_DSENSOR]    = DsensorCmdProc;
    pCmdParseFunc[CMD_ASENSOR]    = AsensorCmdProc;
    pCmdParseFunc[CMD_CALIBRATE]  = CalibrateCmdProc;
    pCmdParseFunc[CMD_UPDATE]     = UpdateCmdProc;
    pCmdParseFunc[CMD_DEBUG]      = DebugCmdProc;

    //ע�����������ģ��Ļص�����
    LinkCmdInit();
    SystemCmdInit();
    UartIntfcCmdInit();
    CanIntfcCmdInit();
    MotorCmdInit();
    EncoderCmdInit();
    PvtCmdInit();
    TrapzCmdInit();
    MotionCmdInit();
    OutOfStepCmdInit();
    OtpCmdInit();
    DsensorCmdInit();
    AsensorCmdInit();
    CalibrateCmdInit();
    UpdateCmdInit();
    DebugCmdInit();

    //��ʼ���������Buffer
    StreamBufferInit(&g_CmdParseBuffer, CmdParseBuffer, sizeof(CmdParseBuffer));  
}


/*********************************************************************************************
�� �� ��: CmdParseFrameProcess;
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
