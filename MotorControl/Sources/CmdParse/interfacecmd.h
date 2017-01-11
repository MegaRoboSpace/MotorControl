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
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/



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