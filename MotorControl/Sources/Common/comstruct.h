/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  comStruct.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2017.01.10;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __COM_STRUCT_H
#define __COM_STRUCT_H

#include "comEnum.h"



/***************************************��������������****************************************/
/*-------------��Buffer�ṹ��-------------*/
typedef struct 
{
    bool bNotEmpty    :1;      //�Ƿ�������
    bool bRewind      :1;      //�Ƿ����
    bool bAlmostFull  :1;      //�Ƿ������
    u8   u8Reverse    :5;      //����
    u16  bufferSize;
    u16  headOffset;
    u16  tailOffset;
    u16  dataTailOffset;       //��Ч���ݵ�β��
    u16  reserveMemorySize;    
    u8   *pBuffer;
    
}StreamBufferStr;

/*-------------����֡��ʽ�ṹ��-------------*/
typedef struct
{
    CmdTypeEnum  mainType;      //����������
    u8           subType;       //����������
    u8           dataLen;       //���ݳ���
    u8           payload[0];    //֡����
    
}CmdParseFrameStr;

/*-------------��ʱ���ṹ��-------------*/
typedef struct
{
  bool         bUsed;        //�Ƿ�����
  u16          periodMS;     //��ʱʱ��
  u64          timeoutMS;    //��ʱʱ��
  timeOutFunc  timerOut;     //��ʱ�ص�����
  
}SoftTimerStr;

/*-----------CAN Phy��֡��ʽ�ṹ��-----------*/
typedef struct
{    
    u32 canID;         //CANID
    u8  frameLen;      //֡���ȣ�����ID
    u8  payload[0];    //֡����
    
}CanPhyFrameStr;

/*-----------UART Phy��֡��ʽ�ṹ��-----------*/
typedef struct
{    
    u8 SOF;           //Start of frame
    u8 frameLen;      //֡���ȣ�����SOF������
    u8 xorValue;      //���У��ֵ
    u8 payload[0];    //֡����
    
}UartPhyFrameStr;

/*-------------CAN�ӿڽṹ��-------------*/
typedef struct
{
    CanTypeEnum  idType;    //����A��B
    
    u8  group;
    CanBaudEnum  baud;      //������
    u32 sendId;
    u32 targetId;
    u32 groupId;
    u32 radioId;
    
}CanIntfcStruct;

/*-------------UART�ӿڽṹ��------------*/
typedef struct
{
    UartBaudEnum baud;       //������
    WordLenEnum  wordLen;    //���ݳ���
    StopBitEnum  stopBit;    //ֹͣλ
    ParityEnum   parity;     //У�鷽ʽ
    FlowCtlEnum  flowCtl;    //������
    
}UartIntfcStruct;

/*-----------ϵͳ�ӿڽṹ��-------------*/
typedef struct
{
    LinkTypeEnum       linkType;      //�ظ�����ʱʹ��CAN����UART
    CanIntfcStruct     canIntfc;
    UartIntfcStruct    uartIntfc;
    
}SystemIntfcStruct;

/*-------------PVT��ṹ��-------------*/
typedef struct
{
    f32 position;    //λ��
    f32 speed;       //�ٶ�
    f32 time;        //ʱ��
      
}PvtPointStruct;

/*-------------PVT���ݽṹ��-------------*/
typedef struct
{
    bool bRewind  :1;    //PVT��Buffer�Ƿ����
    bool bCalcEnd :1;    //�����������Ҫ�ϱ���������PC
    u8   reserve  :6;    //����
    
    PvtModeEnum    pvtMode;                            //PVT����ģʽ
    PvtPointStruct pvtPoint[PVT_POINT_BUFFER_SIZE];    //PVT������
    
    u16 headPoint;      //Buffer����Ч���ݵ���ʼ�㣬��Чָ���ǻ�δ������ĵ�
    u16 tailPoint;      //Buffer����Ч���ݵ���ֹ�㣬��Чָ���ǻ�δ������ĵ�
    u16 remainPoint;    //Bufferʣ���д��ĵ���
    u16 outputPoint;    //��ǰ��������ĵ�
    
    u16 startPoint;     //ѭ����������ģʽ��PVT��ʼ��
    u16 endPoint;       //ѭ����������ģʽ��PVT��ֹ��
    u32 ncycle;         //Nѭ��ģʽ��ѭ����
    u16 warnPoint;      //FIFOģʽ�������

    u32 fpgaPwmClock;   //FPGA PWMʱ��
    f32 startPosition;  //PVT��ʼ���λ��
    u32 targetStep;     //Ŀ�경��
    f32 lastStepSpeed;  //��һ�����ٶȣ�ʵ�ʼ�¼����ʱ��
    f32 lastStepTime;   //��һ�����������PVT��0ʱ�̵�ʱ��(PVT��ĵ�һ����ʱ������Ϊ0)
    
    u32 targetLine;     //Ŀ������
    f32 lastLineSpeed;  //��һ�ߵ��ٶȣ�ʵ�ʼ�¼����ʱ��
    f32 lastLineTime;   //��һ�����������PVT��0ʱ�̵�ʱ��(PVT��ĵ�һ����ʱ������Ϊ0)
    f32 remainLine;     //��ǰ�߼��㲽����ʣ�µ�����
    
    f32             errorTime;      //�������뵼�µ��ۼ����
    DirectionStruct lastStepDir;    //��һ���ķ���
      
}PvtInfoStruct;

/*-------------��������Ϣ�ṹ��-------------*/
typedef struct
{
    EncoderTypeEnum type;             //����
    EncoderChanEnum chanNum;          //ͨ����
    EncoderLineEnum lineNum;          //����
    f32             linePerRadian;    //ÿ���ȶ�Ӧ����������ͨ��������������
      
}EncoderInfoStruct;

/*-------------�����Ϣ�ṹ��-------------*/
typedef struct
{
    MotorTypeEnum        motorType;          //����
    u8                   gearRatio;          //���ٱ�
    StepAngleEnum        stepAngel;          //�����
    MicroStepEnum        microSteps;         //΢����
    u32                  peakSpeed;          //��������ٶ�
    u32                  totalSteps;         //�ܲ���������microSteps * steps * gearRatio
    EncoderInfoStruct    encoderInfo;        //���׵ı�����
      
}MotorInfoStruct;

/*-------------ʧ����Ϣ�ṹ��-------------*/
typedef struct
{
    u32              outOfSteps;    //ʧ��������
    ResponseTypeEnum response;      //��Ӧ
      
}OOStepInfoStruct;

/*-------------��Buffer�ṹ��-------------*/
typedef struct
{
    bool bMotion;    //�Ƿ�ʼ����
    
    bool bReptEnable[REPORT_RESERVE];    //�Ƿ�ʹ���ϱ�����
    
    u8   temp;          //����¶�
    u32  emergency;
    u32  maxSpeed;
    u32  minSpeed;
    u32  maxPosn;
    u32  minPosn;
    u32  maxTorque;
    u32  minTorque;
    u32  origin;
    u32  reptPeriod;    //�ϱ�����
    u32  outOfSteps;
    u32  steps;
    u32  velority;
    u32  torque;
    OOStepInfoStruct outOfStepInfo;
      
}MotionInfoStruct;

/*-------------OTP��Ϣ�ṹ��-------------*/
typedef struct
{
    bool             bEnable;
    u8               threshold;
    ResponseTypeEnum response;
    
}OtpInfoStruct;

/*------------���ִ������ṹ��-----------*/
typedef struct
{
    bool             bEnable;
    TriggerTypeEnum  triggerType;
    ResponseTypeEnum response;
    
}DsensorInfoStruct;

/*-----------ģ�⴫�����ṹ��------------*/
typedef struct
{
    bool             bEnable;
    f32              threshold;
    ResponseTypeEnum response;
    
}AsensorInfoStruct;

/*-------------�������޽ṹ��-------------*/
typedef struct
{
    s16 otpThr;
    s16 canGroup;
    s32 canSendId;
    s32 canTargetId;
    s32 canGroupId;    
    s32 canRadioId;

    s32 pvtStartPoint;
    s32 pvtEndPoint;
    s32 pvtNcycles;
    s32 pvtWarnPoint;
    
    s16 motorGearRatio;
    s32 motorPeakSpeed;
    
    f32 pvtPosn;
    f32 pvtSpeed;
    f32 pvtTime;
    f32 trapzPosn;
    f32 trapzSpeed;
    f32 trapzTime;

    s32 motionEmgc;
    
    s32 motionMaxSpeed;
    s32 motionMaxPosn;
    s32 motionMaxTorque;

    s32 encoderLineNum;

    s32 outOfStepNum;
    
    f32 asensorThr;
    
}UpLimitStruct;

/*-------------�������޽ṹ��-------------*/
typedef struct
{
    s16 otpThr;
    s16 canGroup;
    s32 canSendId;
    s32 canTargetId;
    s32 canGroupId;    
    s32 canRadioId;

    s32 pvtStartPoint;
    s32 pvtEndPoint;
    s32 pvtNcycles;
    s32 pvtWarnPoint;
    
    s16 motorGearRatio;
    s32 motorPeakSpeed;
    
    f32 pvtPosn;
    f32 pvtSpeed;
    f32 pvtTime;
    f32 trapzPosn;
    f32 trapzSpeed;
    f32 trapzTime;

    s32 motionEmgc;
    
    s32 motionMinSpeed;
    s32 motionMinPosn;
    s32 motionMinTorque;

    s32 encoderLineNum;

    s32 outOfStepNum;
    
    f32 asensorThr;
    
}DownLimitStruct;

/*-----------���������޽ṹ��-------------*/
typedef struct
{
    UpLimitStruct   upLimit;
    DownLimitStruct downLimit;
    
}ParaLimitStruct;

/*-------------�汾�Žṹ��-------------*/
typedef struct
{
    u8 software[SOFTWARE_VER_LEN];    //��֧�汾��+��汾��+С�汾��+����汾��, ����汾�Ų�����
    u8 fpga[FPGA_VER_LEN];
    u8 hardware[HARDWARE_VER_LEN];
    u8 boot[BOOT_VER_LEN];
    
}SystemVerStruct;

/*-------------ϵͳ��Ϣ�ṹ��-----------*/
typedef struct
{
    ProductModelEnum qubeleyModel;    //�ͺ�:�����/�������
    s8               qubeleySn[QUBELEY_SN_LEN];    //���к�
    
    u8               errorCode[ERROR_CODE_LEN];    //�������
    SystemVerStruct  version;
    WorkModeEnum     workMode;
    PowerOnModeEnum  powerOn;
    u8               jointNum;       //������������ƵĹؽ���
    
}SystemInfoStruct;



#endif
/*****************************************END OF FILE****************************************/