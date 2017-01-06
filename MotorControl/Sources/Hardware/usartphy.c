/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  usart.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.30;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "usartphy.h"
#include "intfcparaverify.h"



/****************************************外部变量声明*****************************************/
extern u32 g_uartBaudrate[UART_BAUDRATE_NUM];
extern u16 g_uartWordLen[UART_WORD_LEN_NUM];
extern u16 g_uartFlowCtl[UART_FLOW_CTL_NUM];
extern u16 g_uartStopBit[UART_STOP_BIT_NUM];
extern u16 g_uartParity[UART_PARITY_NUM];
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: USARTInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void USARTInit(void)
{ 
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;    
    NVIC_InitTypeDef  NVIC_InitStructure; 
    DMA_InitTypeDef   DMA_InitStructure;


    //配置模块时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
#if UART1_REMAP
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOB | 
                           RCC_APB2Periph_USART1, ENABLE);
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOA | 
                           RCC_APB2Periph_USART1, ENABLE);
#endif

	//配置TX、RX管脚，进行了重映射
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);
#if UART1_REMAP
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
#endif

    //配置DMA
    DMA_Cmd(USART1_TX_DMA_CH, DISABLE);                                        //关DMA通道
    DMA_DeInit(USART1_TX_DMA_CH);                                              //恢复缺省值
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;                 //设置串口发送数据寄存器
    DMA_InitStructure.DMA_MemoryBaseAddr = 0;                                  //长度和地址使用的时候赋值
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                         //设置外设位目标，内存缓冲区 -> 外设寄存器
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                    //内存缓冲区地址增加调整
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;    //外设数据宽度8位，1个字节
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;            //内存数据宽度8位，1个字节
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                              //单次传输模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                    //优先级设置
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                               //关闭内存到内存的DMA模式
    DMA_Init(USART1_TX_DMA_CH, &DMA_InitStructure);                            //写入配置
    DMA_ClearFlag(DMA1_FLAG_GL4 | DMA1_FLAG_TC4 | DMA1_FLAG_TE4);              //清除DMA所有标志
    DMA_ITConfig(USART1_TX_DMA_CH, DMA_IT_TC, ENABLE);                         //开启传输完成中断

    DMA_Cmd(USART1_RX_DMA_CH, DISABLE);
    DMA_DeInit(USART1_RX_DMA_CH); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
    DMA_InitStructure.DMA_MemoryBaseAddr = 0;                 
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                              
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                    
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                              
    DMA_Init(USART1_RX_DMA_CH, &DMA_InitStructure);                           
    DMA_ClearFlag(DMA1_FLAG_GL5 | DMA1_FLAG_TC5 | DMA1_FLAG_TE5);              
    DMA_ITConfig(USART1_RX_DMA_CH, DMA_IT_TC, ENABLE);                        
    

    //配置USART1，波特率115200，数据位8bit，停止位1，校验位None，硬件流控制None，收发全使能
    USART_InitStructure.USART_BaudRate = g_uartBaudrate[g_systemIntfc.uartIntfc.baudIndex];
    USART_InitStructure.USART_WordLength = g_uartWordLen[g_systemIntfc.uartIntfc.wordLen];
    USART_InitStructure.USART_StopBits = g_uartStopBit[g_systemIntfc.uartIntfc.stopBit];
    USART_InitStructure.USART_Parity = g_uartParity[g_systemIntfc.uartIntfc.parity];
    USART_InitStructure.USART_HardwareFlowControl = g_uartFlowCtl[g_systemIntfc.uartIntfc.flowCtl];
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    //使能USART1接收中断
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //使能DMA通道4中断(USART1_TX)
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 

    //使能DMA通道5中断(USART1_RX)
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);
    
   
    //使能DMA发送
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    //使能DMA接收
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

    //使能接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    //使能USART1
    USART_Cmd(USART1, ENABLE);
}


/*********************************************************************************************
函 数 名: USARTRecive;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void USARTRecive(void)
{
    u16 index = 0;
    
    while(index < USART1_BUFF_SIZE)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
        }
        //usart1RxBuffer[index++] = USART_ReceiveData(USART1);  
    }
}


/*********************************************************************************************
函 数 名: USARTSend;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void USARTSend(u8 *pData, u8 dataLen)
{
#if 0    //DMA模式，开始之前需要判断上次的发送是否已经结束，不然新的传输会破坏上次传输
    
    USART1_TX_DMA_CH->CMAR = (u32)pData;
    DMA_SetCurrDataCounter(USART1_TX_DMA_CH, dataLen);    //重设传输长度
    DMA_Cmd(USART1_TX_DMA_CH, ENABLE);
    
#else    //写数据寄存器模式

    u32 index;
    
    for (index = 0;index < dataLen;index++)
    {
        USART_SendData(USART1, *pData++);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
        }
    }
#endif
}


/*********************************************************************************************
函 数 名: UsartBuffDataProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UsartBuffDataProcess(void)
{
    //u16 index;

    
    /*if (txRealLen > 0)
    {
        for (index = 0;index < txRealLen;index++)
        {
            USART_SendData(USART1, usart1TxBuffer[index]);
            txRealLen--;
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {
            }
        }
    }*/
}



/*******************************************文件尾********************************************/