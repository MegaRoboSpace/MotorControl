/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motionparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __MOTION_PARA_VERIFY_H
#define __MOTION_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
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
    bool bReptEnable[REPORT_RESERVE];    //�Ƿ�ʹ���ϱ�����
    u8   temp;             //����¶�
    u32  emergency;
    u32  maxSpeed;
    u32  minSpeed;
    u32  maxPosn;
    u32  minPosn;
    u32  maxTorque;
    u32  minTorque;
    u32  origin;
    u32  reptPeriod;       //�ϱ�����
    u32  outOfSteps;
    u32  steps;
    u32  velority;
    u32  torque;
    OOStepInfoStruct outOfStepInfo;
      
}MotionInfoStruct;



/*******************************************�궨��********************************************/ 



/******************************************��������*******************************************/



/******************************************��������*******************************************/
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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/