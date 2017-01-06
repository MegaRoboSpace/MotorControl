/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  softtimer.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.11;
历史版本:  无;
*********************************************************************************************/
#include "softtimer.h"
#include "usartphy.h"
#include "pvtcmd.h"



/****************************************外部变量声明*****************************************/
extern volatile u64 g_systemMilliSecTick;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SoftTimerStr g_uartDmaTimer;
SoftTimerStr g_pvtCalcEndTimer;
SoftTimerStr g_debugTimer;



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: Delay;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void Delay(u32 count)
{
    for(; count!= 0;count--);
}


/*********************************************************************************************
函 数 名: StimerInitPrivate;
实现功能: 软件定时器初始化; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void StimerInit(SoftTimerStr *thiss, u16 interval, timeOutFunc fTimerProcessor)
{
    thiss->periodMS = interval;
    thiss->timeoutMS = 0;
    thiss->timerOut = fTimerProcessor;
    thiss->bUsed = false;
}


/*********************************************************************************************
函 数 名: StimerExaminePrivate;
实现功能: 检查指定名字的定时器是否超时; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
bool StimerExamine(SoftTimerStr * thiss)
{  

    if(!thiss->bUsed)
        return false;

    static s16 temp = 0;
    temp = (s16)(thiss->timeoutMS - g_systemMilliSecTick);

    if(temp <= 0)
    {  
        if(thiss->timerOut == NULL)
        {
            return true;
        }
        else
        {
            thiss->timerOut();   
        }
    }
    return false;
}


/*********************************************************************************************
函 数 名: StimerAdd;
实现功能: 把时钟添加到时钟链表中并启动; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void StimerAdd(SoftTimerStr *ptSoftTimer)
{
    ptSoftTimer->timeoutMS = g_systemMilliSecTick + ptSoftTimer->periodMS;
    ptSoftTimer->bUsed = true;
}


/*********************************************************************************************
函 数 名: StimerDelete;
实现功能: 把指定名字的时钟从系统时钟链表中删除; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
bool StimerDelete(SoftTimerStr *ptSoftTimer)
{
    ptSoftTimer->bUsed = false;
    return true;
}


/*********************************************************************************************
函 数 名: StimerCheck;
实现功能: 把指定名字的时钟从系统时钟链表中删除; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void StimerAllCheck(void)
{
    StimerExamine(&g_uartDmaTimer);
    StimerExamine(&g_pvtCalcEndTimer);
    StimerExamine(&g_debugTimer);
}


/*********************************************************************************************
函 数 名: UartDmaTimeroutCB;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UartDmaTimeroutCB(void)
{
    //清中断标识，开Usart接收中断
    USART_ClearFlag(USART1, USART_FLAG_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    //关DMA，超时定时器
    DMA_Cmd(USART1_RX_DMA_CH, DISABLE);
    StimerDelete(&g_uartDmaTimer);
}


/*********************************************************************************************
函 数 名: PvtCalcEndTimerOutCB;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtCalcEndTimerOutCB(void)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_CALCEND;
    CmdFrameSend(cmdMainType, cmdSubType, 0, NULL);

    //继续开启定时器，收到回复的时候关闭
    StimerAdd(&g_pvtCalcEndTimer);
}


/*********************************************************************************************
函 数 名: DebugTimerOutCB;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DebugTimerOutCB(void)
{
    BitAction bitVal[2] = {Bit_SET, Bit_RESET};
    static u8 index = 0;
    
    
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, bitVal[index]);
    index++;
    if (index >= 2)
    {
        index = 0;
    }

    //继续开启定时器，收到回复的时候关闭
    StimerAdd(&g_debugTimer);
}


/*********************************************************************************************
函 数 名: StimerAllInit;
实现功能: 无;
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void StimerAllInit(void)
{
    StimerInit(&g_uartDmaTimer,    50,   UartDmaTimeroutCB);       //串口DMA接收定时器，超时时间50ms
    StimerInit(&g_pvtCalcEndTimer, 1000, PvtCalcEndTimerOutCB);    //PVT计算结束后向上位机上报的定时器，超时时间1s
    StimerInit(&g_debugTimer,      10,   DebugTimerOutCB);         //调试用的翻转管脚输出的定时器，超时时间10ms

    //温度传感器的温度采集定时器 NICK MARK

    //模拟传感器的定时器 NICK MARK

    //运行状态上报的定时器 NICK MARK
}



/*******************************************文件尾********************************************/
