/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  cmdparse.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#ifndef __CMD_PARSE_H
#define __CMD_PARSE_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"



/****************************************外部变量声明*****************************************/



/***************************************常数和类型声明****************************************/
typedef enum
{
    CMD_LINK = 0,      //建立连接命令
    CMD_SYSTME,        //系统命令
    CMD_UART,          //RS232接口命令
    CMD_CAN,           //CAN接口命令   
    CMD_MOTOR,         //电机命令
    CMD_ENCODER,       //编码器命令    
    CMD_PVT,           //PVT命令
    CMD_TRAPZCURVE,    //梯形曲线命令     
    CMD_MOTION,        //运动命令
    CMD_OUTOFSTEP,     //失步命令   
    CMD_OTP,           //过温保护命令
    CMD_DSENSOR,       //数字传感器命令
    CMD_ASENSOR,       //模拟传感器命令  
    CMD_CALIBRATE,     //校准命令  
    CMD_UPDATE,        //升级命令  
    CMD_DEBUG,         //调试命令
    CMD_RESERVE
    
}CmdTypeEnum;

typedef enum
{
    LINKCMD_CAN = 0,
    LINKCMD_UART
    
}LinkCmdSubTypeEnum;

typedef struct
{
    CmdTypeEnum    mainType;      //主类型
    u8             subType;       //子类型
    u8             dataLen;       //数据长度
    u8             payload[0];    //数据内容
    
}CmdParseFrameStr;



/*******************************************宏定义********************************************/ 
#define    GET_CMD_PARSE_FRMAE_TOTAL_SIZE      dataLen  + sizeof(CmdParseFrameStr)



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
void CmdParseInit(void);
void CmdFrameSend(CmdTypeEnum cmdMainType, u8 cmdSubType, u8 dataLen, u8 *pData);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/