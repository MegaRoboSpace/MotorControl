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



/****************************************外部变量声明*****************************************/
extern volatile u64 g_systemMilliSecTick;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/



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
函 数 名: StimerInit;
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
函 数 名: StimerExamine;
实现功能: 检查定时器是否超时; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
bool StimerExamine(SoftTimerStr * thiss)
{
    s16 temp = 0;  

    if(!thiss->bUsed)
        return false;
        
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
实现功能: 启动定时器; 
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
实现功能: 关闭定时器; 
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



/*******************************************文件尾********************************************/
