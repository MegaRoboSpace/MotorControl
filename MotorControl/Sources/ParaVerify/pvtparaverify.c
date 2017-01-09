/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtparaverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "pvtparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern ParaLimitStruct g_paraLimit;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
PvtInfoStruct g_pvtInfo = {false, false, 0, PVT_SINGEL,
                           {{0, 0, 0},
                            {0.1274050015509044, 0.4042337149649688, 0.536361535}},
                           0, 0};



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: LinkParaVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtModeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(u8 *)pParaValue = PVT_SINGEL;
              break;

            case 1:
                *(u8 *)pParaValue = PVT_NCYCLE;
              break; 

            case 2:
                *(u8 *)pParaValue = PVT_INFINITY;
              break;

            case 3:
                *(u8 *)pParaValue = PVT_FIFO;
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
�� �� ��: PvtPositionVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtPositionVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtPosn)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtPosn)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: PvtSpeedVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtSpeed)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtSpeed)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: PvtTimeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtTimeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtTime)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtTime)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: PvtStartPointVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtStartPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtStartPoint)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtStartPoint)
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
�� �� ��: PvtEndPointVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtEndPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtEndPoint)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtEndPoint)
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
�� �� ��: PvtNcyclesVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtNcyclesVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtNcycles)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtNcycles)
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
�� �� ��: PvtWarnPointVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 PvtWarnPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.pvtWarnPoint)
        {
            if (tempValue >= g_paraLimit.downLimit.pvtWarnPoint)
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
�� �� ��: TrapzPositionVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 TrapzPositionVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.trapzPosn)
        {
            if (tempValue >= g_paraLimit.downLimit.trapzPosn)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*********************************************************************************************
�� �� ��: TrapzSpeedVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 TrapzSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.trapzSpeed)
        {
            if (tempValue >= g_paraLimit.downLimit.trapzSpeed)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}


/*********************************************************************************************
�� �� ��: TrapzTimeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 TrapzTimeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(f32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.trapzTime)
        {
            if (tempValue >= g_paraLimit.downLimit.trapzTime)
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
        verifyResult = PARA_VERIFY_ERROR_LEN;
    }

    return verifyResult;
}



/*******************************************�ļ�β********************************************/
