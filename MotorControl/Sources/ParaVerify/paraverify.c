/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  paraverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
ParaLimitStruct g_paraLimit;



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: ParaLimitInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void ParaLimitInit(void)
{    
    //����ϵͳ�ͺŶԲ��������޽��и�ֵ
    /*switch (cmdMainType)
    {
        case 0:
          break;

        default:
          break;
    }*/
    
    //����
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

    
    
    //����
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



/*******************************************�ļ�β********************************************/
