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



/****************************************�ⲿ��������*****************************************/
extern SystemIntfcStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
u32 g_canType[CAN_ID_TYPE_NUM] = {CAN_ID_STD, CAN_ID_EXT};

//��˳�����ζ�Ӧ�Ĳ�������1000��500��250��125��100��50��20��10kBps
u16 g_canPrescaler[CAN_BAUDRATE_NUM] = {6, 12, 24, 48, 60, 120, 300, 600}; 



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
    u32 canType = g_canType[g_systemIntfc.canIntfc.idType];
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

    CAN_InitStructure.CAN_Prescaler = g_canPrescaler[g_systemIntfc.canIntfc.baud];

    CAN_Init(CAN_SYSTEM_CAN_TYPE, &CAN_InitStructure);

    //�����˲���0
    CAN_FilterInitStructure.CAN_FilterNumber = 0;

    //Ϊ�˹��˳�һ���ʶ����Ӧ�����ù������鹤��������λģʽ
    //Ϊ�˹��˳�һ����ʶ����Ӧ�����ù������鹤���ڱ�ʶ���б�ģʽ
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    
    //(STID[10:3])(STID[2:0]EXID[17:13])(EXID[12:5])(EXID[4:0]IDE RTR 0)
    CAN_FilterInitStructure.CAN_FilterIdHigh = (u16)(((g_systemIntfc.canIntfc.targetId << 3) >>16) & 0xFFFF);
    CAN_FilterInitStructure.CAN_FilterIdLow = (u16)((g_systemIntfc.canIntfc.targetId << 3) | canType);
    
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (u16)(((g_systemIntfc.canIntfc.groupId << 3) >>16) & 0xFFFF);
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = (u16)((g_systemIntfc.canIntfc.groupId << 3) | canType);

    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_SYSTEM_CAN_FIFO;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    //�����˲���1
    CAN_FilterInitStructure.CAN_FilterNumber = 1;

    //Ϊ�˹��˳�һ���ʶ����Ӧ�����ù������鹤��������λģʽ
    //Ϊ�˹��˳�һ����ʶ����Ӧ�����ù������鹤���ڱ�ʶ���б�ģʽ
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    
    //(STID[10:3])(STID[2:0]EXID[17:13])(EXID[12:5])(EXID[4:0]IDE RTR 0)
    CAN_FilterInitStructure.CAN_FilterIdHigh = (u16)(((g_systemIntfc.canIntfc.radioId << 3) >>16) & 0xFFFF);
    CAN_FilterInitStructure.CAN_FilterIdLow = (u16)((g_systemIntfc.canIntfc.radioId << 3) | canType);
    
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (u16)(((g_systemIntfc.canIntfc.radioId << 3) >>16) & 0xFFFF);
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = (u16)((g_systemIntfc.canIntfc.radioId << 3) | canType);

    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_SYSTEM_CAN_FIFO;
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
    
    TxMessage.IDE = g_canType[g_systemIntfc.canIntfc.idType];     //ʹ����չ��ʶ��: CAN_ID_EXT/CAN_ID_STD

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