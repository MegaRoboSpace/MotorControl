/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  usart.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.08.30;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "usartphy.h"
#include "intfcparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern u32 g_uartBaudrate[UART_BAUDRATE_NUM];
extern u16 g_uartWordLen[UART_WORD_LEN_NUM];
extern u16 g_uartFlowCtl[UART_FLOW_CTL_NUM];
extern u16 g_uartStopBit[UART_STOP_BIT_NUM];
extern u16 g_uartParity[UART_PARITY_NUM];
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: USARTInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void USARTInit(void)
{ 
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;    
    NVIC_InitTypeDef  NVIC_InitStructure; 
    DMA_InitTypeDef   DMA_InitStructure;


    //����ģ��ʱ��
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

	//����TX��RX�ܽţ���������ӳ��
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

    //����DMA
    DMA_Cmd(USART1_TX_DMA_CH, DISABLE);                                        //��DMAͨ��
    DMA_DeInit(USART1_TX_DMA_CH);                                              //�ָ�ȱʡֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;                 //���ô��ڷ������ݼĴ���
    DMA_InitStructure.DMA_MemoryBaseAddr = 0;                                  //���Ⱥ͵�ַʹ�õ�ʱ��ֵ
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                         //��������λĿ�꣬�ڴ滺���� -> ����Ĵ���
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                    //�ڴ滺������ַ���ӵ���
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;    //�������ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;            //�ڴ����ݿ��8λ��1���ֽ�
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                              //���δ���ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                    //���ȼ�����
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                               //�ر��ڴ浽�ڴ��DMAģʽ
    DMA_Init(USART1_TX_DMA_CH, &DMA_InitStructure);                            //д������
    DMA_ClearFlag(DMA1_FLAG_GL4 | DMA1_FLAG_TC4 | DMA1_FLAG_TE4);              //���DMA���б�־
    DMA_ITConfig(USART1_TX_DMA_CH, DMA_IT_TC, ENABLE);                         //������������ж�

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
    

    //����USART1��������115200������λ8bit��ֹͣλ1��У��λNone��Ӳ��������None���շ�ȫʹ��
    USART_InitStructure.USART_BaudRate = g_uartBaudrate[g_systemIntfc.uartIntfc.baudIndex];
    USART_InitStructure.USART_WordLength = g_uartWordLen[g_systemIntfc.uartIntfc.wordLen];
    USART_InitStructure.USART_StopBits = g_uartStopBit[g_systemIntfc.uartIntfc.stopBit];
    USART_InitStructure.USART_Parity = g_uartParity[g_systemIntfc.uartIntfc.parity];
    USART_InitStructure.USART_HardwareFlowControl = g_uartFlowCtl[g_systemIntfc.uartIntfc.flowCtl];
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    //ʹ��USART1�����ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //ʹ��DMAͨ��4�ж�(USART1_TX)
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure); 

    //ʹ��DMAͨ��5�ж�(USART1_RX)
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);
    
   
    //ʹ��DMA����
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    //ʹ��DMA����
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

    //ʹ�ܽ����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    //ʹ��USART1
    USART_Cmd(USART1, ENABLE);
}


/*********************************************************************************************
�� �� ��: USARTRecive;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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
�� �� ��: USARTSend;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void USARTSend(u8 *pData, u8 dataLen)
{
#if 0    //DMAģʽ����ʼ֮ǰ��Ҫ�ж��ϴεķ����Ƿ��Ѿ���������Ȼ�µĴ�����ƻ��ϴδ���
    
    USART1_TX_DMA_CH->CMAR = (u32)pData;
    DMA_SetCurrDataCounter(USART1_TX_DMA_CH, dataLen);    //���贫�䳤��
    DMA_Cmd(USART1_TX_DMA_CH, ENABLE);
    
#else    //д���ݼĴ���ģʽ

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
�� �� ��: UsartBuffDataProcess;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
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



/*******************************************�ļ�β********************************************/