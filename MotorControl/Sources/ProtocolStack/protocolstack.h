/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  protocolstack.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.16;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __PROTOCOL_STACK_H
#define __PROTOCOL_STACK_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "usartmac.h"
#include "canmac.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/



/***************************************��������������****************************************/
typedef void (*CmdParseFunc)(CmdParseFrameStr *pCmdStackFrame);
typedef void (*SubCmdProFunc)(u8 cmdDataLen, u8 *pCmdData);



/******************************************��������*******************************************/



/******************************************��������*******************************************/
void ProtocolStackInit(void);
void CmdParseFrameRegister(CmdTypeEnum msgType, CmdParseFunc pFunc);
void CmdParseFrameProcess(void);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/