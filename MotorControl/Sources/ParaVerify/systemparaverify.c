/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  systemparaverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "systemparaverify.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SystemInfoStruct g_systemInfo;



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: SystemParaVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 SystemModeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(WorkModeEnum) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(WorkModeEnum *)pParaValue = WORK_NORMAL;
              break;
    
            case 1:
                *(WorkModeEnum *)pParaValue = WORK_UNIFORM;
              break;  
    
            case 2:
                *(WorkModeEnum *)pParaValue = WORK_POSITION;
              break; 
    
            case 3:
                *(WorkModeEnum *)pParaValue = WORK_TORQUE;
              break;      
    
            default:
                verifyResult = PARA_VERIFY_ERROR_TYPE;
              break;
        }        
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: SystemPowerOnVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 SystemPowerOnVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(PowerOnModeEnum) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(PowerOnModeEnum *)pParaValue = POWERON_DEFAULT;
              break;
    
            case 1:
                *(PowerOnModeEnum *)pParaValue = POWERON_LAST;
              break;      
    
            default:
                verifyResult = PARA_VERIFY_ERROR_TYPE;
              break;
        }        
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*******************************************�ļ�β********************************************/
