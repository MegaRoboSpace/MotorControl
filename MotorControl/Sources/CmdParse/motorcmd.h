/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motorcmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __MOTOR_CMD_H
#define __MOTOR_CMD_H



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
void MotorMicroStepsSet(u8 cmdDataLen, u8 *pCmdData);
void MotorMicroStepsQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorGearRatioSet(u8 cmdDataLen, u8 *pCmdData);
void MotorGearRatioQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorStepAngleSet(u8 cmdDataLen, u8 *pCmdData);
void MotorStepAngleQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorPeakSpeedSet(u8 cmdDataLen, u8 *pCmdData);
void MotorPeakSpeedQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorTypeSet(u8 cmdDataLen, u8 *pCmdData);
void MotorTypeQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorTempQuery(u8 cmdDataLen, u8 *pCmdData);
void MotorCmdInit(void);
void MotorCmdProc(CmdParseFrameStr *pCmdStackFrame);

void EncoderLineNumSet(u8 cmdDataLen, u8 *pCmdData);
void EncoderLineNumQuery(u8 cmdDataLen, u8 *pCmdData);
void EncoderChanNumSet(u8 cmdDataLen, u8 *pCmdData);
void EncoderChanNumQuery(u8 cmdDataLen, u8 *pCmdData);
void EncoderTypeSet(u8 cmdDataLen, u8 *pCmdData);
void EncoderTypeQuery(u8 cmdDataLen, u8 *pCmdData);
void EncoderCmdInit(void);
void EncoderCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/
