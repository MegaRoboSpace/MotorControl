/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  softtimer.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.11;
历史版本:  无;
*********************************************************************************************/
#ifndef __SOFT_TIMER_H
#define __SOFT_TIMER_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/



/***************************************常数和类型声明****************************************/
typedef void ( *timeOutFunc)(void);

typedef struct
{
  bool         bUsed;
  u16          periodMS;
  u16          timeoutMS;
  timeOutFunc  timerOut;
  
}SoftTimerStr;


/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void Delay(u32 count);
void StimerInit(SoftTimerStr *thiss, u16 interval, timeOutFunc fTimerProcessor);
bool StimerExamine(SoftTimerStr * thiss);
void StimerAdd(SoftTimerStr *ptSoftTimer);
bool StimerDelete(SoftTimerStr *ptSoftTimer);
void StimerAllCheck(void);
void StimerAllInit(void);
void PvtCalcEndTimerOutCB(void);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/