/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  systemparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __SYSTEM_PARA_VERIFY_H
#define __SYSTEM_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/ 
#define    QUBELEY_SN_LEN    14



/***************************************常数和类型声明****************************************/
typedef enum
{
    WORK_NORMAL = 0,    //普通模式
    WORK_UNIFORM,       //匀速模式
    WORK_POSITION,      //位置反馈模式
    WORK_TORQUE         //力矩反馈模式
    
}WorkModeEnum;

typedef enum
{
    POWERON_DEFAULT = 0,    //
    POWERON_LAST,           //
    
}PowerOnModeEnum;

typedef enum
{
    MODEL_SINGEL,
    MODEL_MULTI
    
}ProductModelEnum;

typedef struct
{
    u32              systemInfo;
    u32              errorCode;
    u32              version;
    WorkModeEnum     workMode;
    PowerOnModeEnum  powerOn;
    u8               jointNum;       //多轴控制时的关节数
    ProductModelEnum qubeleyModel;
    s8               qubeleySn[QUBELEY_SN_LEN];
    
}SystemInfoStruct;



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
u8 SystemModeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 SystemPowerOnVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/
