/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  motorparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __MOTOR_PARA_VERIFY_H
#define __MOTOR_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/***************************************��������������****************************************/
typedef enum
{
    MOTOR_42,
    MOTOR_57
    
}MotorTypeEnum;

typedef enum
{
    ECCHAN_1,   //��ͨ��
    ECCHAN_3    //��ͨ��
    
}EncoderChanEnum;

typedef enum
{
    ENCODER_NONE,    //û�б�����
    ENCODER_INC,     //����ʽ
    ENCODER_ABS      //����ʽ
    
}EncoderTypeEnum;

typedef struct
{
    EncoderTypeEnum type;
    EncoderChanEnum chanNum;
    u16             lineNum;
    f32             linePerRadian;    //ÿ�����ϵ��������������������������2��
      
}EncoderInfoStruct;

typedef struct
{
    u8                   gearRatio;
    MotorTypeEnum        motorType;
    u8                   stepsIndex;
    u8                   microStepsIndex;
    u32                  peakSpeed;
    u32                  totalSteps;    //����microSteps * steps
    EncoderInfoStruct    encoderInfo;
      
}MotorInfoStruct;



/*******************************************�궨��********************************************/ 



/******************************************��������*******************************************/



/******************************************��������*******************************************/
u8 MotorMicroStepsVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorGearRatioVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorStepAngleVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorPeakSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 MotorTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderLineNumVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderChanNumVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 EncoderTypeVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/