/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  protocolstack.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.16;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "protocolstack.h"
#include "streambuffer.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
StreamBufferStr g_canRxBuffer;
StreamBufferStr g_canTxBuffer;
u8  canRxBuffer[480];
u8  canTxBuffer[480];

StreamBufferStr g_uartRxBuffer;
StreamBufferStr g_uartTxBuffer;
u8  uartRxBuffer[1024];
u8  uartTxBuffer[1024];

StreamBufferStr g_CmdParseBuffer;    //命令解析缓冲区
u8  CmdParseBuffer[480];

CmdParseFunc pCmdParseFunc[CMD_RESERVE];      //CAN应用层回调函数数组



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: ProtocolStackInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void ProtocolStackInit(void)
{
    //CAN phy层Buffer初始化
    StreamBufferInit(&g_canRxBuffer,  canRxBuffer,  sizeof(canRxBuffer));
    StreamBufferInit(&g_canTxBuffer,  canTxBuffer,  sizeof(canTxBuffer));
    
    //Uart phy层Buffer初始化
    StreamBufferInit(&g_uartRxBuffer,  uartRxBuffer,   sizeof(uartRxBuffer));
    StreamBufferInit(&g_uartTxBuffer,  uartTxBuffer,   sizeof(uartTxBuffer));

    //命令解析相关Buffer初始化
    memset(pCmdParseFunc, 0, sizeof(pCmdParseFunc));
    StreamBufferInit(&g_CmdParseBuffer, CmdParseBuffer, sizeof(CmdParseBuffer));    
}


/*********************************************************************************************
函 数 名: CmdParseFrameRegister;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CmdParseFrameRegister(CmdTypeEnum msgType, CmdParseFunc pFunc)
{
    if (msgType < CMD_RESERVE)
    {    
        pCmdParseFunc[msgType] = pFunc;
    }
}


/*********************************************************************************************
函 数 名: UsartAppFrameProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CmdParseFrameProcess(void)
{
    CmdParseFrameStr *pCmdParseFrame = NULL;


    if (((!g_canRxBuffer.bNotEmpty) && (!g_uartRxBuffer.bNotEmpty) && g_CmdParseBuffer.bNotEmpty) || 
        g_CmdParseBuffer.bAlmostFull)
    {
        pCmdParseFrame = (CmdParseFrameStr *)GetHead(&g_CmdParseBuffer);
        
        if ((pCmdParseFrame->mainType < CMD_RESERVE) && (pCmdParseFunc[pCmdParseFrame->mainType] != NULL))
        {    
            pCmdParseFunc[pCmdParseFrame->mainType](pCmdParseFrame);
        }
        
        Dequeue(&g_CmdParseBuffer, pCmdParseFrame->GET_CMD_PARSE_FRMAE_TOTAL_SIZE);
    }
}



/*******************************************文件尾********************************************/