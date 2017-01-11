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



/****************************************外部变量声明*****************************************/
extern StreamBufferStr   g_canRxBuffer;
extern StreamBufferStr   g_uartRxBuffer;
extern SystemIntfcStruct g_systemIntfc;
extern SystemInfoStruct  g_systemInfo;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
StreamBufferStr g_CmdParseBuffer;    //命令解析缓冲区
u8  CmdParseBuffer[480];

CmdParseFunc  pCmdParseFunc[CMD_RESERVE];      //CAN应用层回调函数数组
SubCmdProFunc pLinkCmdFunc[LINKCMD_RESERVE];



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
函 数 名: LinkIntfcSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void LinkIntfcSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 subType;
    

    if (sizeof(LinkTypeEnum) == cmdDataLen)    //长度先要正确
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
函 数 名: LinkIntfcQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: LinkCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void LinkCmdInit(void)
{
    memset(pLinkCmdFunc, 0, sizeof(pLinkCmdFunc));

    pLinkCmdFunc[LINKCMD_INTFC]  = LinkIntfcSet;
    pLinkCmdFunc[LINKCMD_INTFCQ] = LinkIntfcQuery;
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
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < LINKCMD_RESERVE) && (pLinkCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pLinkCmdFunc[pCmdStackFrame->subType](dataLen, pData);
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

    //注册各个子命令模块的回调函数
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

    //初始化命令解析Buffer
    StreamBufferInit(&g_CmdParseBuffer, CmdParseBuffer, sizeof(CmdParseBuffer));  
}


/*********************************************************************************************
函 数 名: CmdParseFrameProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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



/*******************************************文件尾********************************************/
