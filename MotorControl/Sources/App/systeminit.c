/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  systeminit.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2017.01.11;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "systeminit.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/
#define    SYSTEM_SOFTWARE_BRANCH_VER_INDEX    0 
#define    SYSTEM_SOFTWARE_MAJOR_VER_INDEX     1
#define    SYSTEM_SOFTWARE_MINOR_VER_INDEX     2
#define    SYSTEM_SOFTWARE_BUILD_VER_INDEX     3



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SystemInfoStruct  g_systemInfo;
SystemIntfcStruct g_systemIntfc; 
MotorInfoStruct   g_motorInfo; 
MotionInfoStruct  g_motionInfo;
OtpInfoStruct     g_otpInfo;
DsensorInfoStruct g_dsensorInfo[DIGIT_SENSOR_NUM];
AsensorInfoStruct g_asensorInfo[ANALOG_SENSOR_NUM];
PvtInfoStruct     g_pvtInfo;


PvtPointStruct pvtPoint[3] = {{0, 0, 0},
                              {0.1274050015509044, 0.4042337149649688, 0.536361535},
                              {0.2548100031018088, 0.6547734148730262, 0.759514305}};
                           
u8 software[SOFTWARE_VER_LEN] = {0, 0, 0, 1};
s8 qubeleySn[QUBELEY_SN_LEN] = {0};



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: SystemParaInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void SystemParaInit(void)
{ 
    u16 i;

    
    //系统信息结构体初始化
    g_systemInfo.qubeleyModel = MODEL_SINGEL;
    memcpy(g_systemInfo.qubeleySn, qubeleySn, QUBELEY_SN_LEN);
    memset(g_systemInfo.errorCode, 0, ERROR_CODE_LEN);
    memcpy(g_systemInfo.version.software, software, ERROR_CODE_LEN);
    g_systemInfo.workMode = WORK_NORMAL;
    g_systemInfo.powerOn  = POWERON_DEFAULT;
    g_systemInfo.jointNum = 0;
    

    //系统接口结构体初始化
    g_systemIntfc.linkType = LINK_CAN;
    
    g_systemIntfc.canIntfc.idType = CAN_TYPE_B;
    g_systemIntfc.canIntfc.group = 0;
    g_systemIntfc.canIntfc.baud = CANBAUD_1000;
    g_systemIntfc.canIntfc.sendId   = 0x01000000;
    g_systemIntfc.canIntfc.targetId = 0x00000001;
    g_systemIntfc.canIntfc.groupId  = 0x00000100;
    g_systemIntfc.canIntfc.radioId  = 0x00010000;
    
    g_systemIntfc.uartIntfc.baud = UARTBAUD_115200;
    g_systemIntfc.uartIntfc.wordLen = 0;
    g_systemIntfc.uartIntfc.stopBit = 0;
    g_systemIntfc.uartIntfc.parity = 0;
    g_systemIntfc.uartIntfc.flowCtl = 0;


    //电机信息结构体初始化
    g_motorInfo.motorType = MOTOR_57;
    g_motorInfo.gearRatio = 10;
    g_motorInfo.stepsIndex = 200;
    g_motorInfo.microStepsIndex = 256;
    //g_motorInfo.peakSpeed = ;
    g_motorInfo.totalSteps = g_motorInfo.gearRatio *  g_motorInfo.stepsIndex * g_motorInfo.microStepsIndex;
    g_motorInfo.encoderInfo.type = ENCODER_INC;
    g_motorInfo.encoderInfo.chanNum = ECCHAN_3;
    g_motorInfo.encoderInfo.lineNum = 4000;
    g_motorInfo.encoderInfo.linePerRadian = g_motorInfo.encoderInfo.lineNum * 2 * RECIP_OF_DBL_RADIAN; 


    //运行信息结构体初始化
    g_motionInfo.bMotion = false;
    for (i = 0;i < REPORT_RESERVE;i++)
    {
        g_motionInfo.bReptEnable[i] = false;
    }


    //PVT数据结构体初始化
    g_pvtInfo.bRewind  = false;
    g_pvtInfo.bCalcEnd = false;
    
    g_pvtInfo.pvtMode = PVT_SINGEL;
    memcpy(g_pvtInfo.pvtPoint, pvtPoint, sizeof(pvtPoint));
    g_pvtInfo.headPoint = 0;
    g_pvtInfo.tailPoint = 2;
    g_pvtInfo.fpgaPwmClock = PVT_FPGA_PWM_CLOCK;
    g_pvtInfo.targetStep = 1;
    g_pvtInfo.targetLine = 1;
}


/*******************************************文件尾********************************************/