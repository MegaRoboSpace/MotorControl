/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  usartmac.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.16;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "usartmac.h"
#include "usartphy.h"
#include "streambuffer.h"
#include "msgescape.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/
extern StreamBufferStr g_uartRxBuffer;
extern StreamBufferStr g_uartTxBuffer;
extern StreamBufferStr g_CmdParseBuffer;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: UartFrameSend;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartFrameSend(u8 dataLen, u8 *pDataBuffer)
{
    UartPhyFrameStr *pUartPhyFrame = NULL;
    UartPhyFrameStr uartPhyFrame;
    u8 *pPhyFrame;
    u8 *pTempFrame;
    u8 xorValue = USART1_START_OF_FRAME;
    u8 headLen = sizeof(UartPhyFrameStr) - 1;
    u8 i;


    u8 sendLen = dataLen * 2 + sizeof(UartPhyFrameStr);    //防止转义多出来空间，先申请两倍数据空间
    pPhyFrame = ReserveMemory(&g_uartTxBuffer, sendLen);
    if (NULL != pPhyFrame)
    {
        pUartPhyFrame = (UartPhyFrameStr *)pPhyFrame;

        pPhyFrame[0] = USART1_START_OF_FRAME;
        
        uartPhyFrame.frameLen = dataLen + sizeof(UartPhyFrameStr);
        uartPhyFrame.xorValue = 0;
        pTempFrame = &uartPhyFrame.frameLen;

        //计算帧头校验值，不包括SOF
        for (i = 0;i < headLen;i++)
        {
            xorValue ^= pTempFrame[i];
        }

        //计算数据校验值
        for (i = 0;i < dataLen;i++)
        {
            xorValue ^= pDataBuffer[i];
        }
        uartPhyFrame.xorValue = xorValue;

        //转义帧头
        EscapeMsg(pPhyFrame + 1, pTempFrame, &headLen);    //加一是跳过SOF

        //转义数据
        EscapeMsg(pPhyFrame + 1 + headLen, pDataBuffer, &dataLen);    //加一是跳过SOF
        pUartPhyFrame->frameLen = headLen + 1 + dataLen;    //加一是算上SOF
        
        Enqueue(&g_uartTxBuffer, pUartPhyFrame->frameLen);
    }
}

/*********************************************************************************************
函 数 名: UsartFrameProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UsartFrameProcess()
{
    UartPhyFrameStr *pUartPhyFrame = NULL;
    CmdParseFrameStr *pCmdPareFrame = NULL;
    u8 frameLen;

    
    //如果Usart1接收缓冲区有数据就处理
    if (g_uartRxBuffer.bNotEmpty)
    {   
        pUartPhyFrame = (UartPhyFrameStr *)GetHead(&g_uartRxBuffer);
        frameLen = pUartPhyFrame->frameLen;
        if (DeescapeMsgAndXorCheck((u8 *)pUartPhyFrame, &frameLen))    //校验反转义，并且返回数据的真实长度                              
        {
            pCmdPareFrame = (CmdParseFrameStr *)ReserveMemory(&g_CmdParseBuffer,  
                                                               pUartPhyFrame->GET_UART_PHY_FRMAE_PAYLOAD_SIZE);

            if (NULL != pCmdPareFrame)
            {
                pCmdPareFrame->mainType = (CmdTypeEnum)pUartPhyFrame->payload[0];
                pCmdPareFrame->subType = pUartPhyFrame->payload[1];
                pCmdPareFrame->dataLen = frameLen - sizeof(UartPhyFrameStr) - 2;    //CmdParse帧的长度不包括主类型和子类型，所以减2
                memcpy(pCmdPareFrame->payload, &pUartPhyFrame->payload[2], pCmdPareFrame->dataLen);    //拷贝剩余的数据
                
                Enqueue(&g_CmdParseBuffer, pCmdPareFrame->GET_CMD_PARSE_FRMAE_TOTAL_SIZE);
            }
        }

        //关所有中断    (NICK MARK)
        Dequeue(&g_uartRxBuffer, pUartPhyFrame->frameLen); //处理完成后出队
        //开所有中断    (NICK MARK)
    }

    //如果发送缓冲区有数据就发送
    if (g_uartTxBuffer.bNotEmpty)
    {
        pUartPhyFrame = (UartPhyFrameStr *)GetHead(&g_uartTxBuffer);

        USARTSend((u8 *)pUartPhyFrame, pUartPhyFrame->frameLen);

        Dequeue(&g_uartTxBuffer, pUartPhyFrame->frameLen); //处理完成后出队
    }
}



/*******************************************文件尾********************************************/