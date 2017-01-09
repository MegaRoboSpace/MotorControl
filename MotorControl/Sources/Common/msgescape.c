/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  msgescape.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.16;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "msgescape.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: EscapeMsgAndXor;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void EscapeMsg(u8 *pDestBuffer, u8 *pSrcBuffer, u8 *pLength)
{
    u8 i, j, u8Length = *pLength;    //j������Ϣ���Ȼ������
    u8 receiveByte;

    for (i = 0,j = 0; i < u8Length; i++) 
    {
        receiveByte = pSrcBuffer[i];

        if (receiveByte == 0xFE) //�������0xFE
        {
            pDestBuffer[j++] = FEFD_AFTER_ESCAPE_H;
            pDestBuffer[j++] = FE_AFTER_ESCAPE_L;

        }
        else if (receiveByte == 0xFD) //�������0xFD
        {
            pDestBuffer[j++] = FEFD_AFTER_ESCAPE_H;
            pDestBuffer[j++] = FD_AFTER_ESCAPE_L;
        }
        else
        {
            pDestBuffer[j++] = receiveByte;
        }
    }
    *pLength = j;
}


/*********************************************************************************************
�� �� ��: DeescapeMsgAndXorCheck;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
bool DeescapeMsgAndXorCheck(u8 *pSrcBuffer, u8 *plength)
{
    u8 i, j;
    u8 xorLen = *plength;
    u8 receiveByte, fcs = 0;

    for (i = 0, j = 0; i < xorLen; i++)    //j������Ϣ���Ȼ������
    {
        receiveByte = pSrcBuffer[i];

        fcs ^= receiveByte;    //���Ͷ˼������У��ֵ����ת��֮��

        if (receiveByte == FEFD_AFTER_ESCAPE_H)
        {
            i++;
            if (pSrcBuffer[i] == FE_AFTER_ESCAPE_L)
            {
                fcs ^= FE_AFTER_ESCAPE_L;
                receiveByte = FE_BEFORE_ESCAPE;
            }
            else if (pSrcBuffer[i] == FD_AFTER_ESCAPE_L)
            {
                fcs ^= FD_AFTER_ESCAPE_L;
                receiveByte = FD_BEFORE_ESCAPE;
            }
            else
            {
                return false;
            }
        }

        //fcs ^= receiveByte;
        pSrcBuffer[j++] = receiveByte;    //��ת��֮���ֵ����ԭ��Ϣ
    }

    *plength = j;
    
    return (fcs == 0);
}



/*******************************************�ļ�β********************************************/