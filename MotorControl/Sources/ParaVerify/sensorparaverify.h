/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  sensorparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __SENSOR_PARA_VERIFY_H
#define __SENSOR_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
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



/*******************************************宏定义********************************************/ 
#define    DIGIT_SENSOR_NUM     10
#define    ANALOG_SENSOR_NUM    10



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
u8 OtpStateVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OtpThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 OtpResponseVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 DsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 DsensorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 DsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);
u8 AsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/
