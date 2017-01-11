/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  sensorparaverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "sensorparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern ParaLimitStruct  g_paraLimit;
extern SystemInfoStruct g_systemInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: OtpStateVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 OtpStateVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(bool *)pParaValue = false;
              break;

            case 1:
                *(bool *)pParaValue = true;
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

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: OtpThresholdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 OtpThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8  verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u8 *)pData;
        if (tempValue <= g_paraLimit.upLimit.otpThr)
        {
            if (tempValue >= g_paraLimit.downLimit.otpThr)
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

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: OtpResponseVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 OtpResponseVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(ResponseTypeEnum) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(ResponseTypeEnum *)pParaValue = RESPONSE_NONE;
              break;
    
            case 1:
                *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARM;
              break;  
    
            case 2:
                *(ResponseTypeEnum *)pParaValue = RESPONSE_STOP;
              break; 
    
            case 3:
                *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARMSTOP;
              break;  
    
            case 4:
                *(ResponseTypeEnum *)pParaValue = RESPONSE_RUN;
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

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: DsensorStateVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 DsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8 tempIndex;
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(u8) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *pData;
            switch (tempValue)
            {
                case 0:
                    *(bool *)pParaValue = false;
                  break;

                case 1:
                    *(bool *)pParaValue = true;
                  break;       

                default:
                    verifyResult = PARA_VERIFY_ERROR_TYPE;
                  break;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: DsensorTypeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 DsensorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8 tempIndex;
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(TriggerTypeEnum) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *pData;
            switch (tempValue)
            {
                case 0:
                    *(TriggerTypeEnum *)pParaValue = DTYPE_RISE;
                  break;
        
                case 1:
                    *(TriggerTypeEnum *)pParaValue = DTYPE_FALL;
                  break;  
        
                case 2:
                    *(TriggerTypeEnum *)pParaValue = DTYPE_HIGH;
                  break; 
        
                case 3:
                    *(TriggerTypeEnum *)pParaValue = DTYPE_LOW;
                  break;      
        
                default:
                    verifyResult = PARA_VERIFY_ERROR_TYPE;
                  break;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: DsensorResponseVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 DsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8 tempIndex;
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(ResponseTypeEnum) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *pData;
            switch (tempValue)
            {
                case 0:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_NONE;
                  break;
        
                case 1:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARM;
                  break;  
        
                case 2:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_STOP;
                  break; 
        
                case 3:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARMSTOP;
                  break;  
        
                case 4:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_RUN;
                  break;      
        
                default:
                    verifyResult = PARA_VERIFY_ERROR_TYPE;
                  break;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: AsensorStateVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 AsensorStateVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8 tempIndex;
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(u8) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *pData;
            switch (tempValue)
            {
                case 0:
                    *(bool *)pParaValue = false;
                  break;

                case 1:
                    *(bool *)pParaValue = true;
                  break;       

                default:
                    verifyResult = PARA_VERIFY_ERROR_TYPE;
                  break;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: AsensorThresholdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 AsensorThresholdVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8  tempIndex;
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(f32) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *(f32 *)pData;
            if (tempValue <= g_paraLimit.upLimit.asensorThr)
            {
                if (tempValue >= g_paraLimit.downLimit.asensorThr)
                {
                    *(f32 *)pParaValue = tempValue;
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
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: AsensorResponseVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 AsensorResponseVerify(u8 dataLen, u8 *pData, void *pParaValue, u8 *pIndex)
{
    u8 tempIndex;
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if ((sizeof(ResponseTypeEnum) + sizeof(u8)) == dataLen)    //�����ĳ��ȼ����±�ĳ���
    {
        tempIndex = *pData++;
        if (tempIndex < DIGIT_SENSOR_NUM)
        {
            *pIndex = tempIndex;
            tempValue = *pData;
            switch (tempValue)
            {
                case 0:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_NONE;
                  break;
        
                case 1:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARM;
                  break;  
        
                case 2:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_STOP;
                  break; 
        
                case 3:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_ALARMSTOP;
                  break;  
        
                case 4:
                    *(ResponseTypeEnum *)pParaValue = RESPONSE_RUN;
                  break;      
        
                default:
                    verifyResult = PARA_VERIFY_ERROR_TYPE;
                  break;
            }
        }
        else
        {
            verifyResult = PARA_VERIFY_ERROR_INDEX;
        }
    }
    else
    {
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    g_systemInfo.errorCode[ERROR_CODE_INDEX_PARA_VERIFY] = verifyResult;

    return verifyResult;
}



/*******************************************�ļ�β********************************************/
