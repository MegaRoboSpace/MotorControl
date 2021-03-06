/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  intfcparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __INTFC_PARA_VERIFY_H
#define __INTFC_PARA_VERIFY_H



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
u8 UartBaudVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartWordLenVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartFlowCtlVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartParityVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartStopBitVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanSendIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanBaudVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanGroupVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanTargetIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanGroupIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanRadioIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 LinkParaVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/