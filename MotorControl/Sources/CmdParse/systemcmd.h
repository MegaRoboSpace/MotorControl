/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  systemcmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __SYSTEM_CMD_H
#define __SYSTEM_CMD_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
typedef enum
{
    SYSCMD_INFOQ = 0,
    SYSCMD_ERRORQ,
    SYSCMD_VERSIONQ,
    SYSCMD_MODE,
    SYSCMD_MODEQ,
    SYSCMD_POWERON,
    SYSCMD_POWERONQ,
    SYSCMD_RESERVE
    
}SystemCmdSubTypeEnum;



/*******************************************�궨��********************************************/ 



/******************************************��������*******************************************/



/******************************************��������*******************************************/
void SystemInfoQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemErrorQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemVersionQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemModeSet(u8 cmdDataLen, u8 *pCmdData);
void SystemModeQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemPoweronSet(u8 cmdDataLen, u8 *pCmdData);
void SystemPoweronQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemCmdInit(void);
void SystemCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/