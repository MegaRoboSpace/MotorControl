/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  paraverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __PARA_VERIFY_H
#define __PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    RESPONSE_NONE = 0,
    RESPONSE_ALARM,
    RESPONSE_STOP,
    RESPONSE_ALARMSTOP,
    RESPONSE_RUN
    
}ResponseTypeEnum;

typedef struct
{
    s16 otpThr;
    s16 canGroup;
    s32 canSendId;
    s32 canTargetId;
    s32 canGroupId;    
    s32 canRadioId;

    s32 pvtStartPoint;
    s32 pvtEndPoint;
    s32 pvtNcycles;
    s32 pvtWarnPoint;
    
    s16 motorGearRatio;
    s32 motorPeakSpeed;
    
    f32 pvtPosn;
    f32 pvtSpeed;
    f32 pvtTime;
    f32 trapzPosn;
    f32 trapzSpeed;
    f32 trapzTime;

    s32 motionEmgc;
    
    s32 motionMaxSpeed;
    s32 motionMaxPosn;
    s32 motionMaxTorque;

    s32 encoderLineNum;

    s32 outOfStepNum;
    
    f32 asensorThr;
    
}UpLimitStruct;

typedef struct
{
    s16 otpThr;
    s16 canGroup;
    s32 canSendId;
    s32 canTargetId;
    s32 canGroupId;    
    s32 canRadioId;

    s32 pvtStartPoint;
    s32 pvtEndPoint;
    s32 pvtNcycles;
    s32 pvtWarnPoint;
    
    s16 motorGearRatio;
    s32 motorPeakSpeed;
    
    f32 pvtPosn;
    f32 pvtSpeed;
    f32 pvtTime;
    f32 trapzPosn;
    f32 trapzSpeed;
    f32 trapzTime;

    s32 motionEmgc;
    
    s32 motionMinSpeed;
    s32 motionMinPosn;
    s32 motionMinTorque;

    s32 encoderLineNum;

    s32 outOfStepNum;
    
    f32 asensorThr;
    
}DownLimitStruct;


typedef struct
{
    UpLimitStruct   upLimit;
    DownLimitStruct downLimit;
    
}ParaLimitStruct;



/*******************************************宏定义********************************************/ 
#define    PARA_VERIFY_NO_ERROR            0
#define    PARA_VERIFY_ERROR_TYPE          1
#define    PARA_VERIFY_ERROR_LEN           2
#define    PARA_VERIFY_ERROR_INDEX         3
#define    PARA_VERIFY_LESS_LOWER_LIMIT    4
#define    PARA_VERIFY_GREAT_UPER_LIMIT    5



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void ParaLimitInit(void);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/
