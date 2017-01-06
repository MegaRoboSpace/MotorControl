/**********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  timer.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.22;
历史版本:  无;
**********************************************************************************************/
#include "timer.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/
#define    LSI_FREQ       40000    //Hz



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: TIMInit;
实现功能:  
输入参数: 无;
输出参数: 无;
返 回 值: 无;
*********************************************************************************************/
void TIMInit()
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    

    /*TIM4 Config Begin*****************************************************/
    //TIM4设置为时钟Tick定时器，1ms中断一次
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 36000 - 1;                              //计数到36000溢出，时间刚好1ms
    TIM_TimeBaseStructure.TIM_Prescaler = 1;                                   //设置预分频：72MHz / (1 + 1) = 36MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                    //设置时钟分频系数：不分频  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                //向上计数溢出模式  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
    //使能TIM4溢出中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM4, ENABLE);
    /*TIM4 Config   End*****************************************************/
}


/*********************************************************************************************
函 数 名: IWDGInit;
实现功能:  
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 独立看门狗时钟40KHz, 复位时间等于Prescaler * Reload / LSI_FREQ;
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
函 数 名: IWDGFeed;
实现功能:  
输入参数: 无;
输出参数: 无;
返 回 值: 无;
*********************************************************************************************/
void IWDGFeed(void)  
{  
    IWDG_ReloadCounter();
}



/*******************************************文件尾********************************************/
