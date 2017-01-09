/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtparaverify.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.19;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __PVT_PARA_VERIFY_H
#define __PVT_PARA_VERIFY_H



/******************************************�����ļ�*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************�ⲿ��������*****************************************/



/*******************************************�궨��********************************************/ 
#define    PVT_POINT_BUFFER_SIZE    256



/***************************************��������������****************************************/
typedef enum
{
    PVT_SINGEL,
    PVT_NCYCLE,
    PVT_INFINITY,
    PVT_FIFO
    
}PvtModeEnum;

typedef enum
{
    FORWARD = 0,
    REVERSE
    
}DirectionStruct;

typedef struct
{
    f32 position;
    f32 speed;
    f32 time;
      
}PvtPointStruct;

typedef struct
{
    bool           bRewind  :1;
    bool           bCalcEnd :1;    //�Ƿ�����������������������������������ͼ������������ֱ���������ظ�
    u8             reserve  :6;
    
    PvtModeEnum    pvtMode;
    PvtPointStruct pvtPoint[PVT_POINT_BUFFER_SIZE];
    u16            headPoint;      //Buffer����Ч����ʼ�㣬�������Чָ���ǻ�û�м���ĵ�
    u16            tailPoint;      //Buffer����Ч����ֹ�㣬�������Чָ���ǻ�û�м���ĵ�
    u16            remainPoint;    //��ǰPVT_POINT_BUFFER�л��ж���ʣ��ռ���Դ��PVT����
    u16            outputPoint;    //��ǰ���������PVT������Buffer�е�λ������
    
    u16            startPoint;     //��ʼ(����)����ĵ㣬ѭ��������ģʽ��ʹ��
    u16            endPoint;       //ֹͣ(����)����ĵ㣬ѭ��������ģʽ��ʹ��
    u32            ncycle;         //ѭ��������ѭ��ģʽ��ʹ��
    u16            warnPoint;      //FIFOģʽ��ʣ��δ���PVT�������ޣ����ڴ�ֵ������λ�����;���

    u32             fpgaPwmClock;   //FPGA PWM��ʱ��
    f32             startPosition;  //PVT��ĳ�ʼλ��
    u32             targetStep;     //��ǰҪ��ȡ�Ĳ�����ÿ��PVT List��ʼ����1
    f32             lastStepSpeed;  //��һ�����ٶȣ�ʵ�ʴ洢����ʱ��
    f32             lastStepTime;   //��һ�������0ʱ�̵�ʱ��(PVT List��һ�����ʱ����Զ��0ʱ��)
    
    u32             targetLine;     //��ǰҪ��ȡ��������ÿ��PVT List��ʼ����1
    f32             lastLineSpeed;  //��һ�ߵ��ٶȣ�ʵ�ʴ洢����ʱ��
    f32             lastLineTime;   //��һ�������0ʱ�̵�ʱ��(PVT List��һ�����ʱ����Զ��0ʱ��)
    f32             remainLine;     //����������ʱ��β��������
    
    f32             errorTime;      //���ʱ�䣬��һ��֮���ʱ��ֵ
    DirectionStruct lastStepDir;    //��һ���ķ���
      
}PvtInfoStruct;



/******************************************��������*******************************************/



/******************************************��������*******************************************/
u8 PvtModeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtPositionVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtTimeVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtStartPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtEndPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtNcyclesVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 PvtWarnPointVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzPositionVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzSpeedVerify(u8 dataLen, u8 *pData, void *pParaValue);
u8 TrapzTimeVerify(u8 dataLen, u8 *pData, void *pParaValue);



/*****************************************ͷ�ļ�����******************************************/
#endif
/*******************************************�ļ�β********************************************/