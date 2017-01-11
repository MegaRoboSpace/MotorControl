/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  main.c；
功能描述:  此工程的作用是接收CAN口上的PVT数据并解算成电机每步的脉冲时间，完成电机的运行;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.11.10;
历史版本:  无;
*********************************************************************************************/
#include "main.h"
#include "timer.h"
#include "canphy.h"
#include "canmac.h"
#include "usartphy.h"
#include "usartmac.h"
#include "cmdparse.h"
#include "softtimer.h"
#include "paraverify.h"
#include "pvtalgorithm.h"
#include "pvtcmd.h"



/****************************************外部变量声明*****************************************/
extern SystemInfoStruct  g_systemInfo;
extern PvtInfoStruct     g_pvtInfo;
extern SoftTimerStr      g_debugTimer;
extern MotorInfoStruct   g_motorInfo;
extern SystemIntfcStruct g_systemIntfc;
extern SoftTimerStr      g_uartDmaRecTimer;
extern SoftTimerStr      g_pvtCalcEndTimer;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
RCC_ClocksTypeDef RCC_ClockFreq;



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: WorkModeProcess;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void WorkModeProcess(void)
{
    if (g_systemInfo.workMode != WORK_TORQUE)
    {
        //计算PVT
        PvtResultCalc(g_systemInfo.workMode);
        
        //需要通知控制器PVT计算结束
        if (g_pvtInfo.bCalcEnd)
        {
            PvtCalcEndTimerCB();    //先调用回调函数发送一次计算结束，同时开启定时器等待下次发送
        }
    }
    else
    {
        //开软定时器，定时读取FPGA采集的反馈数据，存入Buffer中，等待CAN接口或者Uart接口发送
    }
}


/*********************************************************************************************
函 数 名: void;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
int main(void)
{
    SystemInit();
    RCC_GetClocksFreq(&RCC_ClockFreq);

    //初始化Flash

    //初始化IIC

    //读取Flash中保存的参数

    //读取EEprom中保持的参数

#if DEBUG_MODE
    g_pvtInfo.fpgaPwmClock = 10000000;    //10MHz
    g_pvtInfo.targetStep = 1;
    g_pvtInfo.targetLine = 1;

    g_motorInfo.encoderInfo.linePerRadian = 4000 * RECIP_OF_DBL_RADIAN;
    g_motorInfo.totalSteps = 512000;
#endif

    //初始化硬件资源
    USARTInit();
    CANInit();
    TIMInit();

    //配置FPGA代码

#if !JTAG_MODE
    //看门狗初始化
    IWDGInit();
#endif

    //初始化协议栈
    UartStreamBufferInit();
    CanStreamBufferInit();

    //初始化命令解析模块
    CmdParseInit();

    //初始化参数验证模块
    ParaLimitInit();
    
#if DEBUG_MODE        
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIOB->BRR = GPIO_Pin_5;
#endif


    while (1)
    {
        //处理CAN数据
        CanFrameProcess();
        
        //处理Usart数据
        UartFrameProcess();

        //处理命令集
        CmdParseFrameProcess();

        //处理工作(根据工作模式进行处理)
        WorkModeProcess();
        
        //处理所有的软件定时器 
        StimerExamine(&g_uartDmaRecTimer);
        StimerExamine(&g_pvtCalcEndTimer);
        
        //喂狗
        IWDGFeed();
    }

    return 0;
}



/*******************************************文件尾********************************************/
