/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  systemcmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "systemcmd.h"
#include "systemparaverify.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/
extern SystemInfoStruct g_systemInfo;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pSystemCmdFunc[SYSCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: SystemInfoQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemErrorQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemVersionQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemModeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void SystemModeSet(u8 cmdDataLen, u8 *pCmdData)
{
    WorkModeEnum workMode;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == SystemModeVerify(cmdDataLen, pCmdData, (void *)&workMode))
    {    
        g_systemInfo.workMode = workMode;
    }
}


/*********************************************************************************************
函 数 名: SystemModeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemPoweronSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void SystemPoweronSet(u8 cmdDataLen, u8 *pCmdData)
{
    PowerOnModeEnum powerOn;

    
    //进行参数验证 
    if (PARA_VERIFY_NO_ERROR == SystemPowerOnVerify(cmdDataLen, pCmdData, (void *)&powerOn))
    {    
        g_systemInfo.powerOn = powerOn;
    }
}


/*********************************************************************************************
函 数 名: SystemPoweronQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: SystemCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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



/*******************************************文件尾********************************************/