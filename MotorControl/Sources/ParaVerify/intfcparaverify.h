/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  intfcparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __INTFC_PARA_VERIFY_H
#define __INTFC_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    LINK_CAN,
    LINK_UART
    
}LinkTypeEnum;

typedef struct
{
    u8  idTypeIndex;
    u8  group;
    u8  baudIndex;    //波特率下标，上位机设置，实际使用时从波特率数组中根据下标取值
    u32 sendId;
    u32 targetId;
    u32 groupId;
    u32 radioId;
    
}CanIntfcStruct;

typedef struct
{
    u8  baudIndex;     //波特率下标，上位机设置，实际使用时从波特率数组中根据下标取值
    u8  wordLen :2;    //数据字长度
    u8  stopBit :2;    //停止位
    u8  parity  :2;    //校验位
    u8  flowCtl :2;    //硬件流控制
    
}UartIntfcStruct;

typedef struct
{
    LinkTypeEnum       linkType;      //当前使用CAN接口/RS232接口进行连接
    CanIntfcStruct     canIntfc;
    UartIntfcStruct    uartIntfc;
    
}SystemInterfaceStruct;



/*******************************************宏定义********************************************/ 
#define    UART_BAUDRATE_NUM       10    //跟数组中值的个数对应
#define    UART_FLOW_CTL_NUM       10    //跟数组中值的个数对应
#define    UART_WORD_LEN_NUM       10    //跟数组中值的个数对应
#define    UART_STOP_BIT_NUM       10    //跟数组中值的个数对应
#define    UART_PARITY_NUM         10    //跟数组中值的个数对应

#define    UART_BAUDRATE_115200    7
#define    UART_BAUDRATE_9600      2

#define    CAN_ID_TYPE_NUM         2     //跟数组中值的个数对应
#define    CAN_BAUDRATE_NUM        8     //跟数组中值的个数对应

#define    CAN_ID_TYPE_STD         0
#define    CAN_ID_TYPE_EXT         1



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
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



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/