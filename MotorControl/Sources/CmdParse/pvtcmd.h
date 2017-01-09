/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtcmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __PVT_CMD_H
#define __PVT_CMD_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/



/***************************************��������������****************************************/
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



/******************************************��������*******************************************/



/******************************************��������*******************************************/
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



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/