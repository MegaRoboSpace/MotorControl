/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  systeminit.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2017.01.11;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "systeminit.h"



/****************************************�ⲿ��������*****************************************/



/*****************************************�ֲ��궨��******************************************/
#define    SYSTEM_SOFTWARE_BRANCH_VER_INDEX    0 
#define    SYSTEM_SOFTWARE_MAJOR_VER_INDEX     1
#define    SYSTEM_SOFTWARE_MINOR_VER_INDEX     2
#define    SYSTEM_SOFTWARE_BUILD_VER_INDEX     3



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
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



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: SystemParaInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void SystemParaInit(void)
{ 
    u16 i;

    
    //ϵͳ��Ϣ�ṹ���ʼ��
    g_systemInfo.qubeleyModel = MODEL_SINGEL;
    memcpy(g_systemInfo.qubeleySn, qubeleySn, QUBELEY_SN_LEN);
    memset(g_systemInfo.errorCode, 0, ERROR_CODE_LEN);
    memcpy(g_systemInfo.version.software, software, ERROR_CODE_LEN);
    g_systemInfo.workMode = WORK_NORMAL;
    g_systemInfo.powerOn  = POWERON_DEFAULT;
    g_systemInfo.jointNum = 0;
    

    //ϵͳ�ӿڽṹ���ʼ��
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


    //�����Ϣ�ṹ���ʼ��
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


    //������Ϣ�ṹ���ʼ��
    g_motionInfo.bMotion = false;
    for (i = 0;i < REPORT_RESERVE;i++)
    {
        g_motionInfo.bReptEnable[i] = false;
    }


    //PVT���ݽṹ���ʼ��
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


/*******************************************�ļ�β********************************************/