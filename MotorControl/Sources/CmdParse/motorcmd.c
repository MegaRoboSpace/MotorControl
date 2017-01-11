/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motorcmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "motorcmd.h"
#include "motorparaverify.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/
extern MotorInfoStruct g_motorInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pMotroCmdFunc[MOTORCMD_RESERVE];
SubCmdProFunc pEncoderCmdFunc[ENCODERCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: MotorMicroStepsSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorMicroStepsSet(u8 cmdDataLen, u8 *pCmdData)
{
    u16 microStepsIndex;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotorMicroStepsVerify(cmdDataLen, pCmdData, (void *)&microStepsIndex))
    {
        g_motorInfo.microStepsIndex = microStepsIndex;

        //΢�����Ͳ����ı����Ҫ���¼����ܵĲ��� NICK MARK
        g_motorInfo.totalSteps = g_motorInfo.microStepsIndex * g_motorInfo.stepsIndex;
    }
}


/*********************************************************************************************
�� �� ��: MotorMicroStepsQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorMicroStepsQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotorCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTOR;
    cmdSubType = MOTORCMD_MICROSTEPSQ;
    dataLen = sizeof(g_motorInfo.microStepsIndex);
    pData = (u8 *)&g_motorInfo.microStepsIndex;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: MotorGearRatioSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorGearRatioSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 gearRatio;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotorGearRatioVerify(cmdDataLen, pCmdData, (void *)&gearRatio))
    {
        g_motorInfo.gearRatio = gearRatio;
    }
}


/*********************************************************************************************
�� �� ��: MotorGearRatioQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorGearRatioQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotorCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTOR;
    cmdSubType = MOTORCMD_GEARRATIOQ;
    dataLen = sizeof(g_motorInfo.gearRatio);
    pData = (u8 *)&g_motorInfo.gearRatio;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: MotorStepAngleSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorStepAngleSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 stepsIndex;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotorStepAngleVerify(cmdDataLen, pCmdData, (void *)&stepsIndex))
    {
        g_motorInfo.stepsIndex = stepsIndex;

        //΢�����Ͳ����ı����Ҫ���¼����ܵĲ��� NICK MARK
        g_motorInfo.totalSteps = g_motorInfo.microStepsIndex * g_motorInfo.stepsIndex;
    }
}


/*********************************************************************************************
�� �� ��: MotorStepAngleQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorStepAngleQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotorCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTOR;
    cmdSubType = MOTORCMD_STEPS;
    dataLen = sizeof(g_motorInfo.stepsIndex);
    pData = (u8 *)&g_motorInfo.stepsIndex;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: MotorPeakSpeedSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorPeakSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 peakSpeed;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotorPeakSpeedVerify(cmdDataLen, pCmdData, (void *)&peakSpeed))
    {
        g_motorInfo.peakSpeed = peakSpeed;
    }
}


/*********************************************************************************************
�� �� ��: MotorPeakSpeedQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorPeakSpeedQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotorCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTOR;
    cmdSubType = MOTORCMD_PEAKSPEEDQ;
    dataLen = sizeof(g_motorInfo.peakSpeed);
    pData = (u8 *)&g_motorInfo.peakSpeed;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: MotorTypeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    MotorTypeEnum motorType;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == MotorTypeVerify(cmdDataLen, pCmdData, (void *)&motorType))
    {
        g_motorInfo.motorType = motorType;
    }
}


/*********************************************************************************************
�� �� ��: MotorTypeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorTypeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    MotorCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_MOTOR;
    cmdSubType = MOTORCMD_TYPEQ;
    dataLen = sizeof(g_motorInfo.motorType);
    pData = (u8 *)&g_motorInfo.motorType;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: MotorCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorCmdInit(void)
{
    memset(pMotroCmdFunc, 0, sizeof(pMotroCmdFunc));

    pMotroCmdFunc[MOTORCMD_MICROSTEPS]  = MotorMicroStepsSet;
    pMotroCmdFunc[MOTORCMD_MICROSTEPSQ] = MotorMicroStepsQuery;
    pMotroCmdFunc[MOTORCMD_GEARRATIO]   = MotorGearRatioSet;
    pMotroCmdFunc[MOTORCMD_GEARRATIOQ]  = MotorGearRatioQuery;
    pMotroCmdFunc[MOTORCMD_STEPS]       = MotorStepAngleSet;
    pMotroCmdFunc[MOTORCMD_STEPSQ]      = MotorStepAngleQuery;
    pMotroCmdFunc[MOTORCMD_PEAKSPEED]   = MotorPeakSpeedSet;
    pMotroCmdFunc[MOTORCMD_PEAKSPEEDQ]  = MotorPeakSpeedQuery;
    pMotroCmdFunc[MOTORCMD_TYPE]        = MotorTypeSet;
    pMotroCmdFunc[MOTORCMD_TYPEQ]       = MotorTypeQuery;
}

            
/*********************************************************************************************
�� �� ��: MotorCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void MotorCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < MOTORCMD_RESERVE) && (pMotroCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pMotroCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: EncoderLineNumSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderLineNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 lineNum;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == EncoderLineNumVerify(cmdDataLen, pCmdData, (void *)&lineNum))
    {
        g_motorInfo.encoderInfo.lineNum = lineNum;
    }
}


/*********************************************************************************************
�� �� ��: EncoderLineNumQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderLineNumQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    EncoderCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_ENCODER;
    cmdSubType = ENCODERCMD_LINENUMQ;
    dataLen = sizeof(g_motorInfo.encoderInfo.lineNum);
    pData = (u8 *)&g_motorInfo.encoderInfo.lineNum;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: EncoderChanNumSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderChanNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    EncoderChanEnum chanNum;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == EncoderChanNumVerify(cmdDataLen, pCmdData, (void *)&chanNum))
    {
        g_motorInfo.encoderInfo.chanNum = chanNum;
    }
}


/*********************************************************************************************
�� �� ��: EncoderChanNumQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderChanNumQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    EncoderCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_ENCODER;
    cmdSubType = ENCODERCMD_CHANNUMQ;
    dataLen = sizeof(g_motorInfo.encoderInfo.chanNum);
    pData = (u8 *)&g_motorInfo.encoderInfo.chanNum;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: EncoderTypeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    EncoderTypeEnum type;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == EncoderTypeVerify(cmdDataLen, pCmdData, (void *)&type))
    {
        g_motorInfo.encoderInfo.type = type;
    }
}


/*********************************************************************************************
�� �� ��: EncoderTypeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderTypeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    EncoderCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_ENCODER;
    cmdSubType = ENCODERCMD_TYPEQ;
    dataLen = sizeof(g_motorInfo.encoderInfo.type);
    pData = (u8 *)&g_motorInfo.encoderInfo.type;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: EncoderCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderCmdInit(void)
{
    memset(pEncoderCmdFunc, 0, sizeof(pEncoderCmdFunc));

    pEncoderCmdFunc[ENCODERCMD_LINENUM]  = EncoderLineNumSet;
    pEncoderCmdFunc[ENCODERCMD_LINENUMQ] = EncoderLineNumQuery;
    pEncoderCmdFunc[ENCODERCMD_CHANNUM]  = EncoderChanNumSet;
    pEncoderCmdFunc[ENCODERCMD_CHANNUMQ] = EncoderChanNumQuery;
    pEncoderCmdFunc[ENCODERCMD_TYPE]     = EncoderTypeSet;
    pEncoderCmdFunc[ENCODERCMD_TYPEQ]    = EncoderTypeQuery;
}

            
/*********************************************************************************************
�� �� ��: EncoderCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EncoderCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < ENCODERCMD_RESERVE) && (pEncoderCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pEncoderCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************�ļ�β********************************************/