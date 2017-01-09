/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  can.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.01;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "canphy.h"
#include "intfcparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern u8  g_canType[CAN_ID_TYPE_NUM];
extern u16 g_canPrescaler[CAN_BAUDRATE_NUM];
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: CANInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CANInit(void)
{
    u32 mask;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef      NVIC_InitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;
    CAN_InitTypeDef       CAN_InitStructure;


    //����ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOB, ENABLE);

	//���ùܽ�(��������ӳ��)
    GPIO_InitStructure.GPIO_Pin = CAN1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(CAN1_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(CAN1_GPIO, &GPIO_InitStructure);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    
    
    //����CAN
    CAN_DeInit(CAN_SYSTEM_CAN_TYPE);
    CAN_StructInit(&CAN_InitStructure);

    CAN_InitStructure.CAN_TTCM = DISABLE;            //û��ʹ��ʱ�䴥��ģʽ
    CAN_InitStructure.CAN_ABOM = DISABLE;            //û��ʹ���Զ����߹���
    CAN_InitStructure.CAN_AWUM = DISABLE;            //û��ʹ���Զ�����ģʽ
    CAN_InitStructure.CAN_NART = DISABLE;            //û��ʹ�ܷ��Զ��ش�ģʽ
    CAN_InitStructure.CAN_RFLM = DISABLE;            //û��ʹ�ܽ���FIFO����ģʽ
    CAN_InitStructure.CAN_TXFP = DISABLE;            //û��ʹ�ܷ���FIFO���ȼ�
    
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;    //CAN����Ϊ����ģʽ
    
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;         //����ͬ����Ծ���1��ʱ�䵥λ
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;         //ʱ���1Ϊ3��ʱ�䵥λ
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;         //ʱ���2Ϊ2��ʱ�䵥λ

    CAN_InitStructure.CAN_Prescaler = g_canPrescaler[g_systemIntfc.canIntfc.baudIndex];

    CAN_Init(CAN_SYSTEM_CAN_TYPE, &CAN_InitStructure);

    //�����˲���
    CAN_FilterInitStructure.CAN_FilterNumber = 0;

    //Ϊ�˹��˳�һ���ʶ����Ӧ�����ù������鹤��������λģʽ
    //Ϊ�˹��˳�һ����ʶ����Ӧ�����ù������鹤���ڱ�ʶ���б�ģʽ
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
    mask |= 0x02;    //ֻ��������֡��������Զ��֡ 
    
    //(STID[10:3])(STID[2:0]EXID[17:13])(EXID[12:5])(EXID[4:0]IDE RTR 0)
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (mask >> 16) & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = mask & 0xFFFF;

    
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    //ʹ���ж�
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN_SYSTEM_CAN_TYPE, CAN_IT_FMP0, ENABLE);    //ʹ��FIFO0��Ϣ�Һ��ж�
}


/*********************************************************************************************
�� �� ��: CANSend;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void CANSend(u32 canId, u8 canRtr, u8 dataLen, u8 *pData)
{
    CanTxMsg TxMessage;
    u8 i;


    TxMessage.StdId = g_systemIntfc.canIntfc.sendId;	//��׼��ʶ��
    TxMessage.ExtId = g_systemIntfc.canIntfc.sendId;    //��չ��ʶ��
    
    TxMessage.RTR = canRtr;     //Ϊ����֡: CAN_RTR_DATA/CAN_RTR_REMOTE
    
    TxMessage.IDE = g_canType[g_systemIntfc.canIntfc.idTypeIndex];     //ʹ����չ��ʶ��: CAN_ID_EXT/CAN_ID_STD

    if (dataLen <= 8)
    {
        TxMessage.DLC = dataLen;	//���ݳ���
        for (i = 0;i < dataLen;i++)
        {
            TxMessage.Data[i] = *pData++;
        }
        
        CAN_Transmit(CAN_SYSTEM_CAN_TYPE, &TxMessage); //��������
    }
}



/*******************************************�ļ�β********************************************/