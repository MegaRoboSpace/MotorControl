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
#include "paraverify.h"
#include "pvtalgorithm.h"
#include "pvtcmd.h"



/****************************************�ⲿ��������*****************************************/
extern SystemInfoStruct  g_systemInfo;
extern PvtInfoStruct     g_pvtInfo;
extern SoftTimerStr      g_debugTimer;
extern MotorInfoStruct   g_motorInfo;
extern SystemIntfcStruct g_systemIntfc;
extern SoftTimerStr      g_uartDmaRecTimer;
extern SoftTimerStr      g_pvtCalcEndTimer;



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
            PvtCalcEndTimerCB();    //�ȵ��ûص���������һ�μ��������ͬʱ������ʱ���ȴ��´η���
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
int main(void)
{
    SystemInit();
    RCC_GetClocksFreq(&RCC_ClockFreq);

    //��ʼ��Flash

    //��ʼ��IIC

    //��ȡFlash�б���Ĳ���

    //��ȡEEprom�б��ֵĲ���

#if DEBUG_MODE
    g_pvtInfo.fpgaPwmClock = 10000000;    //10MHz
    g_pvtInfo.targetStep = 1;
    g_pvtInfo.targetLine = 1;

    g_motorInfo.encoderInfo.linePerRadian = 4000 * RECIP_OF_DBL_RADIAN;
    g_motorInfo.totalSteps = 512000;
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

    //��ʼ��Э��ջ
    UartStreamBufferInit();
    CanStreamBufferInit();

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
        UartFrameProcess();

        //�������
        CmdParseFrameProcess();

        //������(���ݹ���ģʽ���д���)
        WorkModeProcess();
        
        //�������е������ʱ�� 
        StimerExamine(&g_uartDmaRecTimer);
        StimerExamine(&g_pvtCalcEndTimer);
        
        //ι��
        IWDGFeed();
    }

    return 0;
}



/*******************************************�ļ�β********************************************/
