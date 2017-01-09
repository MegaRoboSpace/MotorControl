/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  paraverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __PARA_VERIFY_H
#define __PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
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



/*******************************************�궨��********************************************/ 
#define    PARA_VERIFY_NO_ERROR            0
#define    PARA_VERIFY_ERROR_TYPE          1
#define    PARA_VERIFY_ERROR_LEN           2
#define    PARA_VERIFY_ERROR_INDEX         3
#define    PARA_VERIFY_LESS_LOWER_LIMIT    4
#define    PARA_VERIFY_GREAT_UPER_LIMIT    5



/******************************************��������*******************************************/



/******************************************��������*******************************************/
void ParaLimitInit(void);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/
