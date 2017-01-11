/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  motorcmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "motorcmd.h"
#include "motorparaverify.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/
extern MotorInfoStruct g_motorInfo;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pMotroCmdFunc[MOTORCMD_RESERVE];
SubCmdProFunc pEncoderCmdFunc[ENCODERCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: MotorMicroStepsSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotorMicroStepsSet(u8 cmdDataLen, u8 *pCmdData)
{
    u16 microStepsIndex;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotorMicroStepsVerify(cmdDataLen, pCmdData, (void *)&microStepsIndex))
    {
        g_motorInfo.microStepsIndex = microStepsIndex;

        //微步数和步数改变后需要重新计算总的步数 NICK MARK
        g_motorInfo.totalSteps = g_motorInfo.microStepsIndex * g_motorInfo.stepsIndex;
    }
}


/*********************************************************************************************
函 数 名: MotorMicroStepsQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorGearRatioSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotorGearRatioSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 gearRatio;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotorGearRatioVerify(cmdDataLen, pCmdData, (void *)&gearRatio))
    {
        g_motorInfo.gearRatio = gearRatio;
    }
}


/*********************************************************************************************
函 数 名: MotorGearRatioQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorStepAngleSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotorStepAngleSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 stepsIndex;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotorStepAngleVerify(cmdDataLen, pCmdData, (void *)&stepsIndex))
    {
        g_motorInfo.stepsIndex = stepsIndex;

        //微步数和步数改变后需要重新计算总的步数 NICK MARK
        g_motorInfo.totalSteps = g_motorInfo.microStepsIndex * g_motorInfo.stepsIndex;
    }
}


/*********************************************************************************************
函 数 名: MotorStepAngleQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorPeakSpeedSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotorPeakSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 peakSpeed;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotorPeakSpeedVerify(cmdDataLen, pCmdData, (void *)&peakSpeed))
    {
        g_motorInfo.peakSpeed = peakSpeed;
    }
}


/*********************************************************************************************
函 数 名: MotorPeakSpeedQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorTypeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void MotorTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    MotorTypeEnum motorType;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == MotorTypeVerify(cmdDataLen, pCmdData, (void *)&motorType))
    {
        g_motorInfo.motorType = motorType;
    }
}


/*********************************************************************************************
函 数 名: MotorTypeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: MotorCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: EncoderLineNumSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void EncoderLineNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 lineNum;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == EncoderLineNumVerify(cmdDataLen, pCmdData, (void *)&lineNum))
    {
        g_motorInfo.encoderInfo.lineNum = lineNum;
    }
}


/*********************************************************************************************
函 数 名: EncoderLineNumQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: EncoderChanNumSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void EncoderChanNumSet(u8 cmdDataLen, u8 *pCmdData)
{
    EncoderChanEnum chanNum;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == EncoderChanNumVerify(cmdDataLen, pCmdData, (void *)&chanNum))
    {
        g_motorInfo.encoderInfo.chanNum = chanNum;
    }
}


/*********************************************************************************************
函 数 名: EncoderChanNumQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: EncoderTypeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void EncoderTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    EncoderTypeEnum type;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == EncoderTypeVerify(cmdDataLen, pCmdData, (void *)&type))
    {
        g_motorInfo.encoderInfo.type = type;
    }
}


/*********************************************************************************************
函 数 名: EncoderTypeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: EncoderCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: EncoderCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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



/*******************************************文件尾********************************************/