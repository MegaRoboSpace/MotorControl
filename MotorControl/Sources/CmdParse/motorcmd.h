/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motorcmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __MOTOR_CMD_H
#define __MOTOR_CMD_H



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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/
