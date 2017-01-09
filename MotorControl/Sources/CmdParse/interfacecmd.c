/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  interfacecmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "interfacecmd.h"
#include "intfcparaverify.h"
#include "usartphy.h"
#include "canphy.h"
#include "protocolstack.h"



/****************************************�ⲿ��������*****************************************/
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pUartIntfcCmdFunc[UARTCMD_RESERVE];
SubCmdProFunc pCanIntfcCmdFunc[CANCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: UartBaudSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartBaudSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 baudIndex;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == UartBaudVerify(cmdDataLen, pCmdData, (void *)&baudIndex))
    {
        g_systemIntfc.uartIntfc.baudIndex = baudIndex;
    }
}


/*********************************************************************************************
�� �� ��: UartBaudQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartBaudQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    UartCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_UART;
    cmdSubType = UARTCMD_BAUDQ;
    dataLen = sizeof(g_systemIntfc.uartIntfc.baudIndex);
    pData = &g_systemIntfc.uartIntfc.baudIndex;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: UartWordLenSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartWordLenSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 wordLen;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == UartWordLenVerify(cmdDataLen, pCmdData, (void *)&wordLen))
    {
        g_systemIntfc.uartIntfc.wordLen = wordLen;
    }
}


/*********************************************************************************************
�� �� ��: UartWordLenQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartWordLenQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    UartCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    //u8 *pData;
    u8 data;

    
    cmdMainType = CMD_UART;
    cmdSubType = UARTCMD_WORDLENQ;
    dataLen = 1;
    data = g_systemIntfc.uartIntfc.wordLen;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, &data);
    //dataLen = sizeof(g_systemIntfc.uartIntfc.wordLen);
    //pData = &g_systemIntfc.uartIntfc.wordLen;
    //CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: UartFlowCtlSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartFlowCtlSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 flowCtl;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == UartFlowCtlVerify(cmdDataLen, pCmdData, (void *)&flowCtl))
    {
        g_systemIntfc.uartIntfc.flowCtl = flowCtl;
    }
}


/*********************************************************************************************
�� �� ��: UartFlowCtlQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartFlowCtlQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    UartCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    //u8 *pData;
    u8 data;

    
    cmdMainType = CMD_UART;
    cmdSubType = UARTCMD_FLOWCTLQ;
    dataLen = 1;
    data = g_systemIntfc.uartIntfc.flowCtl;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, &data);
    //dataLen = sizeof(g_systemIntfc.uartIntfc.flowCtl);
    //pData = &g_systemIntfc.uartIntfc.flowCtl;
    //CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: UartParitySet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartParitySet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 parity;

    
    //���в�����֤ 
    if (PARA_VERIFY_NO_ERROR == UartParityVerify(cmdDataLen, pCmdData, (void *)&parity))
    {
        g_systemIntfc.uartIntfc.parity = parity;
    }
}


/*********************************************************************************************
�� �� ��: UartParityQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartParityQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    UartCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    //u8 *pData;
    u8 data;

    
    cmdMainType = CMD_UART;
    cmdSubType = UARTCMD_PARITYQ;
    dataLen = 1;
    data = g_systemIntfc.uartIntfc.parity;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, &data);
    //dataLen = sizeof(g_systemIntfc.uartIntfc.parity);
    //pData = &g_systemIntfc.uartIntfc.parity;
    //CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: UartStopBitSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartStopBitSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 stopBit;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == UartStopBitVerify(cmdDataLen, pCmdData, (void *)&stopBit))
    {
        g_systemIntfc.uartIntfc.stopBit = stopBit;
    }
}


/*********************************************************************************************
�� �� ��: UartStopBitQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartStopBitQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    UartCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    //u8 *pData;
    u8 data;

    
    cmdMainType = CMD_UART;
    cmdSubType = UARTCMD_STOPBITQ;
    dataLen = 1;
    data = g_systemIntfc.uartIntfc.stopBit;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, &data);
    //dataLen = sizeof(g_systemIntfc.uartIntfc.stopBit);
    //pData = &g_systemIntfc.uartIntfc.stopBit;
    //CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: UartApplyPara;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartApplyPara(u8 cmdDataLen, u8 *pCmdData)
{    
    USARTInit();
}


/*********************************************************************************************
�� �� ��: UartIntfcCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartIntfcCmdInit(void)
{
    pUartIntfcCmdFunc[UARTCMD_BAUD]      = UartBaudSet;
    pUartIntfcCmdFunc[UARTCMD_BAUDQ]     = UartBaudQuery;
    pUartIntfcCmdFunc[UARTCMD_WORDLEN]   = UartWordLenSet;
    pUartIntfcCmdFunc[UARTCMD_WORDLENQ]  = UartWordLenQuery;
    pUartIntfcCmdFunc[UARTCMD_FLOWCTL]   = UartFlowCtlSet;
    pUartIntfcCmdFunc[UARTCMD_FLOWCTLQ]  = UartFlowCtlQuery;
    pUartIntfcCmdFunc[UARTCMD_PARITY]    = UartParitySet;
    pUartIntfcCmdFunc[UARTCMD_PARITYQ]   = UartParityQuery;
    pUartIntfcCmdFunc[UARTCMD_STOPBIT]   = UartStopBitSet;
    pUartIntfcCmdFunc[UARTCMD_STOPBITQ]  = UartStopBitQuery;
}

            
/*********************************************************************************************
�� �� ��: UartIntfcCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void UartIntfcCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < UARTCMD_RESERVE) && (pUartIntfcCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pUartIntfcCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: CanTypeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 idIndex;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanTypeVerify(cmdDataLen, pCmdData, (void *)&idIndex))
    {
        g_systemIntfc.canIntfc.idTypeIndex = idIndex;
    }
}


/*********************************************************************************************
�� �� ��: CanTypeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanTypeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_TYPEQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.idTypeIndex);
    pData = &g_systemIntfc.canIntfc.idTypeIndex;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanSendIdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanSendIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 sendId;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanSendIdVerify(cmdDataLen, pCmdData, (void *)&sendId))
    {
        g_systemIntfc.canIntfc.sendId = sendId;
    }
}


/*********************************************************************************************
�� �� ��: CanSendIdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanSendIdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_SENDIDQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.sendId);
    pData = (u8 *)&g_systemIntfc.canIntfc.sendId;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanBaudSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanBaudSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 baudIndex;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanBaudVerify(cmdDataLen, pCmdData, (void *)&baudIndex))
    {
        g_systemIntfc.canIntfc.baudIndex = baudIndex;
    }
}


/*********************************************************************************************
�� �� ��: CanBaudQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanBaudQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_BAUDQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.baudIndex);
    pData = &g_systemIntfc.canIntfc.baudIndex;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanGroupSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanGroupSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 group;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanGroupVerify(cmdDataLen, pCmdData, (void *)&group))
    {
        g_systemIntfc.canIntfc.group = group;
    }
}


/*********************************************************************************************
�� �� ��: CanGroupQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanGroupQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_GROUPQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.group);
    pData = &g_systemIntfc.canIntfc.group;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanTargetIdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanTargetIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 targetId;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanTargetIdVerify(cmdDataLen, pCmdData, (void *)&targetId))
    {
        g_systemIntfc.canIntfc.targetId = targetId;
    }
}


/*********************************************************************************************
�� �� ��: CanTargetIdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanTargetIdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_TARGETIDQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.targetId);
    pData = (u8 *)&g_systemIntfc.canIntfc.targetId;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanGroupIdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanGroupIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 groupId;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanGroupIdVerify(cmdDataLen, pCmdData, (void *)&groupId))
    {
        g_systemIntfc.canIntfc.groupId = groupId;
    }
}


/*********************************************************************************************
�� �� ��: CanGroupIdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanGroupIdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_GROUPIDQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.groupId);
    pData = (u8 *)&g_systemIntfc.canIntfc.groupId;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanRadioIdSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanRadioIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 radioId;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == CanRadioIdVerify(cmdDataLen, pCmdData, (void *)&radioId))
    {
        g_systemIntfc.canIntfc.radioId = radioId;
    }
}


/*********************************************************************************************
�� �� ��: CanRadioIdQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanRadioIdQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    CanCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_CAN;
    cmdSubType = CANCMD_RADIOIDQ;
    dataLen = sizeof(g_systemIntfc.canIntfc.radioId);
    pData = (u8 *)&g_systemIntfc.canIntfc.radioId;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: CanApplyPara;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanApplyPara(u8 cmdDataLen, u8 *pCmdData)
{    
    CANInit();
}


/*********************************************************************************************
�� �� ��: CanIntfcCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanIntfcCmdInit(void)
{
    pCanIntfcCmdFunc[CANCMD_TYPE]      = CanTypeSet;
    pCanIntfcCmdFunc[CANCMD_TYPEQ]     = CanTypeQuery;
    pCanIntfcCmdFunc[CANCMD_SENDID]    = CanSendIdSet;
    pCanIntfcCmdFunc[CANCMD_SENDIDQ]   = CanSendIdQuery;
    pCanIntfcCmdFunc[CANCMD_BAUD]      = CanBaudSet;
    pCanIntfcCmdFunc[CANCMD_BAUDQ]     = CanBaudQuery;
    pCanIntfcCmdFunc[CANCMD_GROUP]     = CanGroupSet;
    pCanIntfcCmdFunc[CANCMD_GROUPQ]    = CanGroupQuery;
    pCanIntfcCmdFunc[CANCMD_TARGETID]  = CanTargetIdSet;
    pCanIntfcCmdFunc[CANCMD_TARGETIDQ] = CanTargetIdQuery;
    pCanIntfcCmdFunc[CANCMD_GROUPID]   = CanGroupIdSet;
    pCanIntfcCmdFunc[CANCMD_GROUPIDQ]  = CanGroupIdQuery;
    pCanIntfcCmdFunc[CANCMD_RADIOID]   = CanRadioIdSet;
    pCanIntfcCmdFunc[CANCMD_RADIOIDQ]  = CanRadioIdQuery;
}

            
/*********************************************************************************************
�� �� ��: CanIntfcCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CanIntfcCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < CANCMD_RESERVE) && (pCanIntfcCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pCanIntfcCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************�ļ�β********************************************/