/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  intfcparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __INTFC_PARA_VERIFY_H
#define __INTFC_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
typedef enum
{
    LINK_CAN,
    LINK_UART
    
}LinkTypeEnum;

typedef struct
{
    u8  idTypeIndex;
    u8  group;
    u8  baudIndex;    //�������±꣬��λ�����ã�ʵ��ʹ��ʱ�Ӳ����������и����±�ȡֵ
    u32 sendId;
    u32 targetId;
    u32 groupId;
    u32 radioId;
    
}CanIntfcStruct;

typedef struct
{
    u8  baudIndex;     //�������±꣬��λ�����ã�ʵ��ʹ��ʱ�Ӳ����������и����±�ȡֵ
    u8  wordLen :2;    //�����ֳ���
    u8  stopBit :2;    //ֹͣλ
    u8  parity  :2;    //У��λ
    u8  flowCtl :2;    //Ӳ��������
    
}UartIntfcStruct;

typedef struct
{
    LinkTypeEnum       linkType;      //��ǰʹ��CAN�ӿ�/RS232�ӿڽ�������
    CanIntfcStruct     canIntfc;
    UartIntfcStruct    uartIntfc;
    
}SystemInterfaceStruct;



/*******************************************�궨��********************************************/ 
#define    UART_BAUDRATE_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_FLOW_CTL_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_WORD_LEN_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_STOP_BIT_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_PARITY_NUM         10    //��������ֵ�ĸ�����Ӧ

#define    UART_BAUDRATE_115200    7
#define    UART_BAUDRATE_9600      2

#define    CAN_ID_TYPE_NUM         2     //��������ֵ�ĸ�����Ӧ
#define    CAN_BAUDRATE_NUM        8     //��������ֵ�ĸ�����Ӧ

#define    CAN_ID_TYPE_STD         0
#define    CAN_ID_TYPE_EXT         1



/******************************************��������*******************************************/



/******************************************��������*******************************************/
u8 UartBaudVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartWordLenVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartFlowCtlVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartParityVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 UartStopBitVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanSendIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanBaudVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanGroupVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanTargetIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanGroupIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 CanRadioIdVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 LinkParaVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/