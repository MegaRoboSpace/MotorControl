/**********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  timer.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.08.22;
��ʷ�汾:  ��;
**********************************************************************************************/
#include "timer.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/
#define    LSI_FREQ       40000    //Hz



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: TIMInit;
ʵ�ֹ���:  
�������: ��;
�������: ��;
�� �� ֵ: ��;
*********************************************************************************************/
void TIMInit()
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    

    /*TIM4 Config Begin*****************************************************/
    //TIM4����Ϊʱ��Tick��ʱ����1ms�ж�һ��
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 36000 - 1;                              //������36000�����ʱ��պ�1ms
    TIM_TimeBaseStructure.TIM_Prescaler = 1;                                   //����Ԥ��Ƶ��72MHz / (1 + 1) = 36MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                    //����ʱ�ӷ�Ƶϵ��������Ƶ  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                //���ϼ������ģʽ  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
    //ʹ��TIM4����ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM4, ENABLE);
    /*TIM4 Config   End*****************************************************/
}


/*********************************************************************************************
�� �� ��: IWDGInit;
ʵ�ֹ���:  
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: �������Ź�ʱ��40KHz, ��λʱ�����Prescaler * Reload / LSI_FREQ;
*********************************************************************************************/
void IWDGInit(void)
{
    //Enables write access to IWDG_PR and IWDG_RLR registers
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    
    //Set prescaler value
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    
    //Set reload value
    //Reload Value = timeout(s) * LSI_FREQ / Prescaler
    IWDG_SetReload(LSI_FREQ / 32);
    
    //Download reload value to register
    IWDG_ReloadCounter();

    //Enable IWDG
    IWDG_Enable();
}


/*********************************************************************************************
�� �� ��: IWDGFeed;
ʵ�ֹ���:  
�������: ��;
�������: ��;
�� �� ֵ: ��;
*********************************************************************************************/
void IWDGFeed(void)  
{  
    IWDG_ReloadCounter();
}



/*******************************************�ļ�β********************************************/
