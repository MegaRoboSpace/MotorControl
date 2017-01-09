/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motioncmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "motioncmd.h"
#include "motionparaverify.h"
#include "protocolstack.h"



/****************************************�ⲿ��������*****************************************/
extern MotionInfoStruct g_motionInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pMotionCmdFunc[MOTIONCMD_RESERVE];
SubCmdProFunc pOutOfStepCmdFunc[OOSCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: MotionRun;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionRun(u8 cmdDataLen, u8 *pCmdData)
{    
    g_motionInfo.bMotion = true;
}


/*********************************************************************************************
�� �� ��: MotionStop;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionStop(u8 cmdDataLen, u8 *pCmdData)
{    
    g_motionInfo.bMotion = false;
}


/*********************************************************************************************
�� �� ��: MotionEmergencySet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionEmergencySet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 emergency;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionEmrgVerify(cmdDataLen, pCmdData, (void *)&emergency))
    {
        g_motionInfo.emergency = emergency;
    }
}


/*********************************************************************************************
�� �� ��: MotionEmergencyQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMaxSpeedSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMaxSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxSpeed;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMaxSpeedVerify(cmdDataLen, pCmdData, (void *)&maxSpeed))
    {
        g_motionInfo.maxSpeed = maxSpeed;
    }
}


/*********************************************************************************************
�� �� ��: MotionMaxSpeedQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMinSpeedSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMinSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minSpeed;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMinSpeedVerify(cmdDataLen, pCmdData, (void *)&minSpeed))
    {
        g_motionInfo.minSpeed = minSpeed;
    }
}


/*********************************************************************************************
�� �� ��: MotionMinSpeedQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMaxPositionSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMaxPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxPosn;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMaxPosnVerify(cmdDataLen, pCmdData, (void *)&maxPosn))
    {
        g_motionInfo.maxPosn = maxPosn;
    }
}


/*********************************************************************************************
�� �� ��: MotionMaxPositionQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMinPositionSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMinPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minPosn;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMinPosnVerify(cmdDataLen, pCmdData, (void *)&minPosn))
    {
        g_motionInfo.minPosn = minPosn;
    }
}


/*********************************************************************************************
�� �� ��: MotionMinPositionQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMaxTorqueSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMaxTorqueSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 maxTorque;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMaxTorqueVerify(cmdDataLen, pCmdData, (void *)&maxTorque))
    {
        g_motionInfo.maxTorque = maxTorque;
    }
}


/*********************************************************************************************
�� �� ��: MotionMaxTorqueQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionMinTorqueSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionMinTorqueSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 minTorque;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionMinTorqueVerify(cmdDataLen, pCmdData, (void *)&minTorque))
    {
        g_motionInfo.minTorque = minTorque;
    }
}


/*********************************************************************************************
�� �� ��: MotionMinTorqueQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionOriginSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionOriginSet(u8 cmdDataLen, u8 *pCmdData)
{
    g_motionInfo.origin = g_motionInfo.steps;
}


/*********************************************************************************************
�� �� ��: MotionOriginQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionReportSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionReportSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bReptEnable;
    u8   i;

    
    for (i = 0;i < REPORT_RESERVE;i++)
    {
        //���в�����֤
        if (PARA_VERIFY_NO_ERROR == MotionReportVerify(1, pCmdData + i, (void *)&bReptEnable))
        {
            g_motionInfo.bReptEnable[i] = bReptEnable;
        }
    }
}


/*********************************************************************************************
�� �� ��: MotionReportQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionReportPeriodSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotionReportPeriodSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 reptPeriod;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotionReportperiodVerify(cmdDataLen, pCmdData, (void *)&reptPeriod))
    {
        g_motionInfo.reptPeriod = reptPeriod;
    }
}


/*********************************************************************************************
�� �� ��: MotionReportPeriodQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionOutNumQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionStepsQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionVelorityQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionTorqueQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionTempQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: MotionCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: PvtCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OutOfStepOutNumSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OutOfStepOutNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 outOfSteps;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == OutOfStepOutNumVerify(cmdDataLen, pCmdData, (void *)&outOfSteps))
    {
        g_motionInfo.outOfStepInfo.outOfSteps = outOfSteps;
    }
}


/*********************************************************************************************
�� �� ��: OutOfStepOutNumQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OutOfStepResponseSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OutOfStepResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == OutOfStepResponseVerify(cmdDataLen, pCmdData, (void *)&response))
    {
        g_motionInfo.outOfStepInfo.response = response;
    }
}


/*********************************************************************************************
�� �� ��: OutOfStepResponseQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OutOfStepCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OutOfStepCmdInit(void)
{
    pOutOfStepCmdFunc[OOSCMD_OUTNUM]    = OutOfStepOutNumSet;
    pOutOfStepCmdFunc[OOSCMD_OUTNUMQ]   = OutOfStepOutNumQuery;
    pOutOfStepCmdFunc[OOSCMD_RESPONSE]  = OutOfStepResponseSet;
    pOutOfStepCmdFunc[OOSCMD_RESPONSEQ] = OutOfStepResponseQuery;
}

            
/*********************************************************************************************
�� �� ��: PvtCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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



/*******************************************�ļ�β********************************************/