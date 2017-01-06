/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motioncmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __MOTION_CMD_H
#define __MOTION_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    MOTIONCMD_RUN = 0,
    MOTIONCMD_STOP,
    MOTIONCMD_EMRG,
    MOTIONCMD_EMRGQ,
    MOTIONCMD_MAXSPEED,
    MOTIONCMD_MAXSPEEDQ,
    MOTIONCMD_MINSPEED,
    MOTIONCMD_MINSPEEDQ,
    MOTIONCMD_MAXPOSN,
    MOTIONCMD_MAXPOSNQ,
    MOTIONCMD_MINPOSN,
    MOTIONCMD_MINPOSNQ,
    MOTIONCMD_MAXTORQUE,
    MOTIONCMD_MAXTORQUEQ,
    MOTIONCMD_MINTORQUE,
    MOTIONCMD_MINTORQUEQ,
    MOTIONCMD_ORIGIN,
    MOTIONCMD_ORIGINQ,
    MOTIONCMD_REPORT,
    MOTIONCMD_REPORTQ,
    MOTIONCMD_RPPERIOD,
    MOTIONCMD_RPPERIODQ,
    MOTIONCMD_OOSTEPSQ,      //Out Of Steps Query
    MOTIONCMD_STEPSQ,
    MOTIONCMD_VELORITYQ,
    MOTIONCMD_TORQUEQ,
    MOTIONCMD_TEMPQ,
    MOTIONCMD_RESERVE
    
    
}MotionCmdSubTypeEnum;

typedef enum
{
    OOSCMD_OUTNUM = 0,
    OOSCMD_OUTNUMQ,
    OOSCMD_RESPONSE,
    OOSCMD_RESPONSEQ,
    OOSCMD_RESERVE
    
}OOStepCmdSubTypeEnum;



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
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



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/