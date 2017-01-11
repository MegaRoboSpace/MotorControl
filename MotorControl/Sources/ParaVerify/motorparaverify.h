/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motorparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __MOTOR_PARA_VERIFY_H
#define __MOTOR_PARA_VERIFY_H



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
u8 MotorMicroStepsVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorGearRatioVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorStepAngleVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorPeakSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderLineNumVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderChanNumVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/