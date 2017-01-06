/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtalgorithm.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.22;
历史版本:  无;
*********************************************************************************************/
#ifndef __PVT_ALGORITHM_H
#define __PVT_ALGORITHM_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "debug.h"
#include "datatype.h"
#include "stm32f10x_tim.h"
#include "systemparaverify.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/  



/***************************************常数和类型声明****************************************/



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void PvtResultCalc(WorkModeEnum workMode);
void PvtDebugMode(void);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/
