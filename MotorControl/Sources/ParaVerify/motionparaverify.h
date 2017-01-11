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
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/



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