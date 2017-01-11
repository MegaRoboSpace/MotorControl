/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  sensorcmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __SENSOR_CMD_H
#define __SENSOR_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
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



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/