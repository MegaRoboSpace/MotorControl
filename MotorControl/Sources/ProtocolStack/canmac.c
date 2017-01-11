/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  canmac.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.22;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "canmac.h"
#include "canphy.h"
#include "softtimer.h"
#include "streambuffer.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/
extern StreamBufferStr g_CmdParseBuffer;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
StreamBufferStr g_canRxBuffer;
StreamBufferStr g_canTxBuffer;
u8  canRxBuffer[480];
u8  canTxBuffer[480];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: CanStreamBufferInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanStreamBufferInit(void)
{
    //CAN phy层Buffer初始化
    StreamBufferInit(&g_canRxBuffer, canRxBuffer, sizeof(canRxBuffer));
    StreamBufferInit(&g_canTxBuffer, canTxBuffer, sizeof(canTxBuffer));  
}


/*********************************************************************************************
函 数 名: SendCanFrame;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanFrameSend(u8 dataLen, u8 *pDataBuffer)
{
    u8 sendLen = dataLen + sizeof(CanPhyFrameStr);
    CanPhyFrameStr *pCanPhyFrame = NULL;
    

    pCanPhyFrame = (CanPhyFrameStr *)ReserveMemory(&g_canTxBuffer, sendLen);
    if (NULL != pCanPhyFrame)
    {
        pCanPhyFrame->frameLen = sendLen;
        
        if (dataLen > 0)
        {
            memcpy(&pCanPhyFrame->payload, pDataBuffer, dataLen);
        }

        Enqueue(&g_canTxBuffer, pCanPhyFrame->frameLen);
    }
}


/*********************************************************************************************
函 数 名: CanFrameProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CanFrameProcess(void)
{    
    CanPhyFrameStr   *pCanPhyFrame = NULL;
    CmdParseFrameStr *pCmdPareFrame = NULL;
    u8 dataLen;
    u8 canData[8];

    
    //如果CAN接收缓冲区有数据就处理
    if (g_canRxBuffer.bNotEmpty)
    {   
        pCanPhyFrame = (CanPhyFrameStr *)GetHead(&g_canRxBuffer);
        dataLen = pCanPhyFrame->GET_CAN_PHY_FRMAE_DATA_SIZE;

        //只把payload中的数据拷贝出来放入CmdParseBuffer中
        pCmdPareFrame = (CmdParseFrameStr *)ReserveMemory(&g_CmdParseBuffer, dataLen);
        if (NULL != pCmdPareFrame)
        {
            pCmdPareFrame->mainType = (CmdTypeEnum)pCanPhyFrame->payload[0];
            pCmdPareFrame->subType = pCanPhyFrame->payload[1];
            pCmdPareFrame->dataLen = dataLen - 2;    //CmdParse帧的长度不包括主类型和子类型，所以减2
            memcpy(pCmdPareFrame->payload, &pCanPhyFrame->payload[2], pCmdPareFrame->dataLen);    //拷贝剩余的数据
            Enqueue(&g_CmdParseBuffer, dataLen);
        }
        //=====================================================================================================

        //关所有中断    (NICK MARK)
        Dequeue(&g_canRxBuffer, pCanPhyFrame->frameLen); //处理完成后出队
        //开所有中断    (NICK MARK)
    }

    //如果有数据要发送
    if (g_canTxBuffer.bNotEmpty)
    {
        pCanPhyFrame = (CanPhyFrameStr *)GetHead(&g_canTxBuffer);

        //目前定义的命令集中长度都限制在了8Bytes内，所以不用分帧发，直接发就是了
        dataLen = pCanPhyFrame->GET_CAN_PHY_FRMAE_DATA_SIZE;
        if (dataLen <= CAN_FRAME_BYTES_MAX)
        {
            memcpy(canData, pCanPhyFrame->payload, dataLen);
            CANSend(pCanPhyFrame->canID, CAN_RTR_DATA, dataLen, canData);
            Delay(0x5FF);    //短暂延时，不然在高速率下发送会丢帧
        }

        Dequeue(&g_canTxBuffer, pCanPhyFrame->frameLen);
    }
}



/*******************************************文件尾********************************************/