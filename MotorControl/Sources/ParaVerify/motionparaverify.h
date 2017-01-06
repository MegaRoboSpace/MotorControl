/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motionparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __MOTION_PARA_VERIFY_H
#define __MOTION_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    REPORT_OUTNUM = 0,
    REPORT_STEPS,
    REPORT_VELORITY,
    REPORT_TORQUE,
    REPORT_TEMP,
    REPORT_RESERVE
    
}ReportTypeEnum;

typedef struct
{
    u32              outOfSteps;
    ResponseTypeEnum response;
      
}OOStepInfoStruct;

typedef struct
{
    bool bMotion;
    bool bReptEnable[REPORT_RESERVE];    //是否使能上报功能
    u8   temp;             //电机温度
    u32  emergency;
    u32  maxSpeed;
    u32  minSpeed;
    u32  maxPosn;
    u32  minPosn;
    u32  maxTorque;
    u32  minTorque;
    u32  origin;
    u32  reptPeriod;       //上报周期
    u32  outOfSteps;
    u32  steps;
    u32  velority;
    u32  torque;
    OOStepInfoStruct outOfStepInfo;
      
}MotionInfoStruct;



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
u8 MotionEmrgVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMaxSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMinSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMaxPosnVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMinPosnVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMaxTorqueVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionMinTorqueVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionReportVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotionReportperiodVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OutOfStepOutNumVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OutOfStepResponseVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/