/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  interfacecmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __INTERFACE_CMD_H
#define __INTERFACE_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    UARTCMD_BAUD = 0,
    UARTCMD_BAUDQ,
    UARTCMD_WORDLEN,
    UARTCMD_WORDLENQ,
    UARTCMD_FLOWCTL,
    UARTCMD_FLOWCTLQ,
    UARTCMD_PARITY,
    UARTCMD_PARITYQ,
    UARTCMD_STOPBIT,
    UARTCMD_STOPBITQ,
    UARTCMD_RESERVE
    
}UartCmdSubTypeEnum;

typedef enum
{
    CANCMD_TYPE = 0,
    CANCMD_TYPEQ,
    CANCMD_SENDID,
    CANCMD_SENDIDQ,
    CANCMD_BAUD,
    CANCMD_BAUDQ,
    CANCMD_GROUP,
    CANCMD_GROUPQ,
    CANCMD_TARGETID,
    CANCMD_TARGETIDQ,
    CANCMD_GROUPID,
    CANCMD_GROUPIDQ,
    CANCMD_RADIOID,
    CANCMD_RADIOIDQ,
    CANCMD_RESERVE
    
}CanCmdSubTypeEnum;



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void UartBaudSet(u8 cmdDataLen, u8 *pCmdData);
void UartBaudQuery(u8 cmdDataLen, u8 *pCmdData);
void UartWordLenSet(u8 cmdDataLen, u8 *pCmdData);
void UartWordLenQuery(u8 cmdDataLen, u8 *pCmdData);
void UartFlowCtlSet(u8 cmdDataLen, u8 *pCmdData);
void UartFlowCtlQuery(u8 cmdDataLen, u8 *pCmdData);
void UartParitySet(u8 cmdDataLen, u8 *pCmdData);
void UartParityQuery(u8 cmdDataLen, u8 *pCmdData);
void UartStopBitSet(u8 cmdDataLen, u8 *pCmdData);
void UartStopBitQuery(u8 cmdDataLen, u8 *pCmdData);
void UartApplyPara(u8 cmdDataLen, u8 *pCmdData);
void UartIntfcCmdInit(void);
void UartIntfcCmdProc(CmdParseFrameStr *pCmdStackFrame);

void CanTypeSet(u8 cmdDataLen, u8 *pCmdData);
void CanTypeQuery(u8 cmdDataLen, u8 *pCmdData);
void CanSendIdSet(u8 cmdDataLen, u8 *pCmdData);
void CanSendIdQuery(u8 cmdDataLen, u8 *pCmdData);
void CanBaudSet(u8 cmdDataLen, u8 *pCmdData);
void CanBaudQuery(u8 cmdDataLen, u8 *pCmdData);
void CanGroupSet(u8 cmdDataLen, u8 *pCmdData);
void CanGroupQuery(u8 cmdDataLen, u8 *pCmdData);
void CanTargetIdSet(u8 cmdDataLen, u8 *pCmdData);
void CanTargetIdQuery(u8 cmdDataLen, u8 *pCmdData);
void CanGroupIdSet(u8 cmdDataLen, u8 *pCmdData);
void CanGroupIdQuery(u8 cmdDataLen, u8 *pCmdData);
void CanRadioIdSet(u8 cmdDataLen, u8 *pCmdData);
void CanRadioIdQuery(u8 cmdDataLen, u8 *pCmdData);
void CanApplyPara(u8 cmdDataLen, u8 *pCmdData);
void CanIntfcCmdInit(void);
void CanIntfcCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/