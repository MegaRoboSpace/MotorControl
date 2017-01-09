/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  main.c��
��������:  �˹��̵������ǽ���CAN���ϵ�PVT���ݲ�����ɵ��ÿ��������ʱ�䣬��ɵ��������;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.11.10;
��ʷ�汾:  ��;
*********************************************************************************************/
#include "main.h"
#include "timer.h"
#include "canphy.h"
#include "canmac.h"
#include "usartphy.h"
#include "usartmac.h"
#include "cmdparse.h"
#include "softtimer.h"
#include "pvtalgorithm.h"
#include "pvtparaverify.h"
#include "protocolstack.h"
#include "systemparaverify.h"
#include "intfcparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern SystemInfoStruct g_systemInfo;
extern PvtInfoStruct    g_pvtInfo;
extern SoftTimerStr     g_pvtCalcEndTimer;
extern SoftTimerStr     g_debugTimer;
extern SystemInterfaceStruct g_systemIntfc;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
RCC_ClocksTypeDef RCC_ClockFreq;



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: WorkModeProcess;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void WorkModeProcess(void)
{
    if (g_systemInfo.workMode != WORK_TORQUE)
    {
        //����PVT
        PvtResultCalc(g_systemInfo.workMode);
        
        //��Ҫ֪ͨ������PVT�������
        if (g_pvtInfo.bCalcEnd)
        {
            PvtCalcEndTimerOutCB();    //�ȵ��ûص���������һ�μ��������ͬʱ������ʱ���ȴ��´η���
        }
    }
    else
    {
        //����ʱ������ʱ��ȡFPGA�ɼ��ķ������ݣ�����Buffer�У��ȴ�CAN�ӿڻ���Uart�ӿڷ���
    }
}


/*********************************************************************************************
�� �� ��: void;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void main(void)
{
    SystemInit();
    RCC_GetClocksFreq(&RCC_ClockFreq);

    //��ʼ��Flash

    //��ʼ��IIC

    //��ȡFlash�б���Ĳ���

    //��ȡEEprom�б��ֵĲ���

#if DEBUG_MODE
    //����ͨ�Žӿ�ΪUart
    g_systemIntfc.linkType = LINK_UART;
    g_systemIntfc.uartIntfc.baudIndex = UART_BAUDRATE_115200;
    g_systemIntfc.canIntfc.idTypeIndex = CAN_ID_TYPE_EXT;
    g_systemIntfc.canIntfc.sendId   = 0x01000000;
    g_systemIntfc.canIntfc.targetId = 0x00000001;
    g_systemIntfc.canIntfc.groupId  = 0x00000100;
    g_systemIntfc.canIntfc.radioId  = 0x00010000;

    g_pvtInfo.fpgaPwmClock = 10000000;    //10MHz
    g_pvtInfo.radianToStep = 81487.33;
#endif

    //��ʼ��Ӳ����Դ
    USARTInit();
    CANInit();
    TIMInit();

    //����FPGA����

#if !JTAG_MODE
    //���Ź���ʼ��
    IWDGInit();
#endif

    //��ʼ�������ʱ��
    StimerAllInit();

    //��ʼ��Э��ջ
    ProtocolStackInit();

    //��ʼ���������ģ��
    CmdParseInit();

    //��ʼ��������֤ģ��
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
        //����CAN����
        CanFrameProcess();
        
        //����Usart����
        UsartFrameProcess();

        //�������
        CmdParseFrameProcess();

        //������(���ݹ���ģʽ���д���)
        WorkModeProcess();
        
        //�������е������ʱ��
        StimerAllCheck();
        
        //ι��
        IWDGFeed();
    }
}



/*******************************************�ļ�β********************************************/
