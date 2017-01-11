/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  intfcparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __INTFC_PARA_VERIFY_H
#define __INTFC_PARA_VERIFY_H



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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/