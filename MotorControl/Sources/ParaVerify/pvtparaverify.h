/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __PVT_PARA_VERIFY_H
#define __PVT_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "comStruct.h"
#include "errorcode.h"
#include "debug.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/



/***************************************��������������****************************************/



/******************************************��������*******************************************/



/******************************************��������*******************************************/
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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/