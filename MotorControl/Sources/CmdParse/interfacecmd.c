/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  interfacecmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include "interfacecmd.h"
#include "intfcparaverify.h"
#include "usartphy.h"
#include "canphy.h"
#include "protocolstack.h"



/****************************************外部变量声明*****************************************/
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pUartIntfcCmdFunc[UARTCMD_RESERVE];
SubCmdProFunc pCanIntfcCmdFunc[CANCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: UartBaudSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartBaudSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 baudIndex;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == UartBaudVerify(cmdDataLen, pCmdData, (void *)&baudIndex))
    {
        g_systemIntfc.uartIntfc.baudIndex = baudIndex;
    }
}


/*********************************************************************************************
函 数 名: UartBaudQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartWordLenSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartWordLenSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 wordLen;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == UartWordLenVerify(cmdDataLen, pCmdData, (void *)&wordLen))
    {
        g_systemIntfc.uartIntfc.wordLen = wordLen;
    }
}


/*********************************************************************************************
函 数 名: UartWordLenQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartFlowCtlSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartFlowCtlSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 flowCtl;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == UartFlowCtlVerify(cmdDataLen, pCmdData, (void *)&flowCtl))
    {
        g_systemIntfc.uartIntfc.flowCtl = flowCtl;
    }
}


/*********************************************************************************************
函 数 名: UartFlowCtlQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartParitySet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartParitySet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 parity;

    
    //进行参数验证 
    if (PARA_VERIFY_NO_ERROR == UartParityVerify(cmdDataLen, pCmdData, (void *)&parity))
    {
        g_systemIntfc.uartIntfc.parity = parity;
    }
}


/*********************************************************************************************
函 数 名: UartParityQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartStopBitSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartStopBitSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 stopBit;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == UartStopBitVerify(cmdDataLen, pCmdData, (void *)&stopBit))
    {
        g_systemIntfc.uartIntfc.stopBit = stopBit;
    }
}


/*********************************************************************************************
函 数 名: UartStopBitQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartApplyPara;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartApplyPara(u8 cmdDataLen, u8 *pCmdData)
{    
    USARTInit();
}


/*********************************************************************************************
函 数 名: UartIntfcCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: UartIntfcCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanTypeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanTypeSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 idIndex;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanTypeVerify(cmdDataLen, pCmdData, (void *)&idIndex))
    {
        g_systemIntfc.canIntfc.idTypeIndex = idIndex;
    }
}


/*********************************************************************************************
函 数 名: CanTypeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanSendIdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanSendIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 sendId;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanSendIdVerify(cmdDataLen, pCmdData, (void *)&sendId))
    {
        g_systemIntfc.canIntfc.sendId = sendId;
    }
}


/*********************************************************************************************
函 数 名: CanSendIdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanBaudSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanBaudSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 baudIndex;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanBaudVerify(cmdDataLen, pCmdData, (void *)&baudIndex))
    {
        g_systemIntfc.canIntfc.baudIndex = baudIndex;
    }
}


/*********************************************************************************************
函 数 名: CanBaudQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanGroupSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanGroupSet(u8 cmdDataLen, u8 *pCmdData)
{
    u8 group;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanGroupVerify(cmdDataLen, pCmdData, (void *)&group))
    {
        g_systemIntfc.canIntfc.group = group;
    }
}


/*********************************************************************************************
函 数 名: CanGroupQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanTargetIdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanTargetIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 targetId;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanTargetIdVerify(cmdDataLen, pCmdData, (void *)&targetId))
    {
        g_systemIntfc.canIntfc.targetId = targetId;
    }
}


/*********************************************************************************************
函 数 名: CanTargetIdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanGroupIdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanGroupIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 groupId;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanGroupIdVerify(cmdDataLen, pCmdData, (void *)&groupId))
    {
        g_systemIntfc.canIntfc.groupId = groupId;
    }
}


/*********************************************************************************************
函 数 名: CanGroupIdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanRadioIdSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanRadioIdSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 radioId;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == CanRadioIdVerify(cmdDataLen, pCmdData, (void *)&radioId))
    {
        g_systemIntfc.canIntfc.radioId = radioId;
    }
}


/*********************************************************************************************
函 数 名: CanRadioIdQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanApplyPara;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanApplyPara(u8 cmdDataLen, u8 *pCmdData)
{    
    CANInit();
}


/*********************************************************************************************
函 数 名: CanIntfcCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: CanIntfcCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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



/*******************************************文件尾********************************************/