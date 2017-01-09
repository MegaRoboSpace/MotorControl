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
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
typedef enum
{
    DTYPE_RISE = 0,
    DTYPE_FALL,
    DTYPE_HIGH,
    DTYPE_LOW
    
}TriggerTypeEnum;

typedef struct
{
    bool             bEnable;
    u8               threshold;
    ResponseTypeEnum response;
    
}OtpInfoStruct;

typedef struct
{
    bool             bEnable;
    TriggerTypeEnum  triggerType;
    ResponseTypeEnum response;
    
}DsensorInfoStruct;

typedef struct
{
    bool             bEnable;
    f32              threshold;
    ResponseTypeEnum response;
    
}AsensorInfoStruct;



/*******************************************�궨��********************************************/ 
#define    DIGIT_SENSOR_NUM     10
#define    ANALOG_SENSOR_NUM    10



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
