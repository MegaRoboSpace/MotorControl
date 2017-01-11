/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __PVT_PARA_VERIFY_H
#define __PVT_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/



/***************************************常数和类型声明****************************************/



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
u8 PvtModeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtPositionVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtTimeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtStartPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtEndPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtNcyclesVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtWarnPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzPositionVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzTimeVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/