/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  intfcparaverify.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "intfcparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern ParaLimitStruct g_paraLimit;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SystemInterfaceStruct g_systemIntfc;

u32 g_uartBaudrate[UART_BAUDRATE_NUM] = { 4800,  7200,   9600,  14400, 19200, 
                                         38400, 57600, 115200, 128000, 4500000};
u16 g_uartWordLen[UART_WORD_LEN_NUM] = {USART_WordLength_8b, USART_WordLength_9b};
u16 g_uartFlowCtl[UART_FLOW_CTL_NUM] = {USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS,
                                        USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS};
u16 g_uartStopBit[UART_STOP_BIT_NUM] = {USART_StopBits_1, USART_StopBits_0_5, 
                                        USART_StopBits_2, USART_StopBits_1_5};
u16 g_uartParity[UART_PARITY_NUM]    = {USART_Parity_No, USART_Parity_Even, USART_Parity_Odd};


u8  g_canType[CAN_ID_TYPE_NUM] = {CAN_ID_STD, CAN_ID_EXT};

//��˳�����ζ�Ӧ�Ĳ�������1000��500��250��125��100��50��20��10kBps
u16 g_canPrescaler[CAN_BAUDRATE_NUM] = {6, 12, 24, 48, 60, 120, 300, 600};    



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: UartBaudVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 UartBaudVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < UART_BAUDRATE_NUM)
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
�� �� ��: UartWordLenVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 UartWordLenVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < UART_WORD_LEN_NUM)
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
�� �� ��: UartFlowCtlVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 UartFlowCtlVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < UART_FLOW_CTL_NUM)
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
�� �� ��: UartParityVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 UartParityVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < UART_PARITY_NUM)
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
�� �� ��: UartStopBitVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 UartStopBitVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < UART_STOP_BIT_NUM)
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
�� �� ��: CanTypeVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanTypeVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < CAN_ID_TYPE_NUM)
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
�� �� ��: CanSendIdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanSendIdVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8  verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.canSendId)
        {
            if (tempValue >= g_paraLimit.downLimit.canSendId)
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
�� �� ��: CanBaudVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanBaudVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue < CAN_BAUDRATE_NUM)
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
�� �� ��: CanGroupVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanGroupVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u8) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        if (tempValue <= g_paraLimit.upLimit.canGroup)
        {
            if (tempValue >= g_paraLimit.downLimit.canGroup)
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
�� �� ��: CanTargetIdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanTargetIdVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.canTargetId)
        {
            if (tempValue >= g_paraLimit.downLimit.canTargetId)
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
�� �� ��: CanGroupIdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanGroupIdVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.canGroupId)
        {
            if (tempValue >= g_paraLimit.downLimit.canGroupId)
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
�� �� ��: CanRadioIdVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 CanRadioIdVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u32 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(u32) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *(u32 *)pData;
        if (tempValue <= g_paraLimit.upLimit.canRadioId)
        {
            if (tempValue >= g_paraLimit.downLimit.canRadioId)
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
�� �� ��: LinkParaVerify;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
u8 LinkParaVerify(u8 dataLen, u8 *pData, void *pParaValue)
{
    u8 tempValue;
    u8 verifyResult = PARA_VERIFY_NO_ERROR;

    
    if (sizeof(LinkTypeEnum) == dataLen)    //������Ҫ��ȷ
    {
        tempValue = *pData;
        switch (tempValue)
        {
            case 0:
                *(LinkTypeEnum *)pParaValue = LINK_CAN;
              break;

            case 1:
                *(LinkTypeEnum *)pParaValue = LINK_UART;
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
