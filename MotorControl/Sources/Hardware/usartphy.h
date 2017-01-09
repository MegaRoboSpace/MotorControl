/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  usart.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.30;
历史版本:  无;
*********************************************************************************************/
#ifndef __USART_PHY_H
#define __USART_PHY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "msgescape.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/



/*******************************************宏定义********************************************/
#if UART1_REMAP
#define    USART1_TX_PIN           GPIO_Pin_6
#define    USART1_RX_PIN           GPIO_Pin_7
#define    USART1_GPIO             GPIOB
#else
#define    USART1_TX_PIN           GPIO_Pin_9
#define    USART1_RX_PIN           GPIO_Pin_10
#define    USART1_GPIO             GPIOA
#endif

#define    USART1_TX_DMA_CH        DMA1_Channel4
#define    USART1_RX_DMA_CH        DMA1_Channel5
#define    USART1_DR_BASE          (uint32_t)0x40013804
#define    USART1_BUFF_SIZE        1600
#define    USART1_START_OF_FRAME   FE_BEFORE_ESCAPE
#define    USART1_FRAME_LEN_MAX    0xFC    //FE和FD会进行转义，为了避免长度被转义所以最大为FC



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void USARTInit(void);
void USARTRecive(void);
void USARTSend(u8 *pData, u8 dataLen);
void UsartBuffDataProcess(void);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/