/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motioncmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include "motioncmd.h"
#include "motionparaverify.h"
#include "protocolstack.h"



/****************************************外部变量声明*****************************************/
extern MotionInfoStruct g_motionInfo;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pMotionCmdFunc[MOTIONCMD_RESERVE];
SubCmdProFunc pOutOfStepCmdFunc[OOSCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: MotionRun;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionRun(u8 cmdDataLen, u8 *pCmdData)
{    
    g_motionInfo.bMotion = true;
}


/*********************************************************************************************
函 数 名: MotionStop;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionStop(u8 cmdDataLen, u8 *pCmdData)
{    
    g_motionInfo.bMotion = false;
}


/*********************************************************************************************
函 数 名: MotionEmergencySet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionEmergencySet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 emergency;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionEmrgVerify(cmdDataLen, pCmdData, (void *)&emergency))
    {
        g_motionInfo.emergency = emergency;
    }
}


/*********************************************************************************************
函 数 名: MotionEmergencyQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionEmergencyQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_EMRGQ;
    dataLen = sizeof(g_motionInfo.emergency);
    pData = (u8 *)&g_motionInfo.emergency;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMaxSpeedSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxSpeed;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMaxSpeedVerify(cmdDataLen, pCmdData, (void *)&maxSpeed))
    {
        g_motionInfo.maxSpeed = maxSpeed;
    }
}


/*********************************************************************************************
函 数 名: MotionMaxSpeedQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxSpeedQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MAXSPEEDQ;
    dataLen = sizeof(g_motionInfo.maxSpeed);
    pData = (u8 *)&g_motionInfo.maxSpeed;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMinSpeedSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minSpeed;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMinSpeedVerify(cmdDataLen, pCmdData, (void *)&minSpeed))
    {
        g_motionInfo.minSpeed = minSpeed;
    }
}


/*********************************************************************************************
函 数 名: MotionMinSpeedQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinSpeedQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MINSPEEDQ;
    dataLen = sizeof(g_motionInfo.minSpeed);
    pData = (u8 *)&g_motionInfo.minSpeed;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMaxPositionSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxPosn;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMaxPosnVerify(cmdDataLen, pCmdData, (void *)&maxPosn))
    {
        g_motionInfo.maxPosn = maxPosn;
    }
}


/*********************************************************************************************
函 数 名: MotionMaxPositionQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxPositionQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MAXPOSNQ;
    dataLen = sizeof(g_motionInfo.maxPosn);
    pData = (u8 *)&g_motionInfo.maxPosn;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMinPositionSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minPosn;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMinPosnVerify(cmdDataLen, pCmdData, (void *)&minPosn))
    {
        g_motionInfo.minPosn = minPosn;
    }
}


/*********************************************************************************************
函 数 名: MotionMinPositionQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinPositionQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MINPOSNQ;
    dataLen = sizeof(g_motionInfo.minPosn);
    pData = (u8 *)&g_motionInfo.minPosn;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMaxTorqueSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxTorqueSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxTorque;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMaxTorqueVerify(cmdDataLen, pCmdData, (void *)&maxTorque))
    {
        g_motionInfo.maxTorque = maxTorque;
    }
}


/*********************************************************************************************
函 数 名: MotionMaxTorqueQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMaxTorqueQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MAXTORQUEQ;
    dataLen = sizeof(g_motionInfo.maxTorque);
    pData = (u8 *)&g_motionInfo.maxTorque;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionMinTorqueSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinTorqueSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minTorque;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionMinTorqueVerify(cmdDataLen, pCmdData, (void *)&minTorque))
    {
        g_motionInfo.minTorque = minTorque;
    }
}


/*********************************************************************************************
函 数 名: MotionMinTorqueQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionMinTorqueQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_MINTORQUEQ;
    dataLen = sizeof(g_motionInfo.minTorque);
    pData = (u8 *)&g_motionInfo.minTorque;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionOriginSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionOriginSet(u8 cmdDataLen, u8 *pCmdData)
{
    g_motionInfo.origin = g_motionInfo.steps;
}


/*********************************************************************************************
函 数 名: MotionOriginQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionOriginQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_ORIGINQ;
    dataLen = sizeof(g_motionInfo.origin);
    pData = (u8 *)&g_motionInfo.origin;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionReportSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionReportSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bReptEnable;
    u8   i;

    
    for (i = 0;i < REPORT_RESERVE;i++)
    {
        //进行参数验证
        if (PARA_VERIFY_NO_ERROR == MotionReportVerify(1, pCmdData + i, (void *)&bReptEnable))
        {
            g_motionInfo.bReptEnable[i] = bReptEnable;
        }
    }
}


/*********************************************************************************************
函 数 名: MotionReportQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionReportQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_REPORTQ;
    dataLen = REPORT_RESERVE;
    pData = g_motionInfo.bReptEnable;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionReportPeriodSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionReportPeriodSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 reptPeriod;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotionReportperiodVerify(cmdDataLen, pCmdData, (void *)&reptPeriod))
    {
        g_motionInfo.reptPeriod = reptPeriod;
    }
}


/*********************************************************************************************
函 数 名: MotionReportPeriodQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionReportPeriodQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_RPPERIODQ;
    dataLen = sizeof(g_motionInfo.reptPeriod);
    pData = (u8 *)&g_motionInfo.reptPeriod;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionOutNumQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionOutNumQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_OOSTEPSQ;
    dataLen = sizeof(g_motionInfo.outOfSteps);
    pData = (u8 *)&g_motionInfo.outOfSteps;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionStepsQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionStepsQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_STEPSQ;
    dataLen = sizeof(g_motionInfo.steps);
    pData = (u8 *)&g_motionInfo.steps;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionVelorityQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionVelorityQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_VELORITYQ;
    dataLen = sizeof(g_motionInfo.velority);
    pData = (u8 *)&g_motionInfo.velority;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionTorqueQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionTorqueQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_TORQUEQ;
    dataLen = sizeof(g_motionInfo.torque);
    pData = (u8 *)&g_motionInfo.torque;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionTempQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionTempQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotionCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = MOTIONCMD_TEMPQ;
    dataLen = sizeof(g_motionInfo.temp);
    pData = &g_motionInfo.temp;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: MotionCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionCmdInit(void)
{
    pMotionCmdFunc[MOTIONCMD_RUN]        = MotionRun;
    pMotionCmdFunc[MOTIONCMD_STOP]       = MotionStop;
    pMotionCmdFunc[MOTIONCMD_EMRG]       = MotionEmergencySet;
    pMotionCmdFunc[MOTIONCMD_EMRGQ]      = MotionEmergencyQuery;
    pMotionCmdFunc[MOTIONCMD_MAXSPEED]   = MotionMaxSpeedSet;
    pMotionCmdFunc[MOTIONCMD_MAXSPEEDQ]  = MotionMaxSpeedQuery;
    pMotionCmdFunc[MOTIONCMD_MINSPEED]   = MotionMinSpeedSet;
    pMotionCmdFunc[MOTIONCMD_MINSPEEDQ]  = MotionMinSpeedQuery;
    pMotionCmdFunc[MOTIONCMD_MAXPOSN]    = MotionMaxPositionSet;
    pMotionCmdFunc[MOTIONCMD_MAXPOSNQ]   = MotionMaxPositionQuery;
    pMotionCmdFunc[MOTIONCMD_MINPOSN]    = MotionMinPositionSet;
    pMotionCmdFunc[MOTIONCMD_MINPOSNQ]   = MotionMinPositionQuery;
    pMotionCmdFunc[MOTIONCMD_MAXTORQUE]  = MotionMaxTorqueSet;
    pMotionCmdFunc[MOTIONCMD_MAXTORQUEQ] = MotionMaxTorqueQuery;
    pMotionCmdFunc[MOTIONCMD_MINTORQUE]  = MotionMinTorqueSet;
    pMotionCmdFunc[MOTIONCMD_MINTORQUEQ] = MotionMinTorqueQuery;
    pMotionCmdFunc[MOTIONCMD_ORIGIN]     = MotionOriginSet;
    pMotionCmdFunc[MOTIONCMD_ORIGINQ]    = MotionOriginQuery;
    pMotionCmdFunc[MOTIONCMD_REPORT]     = MotionReportSet;
    pMotionCmdFunc[MOTIONCMD_REPORTQ]    = MotionReportQuery;
    pMotionCmdFunc[MOTIONCMD_RPPERIOD]   = MotionReportPeriodSet;
    pMotionCmdFunc[MOTIONCMD_RPPERIODQ]  = MotionReportPeriodQuery;
    pMotionCmdFunc[MOTIONCMD_OOSTEPSQ]   = MotionOutNumQuery;
    pMotionCmdFunc[MOTIONCMD_STEPSQ]     = MotionStepsQuery;
    pMotionCmdFunc[MOTIONCMD_VELORITYQ]  = MotionVelorityQuery;
    pMotionCmdFunc[MOTIONCMD_TORQUEQ]    = MotionTorqueQuery;
    pMotionCmdFunc[MOTIONCMD_TEMPQ]      = MotionTempQuery;
}

            
/*********************************************************************************************
函 数 名: PvtCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotionCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < MOTIONCMD_RESERVE) && (pMotionCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pMotionCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
函 数 名: OutOfStepOutNumSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepOutNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 outOfSteps;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == OutOfStepOutNumVerify(cmdDataLen, pCmdData, (void *)&outOfSteps))
    {
        g_motionInfo.outOfStepInfo.outOfSteps = outOfSteps;
    }
}


/*********************************************************************************************
函 数 名: OutOfStepOutNumQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepOutNumQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    OOStepCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = OOSCMD_OUTNUMQ;
    dataLen = sizeof(g_motionInfo.outOfStepInfo.outOfSteps);
    pData = (u8 *)&g_motionInfo.outOfStepInfo.outOfSteps;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: OutOfStepResponseSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == OutOfStepResponseVerify(cmdDataLen, pCmdData, (void *)&response))
    {
        g_motionInfo.outOfStepInfo.response = response;
    }
}


/*********************************************************************************************
函 数 名: OutOfStepResponseQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepResponseQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    OOStepCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTION;
    cmdSubType = OOSCMD_RESPONSEQ;
    dataLen = sizeof(g_motionInfo.outOfStepInfo.response);
    pData = (u8 *)&g_motionInfo.outOfStepInfo.response;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
函 数 名: OutOfStepCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepCmdInit(void)
{
    pOutOfStepCmdFunc[OOSCMD_OUTNUM]    = OutOfStepOutNumSet;
    pOutOfStepCmdFunc[OOSCMD_OUTNUMQ]   = OutOfStepOutNumQuery;
    pOutOfStepCmdFunc[OOSCMD_RESPONSE]  = OutOfStepResponseSet;
    pOutOfStepCmdFunc[OOSCMD_RESPONSEQ] = OutOfStepResponseQuery;
}

            
/*********************************************************************************************
函 数 名: PvtCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void OutOfStepCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < OOSCMD_RESERVE) && (pOutOfStepCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pOutOfStepCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************文件尾********************************************/