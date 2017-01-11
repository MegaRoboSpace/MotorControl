/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motioncmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __MOTION_CMD_H
#define __MOTION_CMD_H



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
void MotionRun(u8 cmdDataLen, u8 *pCmdData);
void MotionStop(u8 cmdDataLen, u8 *pCmdData);
void MotionEmergencySet(u8 cmdDataLen, u8 *pCmdData);
void MotionEmergencyQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxSpeedSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxSpeedQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMinSpeedSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMinSpeedQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxPositionSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxPositionQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMinPositionSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMinPositionQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxTorqueSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMaxTorqueQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionMinTorqueSet(u8 cmdDataLen, u8 *pCmdData);
void MotionMinTorqueQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionOriginSet(u8 cmdDataLen, u8 *pCmdData);
void MotionOriginQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionReportSet(u8 cmdDataLen, u8 *pCmdData);
void MotionReportQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionReportPeriodSet(u8 cmdDataLen, u8 *pCmdData);
void MotionReportPeriodQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionOutNumQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionStepsQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionVelorityQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionTorqueQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionTempQuery(u8 cmdDataLen, u8 *pCmdData);
void MotionCmdInit(void);
void MotionCmdProc(CmdParseFrameStr *pCmdStackFrame);

void OutOfStepOutNumSet(u8 cmdDataLen, u8 *pCmdData);
void OutOfStepOutNumQuery(u8 cmdDataLen, u8 *pCmdData);
void OutOfStepResponseSet(u8 cmdDataLen, u8 *pCmdData);
void OutOfStepResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void OutOfStepCmdInit(void);
void OutOfStepCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/