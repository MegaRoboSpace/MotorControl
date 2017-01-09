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
#include "systemcmd.h"
#include "interfacecmd.h"
#include "pvtcmd.h"
#include "motioncmd.h"
#include "calibratecmd.h"
#include "updatecmd.h"
#include "debugcmd.h"
#include "motorcmd.h"
#include "sensorcmd.h"
#include "paraverify.h"
#include "intfcparaverify.h"
#include "protocolstack.h"



/****************************************�ⲿ��������*****************************************/
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



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
            pSendBuffer = (u8 *)malloc(sendLen);
            if (pSendBuffer != NULL)
            {
                pSendBuffer[0] = cmdMainType;
                pSendBuffer[1] = cmdSubType;
                memcpy(pSendBuffer + 2, pData, dataLen);
                CanFrameSend(sendLen, pSendBuffer);
            }
            free(pSendBuffer);
          break;
          
        case LINK_UART:
            pSendBuffer = (u8 *)malloc(sendLen);
            if (pSendBuffer != NULL)
            {
                pSendBuffer[0] = cmdMainType;
                pSendBuffer[1] = cmdSubType;
                memcpy(pSendBuffer + 2, pData, dataLen);
                UartFrameSend(sendLen, pSendBuffer);
            }
            free(pSendBuffer);
          break;

        default:
          break;
    }
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
    u8 subType = pCmdStackFrame->subType;
    

    switch (subType)
    {
        case LINKCMD_CAN:
            g_systemIntfc.linkType = LINK_CAN;
          break;
          
        case LINKCMD_UART: 
            g_systemIntfc.linkType = LINK_UART;
          break;

        default:
          break;
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
    CmdParseFrameRegister(CMD_LINK,       LinkCmdProc);
    CmdParseFrameRegister(CMD_SYSTME,     SystemCmdProc);
    CmdParseFrameRegister(CMD_UART,       UartIntfcCmdProc);
    CmdParseFrameRegister(CMD_CAN,        CanIntfcCmdProc);
    CmdParseFrameRegister(CMD_MOTOR,      MotorCmdProc);
    CmdParseFrameRegister(CMD_ENCODER,    EncoderCmdProc);
    CmdParseFrameRegister(CMD_PVT,        PvtCmdProc);
    CmdParseFrameRegister(CMD_TRAPZCURVE, TrapzCmdProc);
    CmdParseFrameRegister(CMD_MOTION,     MotionCmdProc);
    CmdParseFrameRegister(CMD_OUTOFSTEP,  OutOfStepCmdProc);
    CmdParseFrameRegister(CMD_OTP,        OtpCmdProc);
    CmdParseFrameRegister(CMD_DSENSOR,    DsensorCmdProc);
    CmdParseFrameRegister(CMD_ASENSOR,    AsensorCmdProc);
    CmdParseFrameRegister(CMD_CALIBRATE,  CalibrateCmdProc);
    CmdParseFrameRegister(CMD_UPDATE,     UpdateCmdProc);
    CmdParseFrameRegister(CMD_DEBUG,      DebugCmdProc);

    //ע�����������ģ��Ļص�����
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
}



/*******************************************�ļ�β********************************************/
