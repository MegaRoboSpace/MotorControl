/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  sensorcmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __SENSOR_CMD_H
#define __SENSOR_CMD_H



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
void OtpStateSet(u8 cmdDataLen, u8 *pCmdData);
void OtpStateQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpThresholdSet(u8 cmdDataLen, u8 *pCmdData);
void OtpThresholdQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpResponseSet(u8 cmdDataLen, u8 *pCmdData);
void OtpResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpCmdInit(void);
void OtpCmdProc(CmdParseFrameStr *pCmdStackFrame);

void DsensorStateSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorStateQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorTypeSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorTypeQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorResponseSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorCmdInit(void);
void DsensorCmdProc(CmdParseFrameStr *pCmdStackFrame);

void AsensorStateSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorStateQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorThresholdSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorThresholdQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorResponseSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorCmdInit(void);
void AsensorCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/