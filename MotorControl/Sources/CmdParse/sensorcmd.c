/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  sensorcmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "sensorcmd.h"
#include "sensorparaverify.h"
#include "cmdparse.h"



/****************************************�ⲿ��������*****************************************/
extern OtpInfoStruct     g_otpInfo;
extern DsensorInfoStruct g_dsensorInfo[DIGIT_SENSOR_NUM];
extern AsensorInfoStruct g_asensorInfo[ANALOG_SENSOR_NUM];



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pOtpCmdFunc[OTPCMD_RESERVE];
SubCmdProFunc pDsensorCmdFunc[DSENSORCMD_RESERVE];
SubCmdProFunc pAsensorCmdFunc[ASENSORCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: OtpStateSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OtpStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == OtpStateVerify(cmdDataLen, pCmdData, (void *)&bEnable))
    {
        g_otpInfo.bEnable = bEnable;
    }
}


/*********************************************************************************************
�� �� ��: OtpStateQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OtpThresholdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OtpThresholdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 threshold;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == OtpThresholdVerify(cmdDataLen, pCmdData, (void *)&threshold))
    {
        g_otpInfo.threshold = threshold;
    }
}


/*********************************************************************************************
�� �� ��: OtpThresholdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OtpResponseSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void OtpResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == OtpResponseVerify(cmdDataLen, pCmdData, (void *)&response))
    {
        g_otpInfo.response = response;
    }
}


/*********************************************************************************************
�� �� ��: OtpResponseQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OtpCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: OtpCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: DsensorStateSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void DsensorStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;
    u8   index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == DsensorStateVerify(cmdDataLen, pCmdData, (void *)&bEnable, &index))
    {
        g_dsensorInfo[index].bEnable = bEnable;
    }
}


/*********************************************************************************************
�� �� ��: DsensorStateQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: DsensorTypeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void DsensorTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    TriggerTypeEnum triggerType;
    u8   index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == DsensorTypeVerify(cmdDataLen, pCmdData, (void *)&triggerType, &index))
    {
        g_dsensorInfo[index].triggerType = triggerType;
    }
}


/*********************************************************************************************
�� �� ��: DsensorTypeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: DsensorResponseSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void DsensorResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;
    u8   index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == DsensorResponseVerify(cmdDataLen, pCmdData, (void *)&response, &index))
    {
        g_dsensorInfo[index].response = response;
    }
}


/*********************************************************************************************
�� �� ��: DsensorResponseQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: DsensorCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: DsensorCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: AsensorStateSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void AsensorStateSet(u8 cmdDataLen, u8 *pCmdData)
{
    bool bEnable;
    u8   index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == AsensorStateVerify(cmdDataLen, pCmdData, (void *)&bEnable, &index))
    {
        g_asensorInfo[index].bEnable = bEnable;
    }
}


/*********************************************************************************************
�� �� ��: AsensorStateQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: AsensorThresholdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void AsensorThresholdSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 threshold;
    u8  index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == AsensorThresholdVerify(cmdDataLen, pCmdData, (void *)&threshold, &index))
    {
        g_asensorInfo[index].threshold = threshold;
    }
}


/*********************************************************************************************
�� �� ��: AsensorThresholdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: AsensorResponseSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void AsensorResponseSet(u8 cmdDataLen, u8 *pCmdData)
{
    ResponseTypeEnum response;
    u8   index;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == AsensorResponseVerify(cmdDataLen, pCmdData, (void *)&response, &index))
    {
        g_asensorInfo[index].response = response;
    }
}


/*********************************************************************************************
�� �� ��: AsensorResponseQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: AsensorCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: AsensorCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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



/*******************************************�ļ�β********************************************/
