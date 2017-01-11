/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  paraverify.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
ParaLimitStruct g_paraLimit;



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: ParaLimitInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void ParaLimitInit(void)
{    
    //根据系统型号对参数上下限进行赋值
    /*switch (cmdMainType)
    {
        case 0:
          break;

        default:
          break;
    }*/
    
    //上限
    g_paraLimit.upLimit.otpThr = 150;
    g_paraLimit.upLimit.canGroup = 200;
    g_paraLimit.upLimit.canSendId = 0x1FFFFFFF;
    g_paraLimit.upLimit.canTargetId = 0x1FFFFFFF;
    g_paraLimit.upLimit.canGroupId = 0x1FFFFFFF;
    g_paraLimit.upLimit.canRadioId = 0x1FFFFFFF;
    g_paraLimit.upLimit.motorGearRatio = 250;
    g_paraLimit.upLimit.motorPeakSpeed = 1024000;
    g_paraLimit.upLimit.pvtStartPoint = PVT_POINT_BUFFER_SIZE - 1;
    g_paraLimit.upLimit.pvtEndPoint = PVT_POINT_BUFFER_SIZE - 1;
    g_paraLimit.upLimit.pvtWarnPoint = PVT_POINT_BUFFER_SIZE - 1;
    g_paraLimit.upLimit.pvtPosn = 500000.0;
    g_paraLimit.upLimit.pvtSpeed = 1024000.0;
    g_paraLimit.upLimit.pvtTime = 500000.0;
    g_paraLimit.upLimit.trapzPosn = 500000.0;
    g_paraLimit.upLimit.trapzSpeed = 1024000.0;
    g_paraLimit.upLimit.trapzTime = 500000.0;
    g_paraLimit.upLimit.motionEmgc = 500000.0;
    g_paraLimit.upLimit.outOfStepNum = 1024000;   
    g_paraLimit.upLimit.asensorThr = 10.0;
    g_paraLimit.upLimit.motionMaxSpeed = 1024000;
    g_paraLimit.upLimit.motionMaxPosn = 500000;
    g_paraLimit.upLimit.motionMaxTorque = 500000;

    
    
    //下限
    g_paraLimit.downLimit.otpThr = 0;
    g_paraLimit.downLimit.canGroup = 0;
    g_paraLimit.downLimit.canSendId = 0;
    g_paraLimit.downLimit.canTargetId = 0;
    g_paraLimit.downLimit.canGroupId = 0;
    g_paraLimit.downLimit.canRadioId = 0;
    g_paraLimit.downLimit.motorGearRatio = 0;
    g_paraLimit.downLimit.motorPeakSpeed = 0;
    g_paraLimit.downLimit.pvtStartPoint = 0;
    g_paraLimit.downLimit.pvtEndPoint = 0;
    g_paraLimit.downLimit.pvtWarnPoint = 0;
    g_paraLimit.downLimit.pvtPosn = 0;
    g_paraLimit.downLimit.pvtSpeed = 0;
    g_paraLimit.downLimit.pvtTime = 0;
    g_paraLimit.downLimit.trapzPosn = 0;
    g_paraLimit.downLimit.trapzSpeed = 0;
    g_paraLimit.downLimit.trapzTime = 0;
    g_paraLimit.downLimit.motionEmgc = 0;
    g_paraLimit.downLimit.outOfStepNum = 0;   
    g_paraLimit.downLimit.asensorThr = 0;
    g_paraLimit.downLimit.motionMinSpeed = 0;
    g_paraLimit.downLimit.motionMinPosn = 0;
    g_paraLimit.downLimit.motionMinTorque = 0;
}



/*******************************************文件尾********************************************/
