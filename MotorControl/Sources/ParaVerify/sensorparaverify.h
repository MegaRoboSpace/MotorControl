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
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/



/*******************************************宏定义********************************************/ 



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
