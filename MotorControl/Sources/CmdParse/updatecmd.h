/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  updatecmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __UPDATE_CMD_H
#define __UPDATE_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    UPDATECMD_START = 0,
    UPDATECMD_READY,
    UPDATECMD_TYPE,
    UPDATECMD_DATA,
    UPDATECMD_END,
    UPDATECMD_RESERVE
    
}UpdateCmdSubTypeEnum;



/*******************************************宏定义********************************************/ 



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void UpdateStart(u8 cmdDataLen, u8 *pCmdData);
void UpdateReady(u8 cmdDataLen, u8 *pCmdData);
void UpdateType(u8 cmdDataLen, u8 *pCmdData);
void UpdateData(u8 cmdDataLen, u8 *pCmdData);
void UpdateEnd(u8 cmdDataLen, u8 *pCmdData);
void UpdateCmdInit(void);
void UpdateCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/