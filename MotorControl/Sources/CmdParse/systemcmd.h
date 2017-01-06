/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  systemcmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __SYSTEM_CMD_H
#define __SYSTEM_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
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



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void SystemInfoQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemErrorQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemVersionQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemModeSet(u8 cmdDataLen, u8 *pCmdData);
void SystemModeQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemPoweronSet(u8 cmdDataLen, u8 *pCmdData);
void SystemPoweronQuery(u8 cmdDataLen, u8 *pCmdData);
void SystemCmdInit(void);
void SystemCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/