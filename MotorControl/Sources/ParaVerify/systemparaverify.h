/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  systemparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __SYSTEM_PARA_VERIFY_H
#define __SYSTEM_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/ 
#define    QUBELEY_SN_LEN    14



/***************************************��������������****************************************/
typedef enum
{
    WORK_NORMAL = 0,    //��ͨģʽ
    WORK_UNIFORM,       //����ģʽ
    WORK_POSITION,      //λ�÷���ģʽ
    WORK_TORQUE         //���ط���ģʽ
    
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
    u8               jointNum;       //�������ʱ�Ĺؽ���
    ProductModelEnum qubeleyModel;
    s8               qubeleySn[QUBELEY_SN_LEN];
    
}SystemInfoStruct;



/******************************************��������*******************************************/



/******************************************��������*******************************************/
u8 SystemModeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 SystemPowerOnVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/
