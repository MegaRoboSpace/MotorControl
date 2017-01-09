/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtparaverify.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.19;
历史版本:  无;
*********************************************************************************************/
#ifndef __PVT_PARA_VERIFY_H
#define __PVT_PARA_VERIFY_H



/******************************************包含文件*******************************************/
#include "stm32f10x.h"
#include "datatype.h"
#include "debug.h"
#include "paraverify.h"



/****************************************外部变量声明*****************************************/



/*******************************************宏定义********************************************/ 
#define    PVT_POINT_BUFFER_SIZE    256



/***************************************常数和类型声明****************************************/
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
    bool           bCalcEnd :1;    //是否计算结束可以输出，如果结束就向控制器发送计算结束的命令直到控制器回复
    u8             reserve  :6;
    
    PvtModeEnum    pvtMode;
    PvtPointStruct pvtPoint[PVT_POINT_BUFFER_SIZE];
    u16            headPoint;      //Buffer中有效的起始点，这里的有效指的是还没有计算的点
    u16            tailPoint;      //Buffer中有效的终止点，这里的有效指的是还没有计算的点
    u16            remainPoint;    //当前PVT_POINT_BUFFER中还有多少剩余空间可以存放PVT数据
    u16            outputPoint;    //当前正在输出的PVT数据在Buffer中的位置索引
    
    u16            startPoint;     //开始(计算)输出的点，循环或无限模式下使用
    u16            endPoint;       //停止(计算)输出的点，循环或无限模式下使用
    u32            ncycle;         //循环次数，循环模式下使用
    u16            warnPoint;      //FIFO模式下剩余未输出PVT点数下限，少于此值后将向上位机发送警告

    u32             fpgaPwmClock;   //FPGA PWM的时钟
    f32             startPosition;  //PVT表的初始位置
    u32             targetStep;     //当前要求取的步数，每个PVT List初始都是1
    f32             lastStepSpeed;  //上一步的速度，实际存储的是时间
    f32             lastStepTime;   //上一步相对于0时刻的时间(PVT List第一个点的时间永远是0时刻)
    
    u32             targetLine;     //当前要求取的线数，每个PVT List初始都是1
    f32             lastLineSpeed;  //上一线的速度，实际存储的是时间
    f32             lastLineTime;   //上一线相对于0时刻的时间(PVT List第一个点的时间永远是0时刻)
    f32             remainLine;     //不是整数线时，尾部的线数
    
    f32             errorTime;      //误差时间，归一化之后的时间值
    DirectionStruct lastStepDir;    //上一步的方向
      
}PvtInfoStruct;



/******************************************变量声明*******************************************/



/******************************************函数声明*******************************************/
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



/*****************************************头文件保护******************************************/
#endif
/*******************************************文件尾********************************************/