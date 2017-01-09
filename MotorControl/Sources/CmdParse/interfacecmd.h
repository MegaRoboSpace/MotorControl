/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  interfacecmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __INTERFACE_CMD_H
#define __INTERFACE_CMD_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
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



/*******************************************�궨��********************************************/ 



/******************************************��������*******************************************/



/******************************************��������*******************************************/
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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/