/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  comStruct.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2017.01.10;
历史版本:  无;
*********************************************************************************************/
#ifndef __COM_STRUCT_H
#define __COM_STRUCT_H

#include "comEnum.h"



/***************************************常数和类型声明****************************************/
/*-------------流Buffer结构体-------------*/
typedef struct 
{
    bool bNotEmpty    :1;      //是否有数据
    bool bRewind      :1;      //是否回绕
    bool bAlmostFull  :1;      //是否快满了
    u8   u8Reverse    :5;      //保留
    u16  bufferSize;
    u16  headOffset;
    u16  tailOffset;
    u16  dataTailOffset;       //有效数据的尾部
    u16  reserveMemorySize;    
    u8   *pBuffer;
    
}StreamBufferStr;

/*-------------命令帧格式结构体-------------*/
typedef struct
{
    CmdTypeEnum  mainType;      //命令主类型
    u8           subType;       //命令子类型
    u8           dataLen;       //数据长度
    u8           payload[0];    //帧数据
    
}CmdParseFrameStr;

/*-------------软定时器结构体-------------*/
typedef struct
{
  bool         bUsed;        //是否启用
  u16          periodMS;     //定时时间
  u64          timeoutMS;    //超时时间
  timeOutFunc  timerOut;     //超时回调函数
  
}SoftTimerStr;

/*-----------CAN Phy层帧格式结构体-----------*/
typedef struct
{    
    u32 canID;         //CANID
    u8  frameLen;      //帧长度，包含ID
    u8  payload[0];    //帧数据
    
}CanPhyFrameStr;

/*-----------UART Phy层帧格式结构体-----------*/
typedef struct
{    
    u8 SOF;           //Start of frame
    u8 frameLen;      //帧长度，包含SOF和自身
    u8 xorValue;      //异或校验值
    u8 payload[0];    //帧数据
    
}UartPhyFrameStr;

/*-------------CAN接口结构体-------------*/
typedef struct
{
    CanTypeEnum  idType;    //类型A或B
    
    u8  group;
    CanBaudEnum  baud;      //波特率
    u32 sendId;
    u32 targetId;
    u32 groupId;
    u32 radioId;
    
}CanIntfcStruct;

/*-------------UART接口结构体------------*/
typedef struct
{
    UartBaudEnum baud;       //波特率
    WordLenEnum  wordLen;    //数据长度
    StopBitEnum  stopBit;    //停止位
    ParityEnum   parity;     //校验方式
    FlowCtlEnum  flowCtl;    //流控制
    
}UartIntfcStruct;

/*-----------系统接口结构体-------------*/
typedef struct
{
    LinkTypeEnum       linkType;      //回复命令时使用CAN还是UART
    CanIntfcStruct     canIntfc;
    UartIntfcStruct    uartIntfc;
    
}SystemIntfcStruct;

/*-------------PVT点结构体-------------*/
typedef struct
{
    f32 position;    //位置
    f32 speed;       //速度
    f32 time;        //时间
      
}PvtPointStruct;

/*-------------PVT数据结构体-------------*/
typedef struct
{
    bool bRewind  :1;    //PVT点Buffer是否回绕
    bool bCalcEnd :1;    //计算结束，需要上报控制器或PC
    u8   reserve  :6;    //保留
    
    PvtModeEnum    pvtMode;                            //PVT计算模式
    PvtPointStruct pvtPoint[PVT_POINT_BUFFER_SIZE];    //PVT点数据
    
    u16 headPoint;      //Buffer中有效数据的起始点，有效指的是还未被计算的点
    u16 tailPoint;      //Buffer中有效数据的终止点，有效指的是还未被计算的点
    u16 remainPoint;    //Buffer剩余可写入的点数
    u16 outputPoint;    //当前正在输出的点
    
    u16 startPoint;     //循环或者无限模式下PVT起始点
    u16 endPoint;       //循环或者无限模式下PVT终止点
    u32 ncycle;         //N循环模式的循环数
    u16 warnPoint;      //FIFO模式警告点数

    u32 fpgaPwmClock;   //FPGA PWM时钟
    f32 startPosition;  //PVT初始点的位置
    u32 targetStep;     //目标步数
    f32 lastStepSpeed;  //上一步的速度，实际记录的是时间
    f32 lastStepTime;   //上一步相对于整个PVT表0时刻的时间(PVT表的第一个点时间总是为0)
    
    u32 targetLine;     //目标线数
    f32 lastLineSpeed;  //上一线的速度，实际记录的是时间
    f32 lastLineTime;   //上一线相对于整个PVT表0时刻的时间(PVT表的第一个点时间总是为0)
    f32 remainLine;     //当前线计算步数后剩下的线数
    
    f32             errorTime;      //四舍五入导致的累计误差
    DirectionStruct lastStepDir;    //上一步的方向
      
}PvtInfoStruct;

/*-------------编码器信息结构体-------------*/
typedef struct
{
    EncoderTypeEnum type;             //类型
    EncoderChanEnum chanNum;          //通道数
    EncoderLineEnum lineNum;          //线数
    f32             linePerRadian;    //每弧度对应的线数，由通道数和线数计算
      
}EncoderInfoStruct;

/*-------------电机信息结构体-------------*/
typedef struct
{
    MotorTypeEnum        motorType;          //类型
    u8                   gearRatio;          //减速比
    StepAngleEnum        stepAngel;          //步距角
    MicroStepEnum        microSteps;         //微步数
    u32                  peakSpeed;          //最大运行速度
    u32                  totalSteps;         //总步数，等于microSteps * steps * gearRatio
    EncoderInfoStruct    encoderInfo;        //配套的编码器
      
}MotorInfoStruct;

/*-------------失步信息结构体-------------*/
typedef struct
{
    u32              outOfSteps;    //失步数上限
    ResponseTypeEnum response;      //响应
      
}OOStepInfoStruct;

/*-------------流Buffer结构体-------------*/
typedef struct
{
    bool bMotion;    //是否开始运行
    
    bool bReptEnable[REPORT_RESERVE];    //是否使能上报功能
    
    u8   temp;          //电机温度
    u32  emergency;
    u32  maxSpeed;
    u32  minSpeed;
    u32  maxPosn;
    u32  minPosn;
    u32  maxTorque;
    u32  minTorque;
    u32  origin;
    u32  reptPeriod;    //上报周期
    u32  outOfSteps;
    u32  steps;
    u32  velority;
    u32  torque;
    OOStepInfoStruct outOfStepInfo;
      
}MotionInfoStruct;

/*-------------OTP信息结构体-------------*/
typedef struct
{
    bool             bEnable;
    u8               threshold;
    ResponseTypeEnum response;
    
}OtpInfoStruct;

/*------------数字传感器结构体-----------*/
typedef struct
{
    bool             bEnable;
    TriggerTypeEnum  triggerType;
    ResponseTypeEnum response;
    
}DsensorInfoStruct;

/*-----------模拟传感器结构体------------*/
typedef struct
{
    bool             bEnable;
    f32              threshold;
    ResponseTypeEnum response;
    
}AsensorInfoStruct;

/*-------------参数上限结构体-------------*/
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

/*-------------参数下限结构体-------------*/
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

/*-----------参数上下限结构体-------------*/
typedef struct
{
    UpLimitStruct   upLimit;
    DownLimitStruct downLimit;
    
}ParaLimitStruct;

/*-------------版本号结构体-------------*/
typedef struct
{
    u8 software[SOFTWARE_VER_LEN];    //分支版本号+大版本号+小版本号+编译版本号, 编译版本号不对外
    u8 fpga[FPGA_VER_LEN];
    u8 hardware[HARDWARE_VER_LEN];
    u8 boot[BOOT_VER_LEN];
    
}SystemVerStruct;

/*-------------系统信息结构体-----------*/
typedef struct
{
    ProductModelEnum qubeleyModel;    //型号:单电机/多轴控制
    s8               qubeleySn[QUBELEY_SN_LEN];    //序列号
    
    u8               errorCode[ERROR_CODE_LEN];    //错误代码
    SystemVerStruct  version;
    WorkModeEnum     workMode;
    PowerOnModeEnum  powerOn;
    u8               jointNum;       //多轴控制器控制的关节数
    
}SystemInfoStruct;



#endif
/*****************************************END OF FILE****************************************/