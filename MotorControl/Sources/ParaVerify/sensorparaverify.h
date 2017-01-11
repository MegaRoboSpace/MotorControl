/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  sensorparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __SENSOR_PARA_VERIFY_H
#define __SENSOR_PARA_VERIFY_H



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
u8 OtpStateVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OtpThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OtpResponseVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 DsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 DsensorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 DsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/
