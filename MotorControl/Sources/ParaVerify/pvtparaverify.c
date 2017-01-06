/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtparaverify.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#include "pvtparaverify.h"



/****************************************外部变量声明*****************************************/
extern ParaLimitStruct g_paraLimit;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
PvtInfoStruct g_pvtInfo = {false, false, 0, PVT_SINGEL,
                           {{0, 0, 0},
                            {0.1274050015509044, 0.4042337149649688, 0.536361535}},
                           0, 0};



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: LinkParaVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtModeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //长度先要正确
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
函 数 名: PvtPositionVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtPositionVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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
函 数 名: PvtSpeedVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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
函 数 名: PvtTimeVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtTimeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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
函 数 名: PvtStartPointVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtStartPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //长度先要正确
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
函 数 名: PvtEndPointVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtEndPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //长度先要正确
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
函 数 名: PvtNcyclesVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtNcyclesVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //长度先要正确
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
函 数 名: PvtWarnPointVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 PvtWarnPointVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //长度先要正确
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
函 数 名: TrapzPositionVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 TrapzPositionVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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
函 数 名: TrapzSpeedVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 TrapzSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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
函 数 名: TrapzTimeVerify;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
u8 TrapzTimeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    f32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(f32) == dataLen)    //长度先要正确
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



/*******************************************文件尾********************************************/
