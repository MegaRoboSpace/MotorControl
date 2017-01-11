/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  sensorcmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "sensorcmd.h"
#include "sensorparaverify.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/
extern OtpInfoStruct     g_otpInfo;
extern DsensorInfoStruct g_dsensorInfo[DIGIT_SENSOR_NUM];
extern AsensorInfoStruct g_asensorInfo[ANALOG_SENSOR_NUM];



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pOtpCmdFunc[OTPCMD_RESERVE];
SubCmdProFunc pDsensorCmdFunc[DSENSORCMD_RESERVE];
SubCmdProFunc pAsensorCmdFunc[ASENSORCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: OtpStateSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == OtpStateVerify(cmdDataLen, pCmdData, (void *)&bEnable))
    {
        g_otpInfo.bEnable = bEnable;
    }
}


/*********************************************************************************************
函 数 名: OtpStateQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpStateQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    OtpCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_OTP;
    cmdSubType = OTPCMD_STATEQ;
    dataLen = sizeof(g_otpInfo.bEnable);
    pData = &g_otpInfo.bEnable;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: OtpThresholdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpThresholdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 threshold;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == OtpThresholdVerify(cmdDataLen, pCmdData, (void *)&threshold))
    {
        g_otpInfo.threshold = threshold;
    }
}


/*********************************************************************************************
函 数 名: OtpThresholdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpThresholdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    OtpCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_OTP;
    cmdSubType = OTPCMD_THRESHOLDQ;
    dataLen = sizeof(g_otpInfo.threshold);
    pData = &g_otpInfo.threshold;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: OtpResponseSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == OtpResponseVerify(cmdDataLen, pCmdData, (void *)&response))
    {
        g_otpInfo.response = response;
    }
}


/*********************************************************************************************
函 数 名: OtpResponseQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpResponseQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    OtpCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_OTP;
    cmdSubType = OTPCMD_RESPONSEQ;
    dataLen = sizeof(g_otpInfo.response);
    pData = (u8 *)&g_otpInfo.response;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: OtpCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpCmdInit(void)
{
    memset(pOtpCmdFunc, 0, sizeof(pOtpCmdFunc));

    pOtpCmdFunc[OTPCMD_STATE]      = OtpStateSet;
    pOtpCmdFunc[OTPCMD_STATEQ]     = OtpStateQuery;
    pOtpCmdFunc[OTPCMD_THRESHOLD]  = OtpThresholdSet;
    pOtpCmdFunc[OTPCMD_THRESHOLDQ] = OtpThresholdQuery;
    pOtpCmdFunc[OTPCMD_RESPONSE]   = OtpResponseSet;
    pOtpCmdFunc[OTPCMD_RESPONSEQ]  = OtpResponseQuery;
}

            
/*********************************************************************************************
函 数 名: OtpCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OtpCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < OTPCMD_RESERVE) && (pOtpCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pOtpCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*********************************************************************************************
函 数 名: DsensorStateSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;
    u8   index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == DsensorStateVerify(cmdDataLen, pCmdData, (void *)&bEnable, &index))
    {
        g_dsensorInfo[index].bEnable = bEnable;
    }
}


/*********************************************************************************************
函 数 名: DsensorStateQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorStateQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    DsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    if ((sizeof(u8) == cmdDataLen) && (index < DIGIT_SENSOR_NUM))
    {
        cmdMainType = CMD_DSENSOR;
        cmdSubType = DSENSORCMD_STATEQ;
        dataLen = sizeof(g_dsensorInfo[index].bEnable);
        pData = &g_dsensorInfo[index].bEnable;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: DsensorTypeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    TriggerTypeEnum triggerType;
    u8   index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == DsensorTypeVerify(cmdDataLen, pCmdData, (void *)&triggerType, &index))
    {
        g_dsensorInfo[index].triggerType = triggerType;
    }
}


/*********************************************************************************************
函 数 名: DsensorTypeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorTypeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    DsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    if ((sizeof(u8) == cmdDataLen) && (index < DIGIT_SENSOR_NUM))
    {
        cmdMainType = CMD_DSENSOR;
        cmdSubType = DSENSORCMD_TYPEQ;
        dataLen = sizeof(g_dsensorInfo[index].triggerType);
        pData = (u8 *)&g_dsensorInfo[index].triggerType;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: DsensorResponseSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;
    u8   index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == DsensorResponseVerify(cmdDataLen, pCmdData, (void *)&response, &index))
    {
        g_dsensorInfo[index].response = response;
    }
}


/*********************************************************************************************
函 数 名: DsensorResponseQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    DsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    
    if ((sizeof(u8) == cmdDataLen) && (index < DIGIT_SENSOR_NUM))
    {
        cmdMainType = CMD_DSENSOR;
        cmdSubType = DSENSORCMD_RESPONSEQ;
        dataLen = sizeof(g_dsensorInfo[index].response);
        pData = (u8 *)&g_dsensorInfo[index].response;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: DsensorCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorCmdInit(void)
{
    memset(pDsensorCmdFunc, 0, sizeof(pDsensorCmdFunc));

    pDsensorCmdFunc[DSENSORCMD_STATE]     = DsensorStateSet;
    pDsensorCmdFunc[DSENSORCMD_STATEQ]    = DsensorStateQuery;
    pDsensorCmdFunc[DSENSORCMD_TYPE]      = DsensorTypeSet;
    pDsensorCmdFunc[DSENSORCMD_TYPEQ]     = DsensorTypeQuery;
    pDsensorCmdFunc[DSENSORCMD_RESPONSE]  = DsensorResponseSet;
    pDsensorCmdFunc[DSENSORCMD_RESPONSEQ] = DsensorResponseQuery;
}

            
/*********************************************************************************************
函 数 名: DsensorCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DsensorCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < DSENSORCMD_RESERVE) && (pDsensorCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pDsensorCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: AsensorStateSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;
    u8   index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == AsensorStateVerify(cmdDataLen, pCmdData, (void *)&bEnable, &index))
    {
        g_asensorInfo[index].bEnable = bEnable;
    }
}


/*********************************************************************************************
函 数 名: AsensorStateQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorStateQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    AsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    
    if ((sizeof(u8) == cmdDataLen) && (index < ANALOG_SENSOR_NUM))
    {
        cmdMainType = CMD_ASENSOR;
        cmdSubType = ASENSORCMD_STATEQ;
        dataLen = sizeof(g_asensorInfo[index].bEnable);
        pData = &g_asensorInfo[index].bEnable;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: AsensorThresholdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorThresholdSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 threshold;
    u8  index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == AsensorThresholdVerify(cmdDataLen, pCmdData, (void *)&threshold, &index))
    {
        g_asensorInfo[index].threshold = threshold;
    }
}


/*********************************************************************************************
函 数 名: AsensorThresholdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorThresholdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    AsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    
    if ((sizeof(u8) == cmdDataLen) && (index < ANALOG_SENSOR_NUM))
    {
        cmdMainType = CMD_ASENSOR;
        cmdSubType = ASENSORCMD_THRESHOLDQ;
        dataLen = sizeof(g_asensorInfo[index].threshold);
        pData = (u8 *)&g_asensorInfo[index].threshold;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: AsensorResponseSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;
    u8   index;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == AsensorResponseVerify(cmdDataLen, pCmdData, (void *)&response, &index))
    {
        g_asensorInfo[index].response = response;
    }
}


/*********************************************************************************************
函 数 名: AsensorResponseQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorResponseQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    AsensorCmdSubTypeEnum cmdSubType;
    u8 index = *pCmdData;
    u8 dataLen;
    u8 *pData;

    
    if ((sizeof(u8) == cmdDataLen) && (index < ANALOG_SENSOR_NUM))
    {
        cmdMainType = CMD_ASENSOR;
        cmdSubType = ASENSORCMD_RESPONSEQ;
        dataLen = sizeof(g_asensorInfo[index].response);
        pData = (u8 *)&g_asensorInfo[index].response;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: AsensorCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorCmdInit(void)
{
    memset(pAsensorCmdFunc, 0, sizeof(pAsensorCmdFunc));

    pAsensorCmdFunc[ASENSORCMD_STATE]      = AsensorStateSet;
    pAsensorCmdFunc[ASENSORCMD_STATEQ]     = AsensorStateQuery;
    pAsensorCmdFunc[ASENSORCMD_THRESHOLD]  = AsensorThresholdSet;
    pAsensorCmdFunc[ASENSORCMD_THRESHOLDQ] = AsensorThresholdQuery;
    pAsensorCmdFunc[ASENSORCMD_RESPONSE]   = AsensorResponseSet;
    pAsensorCmdFunc[ASENSORCMD_RESPONSEQ]  = AsensorResponseQuery;
}

            
/*********************************************************************************************
函 数 名: AsensorCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void AsensorCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < ASENSORCMD_RESERVE) && (pAsensorCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pAsensorCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************文件尾********************************************/
