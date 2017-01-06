/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  can.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.01;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "canphy.h"
#include "intfcparaverify.h"



/****************************************外部变量声明*****************************************/
extern u8  g_canType[CAN_ID_TYPE_NUM];
extern u16 g_canPrescaler[CAN_BAUDRATE_NUM];
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: CANInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CANInit(void)
{
    u32 mask;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef      NVIC_InitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;
    CAN_InitTypeDef       CAN_InitStructure;


    //配置时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOB, ENABLE);

	//配置管脚(进行了重映射)
    GPIO_InitStructure.GPIO_Pin = CAN1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(CAN1_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(CAN1_GPIO, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    
    
    //配置CAN
    CAN_DeInit(CAN_SYSTEM_CAN_TYPE);
    CAN_StructInit(&CAN_InitStructure);

    CAN_InitStructure.CAN_TTCM = DISABLE;            //没有使能时间触发模式
    CAN_InitStructure.CAN_ABOM = DISABLE;            //没有使能自动离线管理
    CAN_InitStructure.CAN_AWUM = DISABLE;            //没有使能自动唤醒模式
    CAN_InitStructure.CAN_NART = DISABLE;            //没有使能非自动重传模式
    CAN_InitStructure.CAN_RFLM = DISABLE;            //没有使能接收FIFO锁定模式
    CAN_InitStructure.CAN_TXFP = DISABLE;            //没有使能发送FIFO优先级
    
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;    //CAN设置为正常模式
    
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;         //重新同步跳跃宽度1个时间单位
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;         //时间段1为3个时间单位
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;         //时间段2为2个时间单位

    CAN_InitStructure.CAN_Prescaler = g_canPrescaler[g_systemIntfc.canIntfc.baudIndex];

    CAN_Init(CAN_SYSTEM_CAN_TYPE, &CAN_InitStructure);

    //配置滤波器
    CAN_FilterInitStructure.CAN_FilterNumber = 0;

    //为了过滤出一组标识符，应该设置过滤器组工作在屏蔽位模式
    //为了过滤出一个标识符，应该设置过滤器组工作在标识符列表模式
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    
    //(STID[10:3])(STID[2:0]EXID[17:13])(EXID[12:5])(EXID[4:0]IDE RTR 0)
    CAN_FilterInitStructure.CAN_FilterIdHigh = ((g_systemIntfc.canIntfc.targetId << 3) >>16) & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterIdLow = (u16)(g_systemIntfc.canIntfc.targetId << 3) | g_canType[g_systemIntfc.canIntfc.idTypeIndex];

    mask = g_systemIntfc.canIntfc.targetId ^ 
           g_systemIntfc.canIntfc.groupId ^ 
           g_systemIntfc.canIntfc.radioId;
    mask = ~mask;
    mask <<= 3;
    mask |= 0x02;    //只接收数据帧，不接收远程帧 
    
    //(STID[10:3])(STID[2:0]EXID[17:13])(EXID[12:5])(EXID[4:0]IDE RTR 0)
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (mask >> 16) & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = mask & 0xFFFF;

    
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    //使能中断
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN_SYSTEM_CAN_TYPE, CAN_IT_FMP0, ENABLE);    //使能FIFO0消息挂号中断
}


/*********************************************************************************************
函 数 名: CANSend;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void CANSend(u32 canId, u8 canRtr, u8 dataLen, u8 *pData)
{
    CanTxMsg TxMessage;
    u8 i;


    TxMessage.StdId = g_systemIntfc.canIntfc.sendId;	//标准标识符
    TxMessage.ExtId = g_systemIntfc.canIntfc.sendId;    //扩展标识符
    
    TxMessage.RTR = canRtr;     //为数据帧: CAN_RTR_DATA/CAN_RTR_REMOTE
    
    TxMessage.IDE = g_canType[g_systemIntfc.canIntfc.idTypeIndex];     //使用扩展标识符: CAN_ID_EXT/CAN_ID_STD

    if (dataLen <= 8)
    {
        TxMessage.DLC = dataLen;	//数据长度
        for (i = 0;i < dataLen;i++)
        {
            TxMessage.Data[i] = *pData++;
        }
        
        CAN_Transmit(CAN_SYSTEM_CAN_TYPE, &TxMessage); //发送数据
    }
}



/*******************************************文件尾********************************************/