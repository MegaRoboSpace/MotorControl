/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  cmdparse.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
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



/****************************************外部变量声明*****************************************/
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: CmdFrameSend;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: LinkCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CmdParseInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CmdParseInit()
{
    //注册命令解析模块回调函数
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

    //注册各个子命令模块的回调函数
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



/*******************************************文件尾********************************************/
