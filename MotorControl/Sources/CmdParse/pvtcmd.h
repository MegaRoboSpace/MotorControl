/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtcmd.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __PVT_CMD_H
#define __PVT_CMD_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    PVTCMD_MODE = 0,
    PVTCMD_MODEQ,
    PVTCMD_POINT,
    PVTCMD_POINTQ,
    PVTCMD_POSN,
    PVTCMD_POSNQ,
    PVTCMD_SPEED,
    PVTCMD_SPEEDQ,
    PVTCMD_TIME,
    PVTCMD_TIMEQ,
    PVTCMD_REMAINPOINTQ,
    PVTCMD_OUTPUTPOINTQ,
    PVTCMD_STARTPOINT,
    PVTCMD_STARTPOINTQ,
    PVTCMD_ENDPOINT,
    PVTCMD_ENDPOINTQ,
    PVTCMD_NCYCLES,
    PVTCMD_NCYCLESQ,
    PVTCMD_WARNPOINT,
    PVTCMD_WARNPOINTQ,
    PVTCMD_CLEAR,
    PVTCMD_WARN,
    PVTCMD_CALCEND,
    PVTCMD_RESERVE
    
}PvtCmdSubTypeEnum;

typedef enum
{
    TRAPZCMD_POINT = 0,
    TRAPZCMD_POINTQ,
    TRAPZCMD_POSN,
    TRAPZCMD_SPEED,
    TRAPZCMD_TIME,
    TRAPZCMD_RESERVE
    
}TrapzCmdSubTypeEnum;



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void PvtModeSet(u8 cmdDataLen, u8 *pCmdData);
void PvtModeQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtPointSet(u8 cmdDataLen, u8 *pCmdData);
void PvtPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtPositionSet(u8 cmdDataLen, u8 *pCmdData);
void PvtPositionQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtSpeedSet(u8 cmdDataLen, u8 *pCmdData);
void PvtSpeedQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtTimeSet(u8 cmdDataLen, u8 *pCmdData);
void PvtTimeQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtStartPointSet(u8 cmdDataLen, u8 *pCmdData);
void PvtStartPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtEndPointSet(u8 cmdDataLen, u8 *pCmdData);
void PvtEndPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtNcyclesSet(u8 cmdDataLen, u8 *pCmdData);
void PvtNcyclesQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtRemainPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtOutputPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtWarnPointSet(u8 cmdDataLen, u8 *pCmdData);
void PvtWarnPointQuery(u8 cmdDataLen, u8 *pCmdData);
void PvtWarn(u8 cmdDataLen, u8 *pCmdData);
void PvtClear(u8 cmdDataLen, u8 *pCmdData);
void PvtCalcEnd(u8 cmdDataLen, u8 *pCmdData);
void PvtCmdInit(void);
void PvtCmdProc(CmdParseFrameStr *pCmdStackFrame);

void TrapzPointSet(u8 cmdDataLen, u8 *pCmdData);
void TrapzPointQuery(u8 cmdDataLen, u8 *pCmdData);
void TrapzPositionSet(u8 cmdDataLen, u8 *pCmdData);
void TrapzSpeedSet(u8 cmdDataLen, u8 *pCmdData);
void TrapzTimeSet(u8 cmdDataLen, u8 *pCmdData);
void TrapzCmdInit(void);
void TrapzCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/