/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  systemcmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "systemcmd.h"
#include "systemparaverify.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/
extern SystemInfoStruct g_systemInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pSystemCmdFunc[SYSCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: SystemInfoQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemInfoQuery(u8 cmdDataLen, u8 *pCmdData)
{
    /*CmdTypeEnum cmdMainType;
    SystemCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_SYSTME;
    cmdSubType = SYSCMD_INFOQ;
    dataLen = sizeof(g_systemInfo.systemInfo);
    pData = (u8 *)&g_systemInfo.systemInfo;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);*/
}


/*********************************************************************************************
�� �� ��: SystemErrorQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemErrorQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    SystemCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_SYSTME;
    cmdSubType = SYSCMD_ERRORQ;
    dataLen = sizeof(g_systemInfo.errorCode);
    pData = g_systemInfo.errorCode;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: SystemVersionQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemVersionQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    SystemCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_SYSTME;
    cmdSubType = SYSCMD_VERSIONQ;
    dataLen = sizeof(g_systemInfo.version.software);
    pData = g_systemInfo.version.software;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: SystemModeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemModeSet(u8 cmdDataLen, u8 *pCmdData)
{
    WorkModeEnum workMode;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == SystemModeVerify(cmdDataLen, pCmdData, (void *)&workMode))
    {    
        g_systemInfo.workMode = workMode;
    }
}


/*********************************************************************************************
�� �� ��: SystemModeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemModeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    SystemCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_SYSTME;
    cmdSubType = SYSCMD_MODEQ;
    dataLen = sizeof(g_systemInfo.workMode);
    pData = (u8 *)&g_systemInfo.workMode;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: SystemPoweronSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemPoweronSet(u8 cmdDataLen, u8 *pCmdData)
{
    PowerOnModeEnum powerOn;

    
    //���в�����֤ 
    if (PARA_VERIFY_NO_ERROR == SystemPowerOnVerify(cmdDataLen, pCmdData, (void *)&powerOn))
    {    
        g_systemInfo.powerOn = powerOn;
    }
}


/*********************************************************************************************
�� �� ��: SystemPoweronQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemPoweronQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    SystemCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_SYSTME;
    cmdSubType = SYSCMD_POWERONQ;
    dataLen = sizeof(g_systemInfo.powerOn);
    pData = (u8 *)&g_systemInfo.powerOn;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: SystemCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemCmdInit(void)
{
    memset(pSystemCmdFunc, 0, sizeof(pSystemCmdFunc));

    pSystemCmdFunc[SYSCMD_INFOQ]    = SystemInfoQuery;
    pSystemCmdFunc[SYSCMD_ERRORQ]   = SystemErrorQuery;
    pSystemCmdFunc[SYSCMD_VERSIONQ] = SystemVersionQuery;
    pSystemCmdFunc[SYSCMD_MODE]     = SystemModeSet;
    pSystemCmdFunc[SYSCMD_MODEQ]    = SystemModeQuery;
    pSystemCmdFunc[SYSCMD_POWERON]  = SystemPoweronSet;
    pSystemCmdFunc[SYSCMD_POWERONQ] = SystemPoweronQuery;
}

            
/*********************************************************************************************
�� �� ��: SystemCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < SYSCMD_RESERVE) && (pSystemCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pSystemCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************�ļ�β********************************************/