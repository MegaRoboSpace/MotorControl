/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motorparaverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "motorparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern ParaLimitStruct g_paraLimit;



/*****************************************�ֲ��궨��******************************************/
#define    MOTOR_MICRO_STEPS_INDEX_NUM    9
#define    MOTOR_STEPS_INDEX_NUM          9
#define    MOTOR_TYPE_INDEX_NUM           2



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
MotorInfoStruct g_motorInfo;



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: MotorMicroStepsVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 MotorMicroStepsVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < MOTOR_MICRO_STEPS_INDEX_NUM)
        {
            *(u8 *)pParaValue = tempValue;
        }
        else
        {
            verifyResult = PARA_VERIFY_GREAT_UPER_LIMIT;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: MotorGearRatioVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 MotorGearRatioVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue <= g_paraLimit.upLimit.motorGearRatio)
        {
            if (tempValue >= g_paraLimit.downLimit.motorGearRatio)
            {
                *(u8 *)pParaValue = tempValue;
            }
            else
            {
                verifyResult = PARA_VERIFY_LESS_LOWER_LIMIT;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_GREAT_UPER_LIMIT;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: MotorStepAngleVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 MotorStepAngleVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < MOTOR_STEPS_INDEX_NUM)
        {
            *(u8 *)pParaValue = tempValue;
        }
        else
        {
            verifyResult = PARA_VERIFY_GREAT_UPER_LIMIT;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: MotorPeakSpeedVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 MotorPeakSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.motorPeakSpeed)
        {
            if (tempValue >= g_paraLimit.downLimit.motorPeakSpeed)
            {
                *(u32 *)pParaValue = tempValue;
            }
            else
            {
                verifyResult = PARA_VERIFY_LESS_LOWER_LIMIT;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_GREAT_UPER_LIMIT;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: MotorTypeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 MotorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < MOTOR_TYPE_INDEX_NUM)
        {
            *(u8 *)pParaValue = tempValue;
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_TYPE;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: EncoderLineNumVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 EncoderLineNumVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u16 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u16 *)pData;
        if (tempValue <= g_paraLimit.upLimit.encoderLineNum)
        {
            if (tempValue >= g_paraLimit.downLimit.encoderLineNum)
            {
                *(u16 *)pParaValue = tempValue;
            }
            else
            {
                verifyResult = PARA_VERIFY_LESS_LOWER_LIMIT;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_GREAT_UPER_LIMIT;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: EncoderChanNumVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 EncoderChanNumVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(EncoderChanEnum *)pParaValue = ECCHAN_1;
              break;
    
            case 1:
                *(EncoderChanEnum *)pParaValue = ECCHAN_3;
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
�� �� ��: EncoderTypeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 EncoderTypeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u16) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(EncoderTypeEnum *)pParaValue = ENCODER_INC;
              break;
    
            case 1:
                *(EncoderTypeEnum *)pParaValue = ENCODER_ABS;
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
