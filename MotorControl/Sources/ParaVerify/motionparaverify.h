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
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/



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