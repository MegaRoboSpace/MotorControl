/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  sensorcmd.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __SENSOR_CMD_H
#define __SENSOR_CMD_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
typedef enum
{
    OTPCMD_STATE = 0,
    OTPCMD_STATEQ,
    OTPCMD_THRESHOLD,
    OTPCMD_THRESHOLDQ,
    OTPCMD_RESPONSE,
    OTPCMD_RESPONSEQ,
    OTPCMD_RESERVE
    
}OtpCmdSubTypeEnum;

typedef enum
{
    DSENSORCMD_STATE = 0,
    DSENSORCMD_STATEQ,
    DSENSORCMD_TYPE,
    DSENSORCMD_TYPEQ,
    DSENSORCMD_RESPONSE,
    DSENSORCMD_RESPONSEQ,
    DSENSORCMD_RESERVE
    
}DsensorCmdSubTypeEnum;

typedef enum
{
    ASENSORCMD_STATE = 0,
    ASENSORCMD_STATEQ,
    ASENSORCMD_THRESHOLD,
    ASENSORCMD_THRESHOLDQ,
    ASENSORCMD_RESPONSE,
    ASENSORCMD_RESPONSEQ,
    ASENSORCMD_RESERVE
    
}AsensorCmdSubTypeEnum;



/*******************************************�궨��********************************************/ 



/******************************************��������*******************************************/



/******************************************��������*******************************************/
void OtpStateSet(u8 cmdDataLen, u8 *pCmdData);
void OtpStateQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpThresholdSet(u8 cmdDataLen, u8 *pCmdData);
void OtpThresholdQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpResponseSet(u8 cmdDataLen, u8 *pCmdData);
void OtpResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void OtpCmdInit(void);
void OtpCmdProc(CmdParseFrameStr *pCmdStackFrame);

void DsensorStateSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorStateQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorTypeSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorTypeQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorResponseSet(u8 cmdDataLen, u8 *pCmdData);
void DsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void DsensorCmdInit(void);
void DsensorCmdProc(CmdParseFrameStr *pCmdStackFrame);

void AsensorStateSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorStateQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorThresholdSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorThresholdQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorResponseSet(u8 cmdDataLen, u8 *pCmdData);
void AsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData);
void AsensorCmdInit(void);
void AsensorCmdProc(CmdParseFrameStr *pCmdStackFrame);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/