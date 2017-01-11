/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  comEnum.h;
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2017.01.10;
��ʷ�汾:  ��;
*********************************************************************************************/
#ifndef __COM_ENUM_H
#define __COM_ENUM_H



/*******************************************�궨��********************************************/
#define    PVT_POINT_BUFFER_SIZE    256  
#define    RECIP_OF_DBL_RADIAN      0.1591549f    //��ȡֵ3.1415926
#define    PVT_FPGA_PWM_CLOCK       10000000      //10MHz

#define    QUBELEY_SN_LEN      14
#define    ERROR_CODE_LEN      6     //�ֽ���
#define    SOFTWARE_VER_LEN    4
#define    FPGA_VER_LEN        2
#define    HARDWARE_VER_LEN    2
#define    BOOT_VER_LEN        2

#define    UART_BAUDRATE_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_FLOW_CTL_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_WORD_LEN_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_STOP_BIT_NUM       10    //��������ֵ�ĸ�����Ӧ
#define    UART_PARITY_NUM         10    //��������ֵ�ĸ�����Ӧ

#define    CAN_ID_TYPE_NUM         2     //��������ֵ�ĸ�����Ӧ
#define    CAN_BAUDRATE_NUM        8     //��������ֵ�ĸ�����Ӧ

#define    DIGIT_SENSOR_NUM     10
#define    ANALOG_SENSOR_NUM    10



/***************************************��������������****************************************/
typedef void ( *timeOutFunc)(void);
typedef void (*SubCmdProFunc)(u8 cmdDataLen, u8 *pCmdData);



/***************************************��������������****************************************/
/*-------------����ϵͳö��-------------*/
//������ö��
typedef enum
{
    CMD_LINK = 1,      //������������
    CMD_SYSTME,        //ϵͳ��������
    CMD_UART,          //RS232��������
    CMD_CAN,           //CAN��������
    CMD_MOTOR,         //�����������
    CMD_ENCODER,       //��������������
    CMD_PVT,           //PVT��������
    CMD_TRAPZCURVE,    //����������������
    CMD_MOTION,        //������������
    CMD_OUTOFSTEP,     //ʧ����������
    CMD_OTP,           //OTP��������
    CMD_DSENSOR,       //���ִ�������������
    CMD_ASENSOR,       //ģ�⴫������������
    CMD_CALIBRATE,     //У׼����
    CMD_UPDATE,        //��������
    CMD_DEBUG,         //DEBUG����
    CMD_RESERVE        //����
    
}CmdTypeEnum;

//������ö��
typedef enum
{
    LINKCMD_INTFC = 0,
    LINKCMD_INTFCQ,
    LINKCMD_RESERVE
    
}LinkCmdSubTypeEnum;

typedef enum
{
    SYSCMD_INFOQ = 0,
    SYSCMD_ERRORQ,
    SYSCMD_VERSIONQ,
    SYSCMD_MODE,
    SYSCMD_MODEQ,
    SYSCMD_POWERON,
    SYSCMD_POWERONQ,
    SYSCMD_RESERVE
    
}SystemCmdSubTypeEnum;

typedef enum
{
    UARTCMD_BAUD = 0,
    UARTCMD_BAUDQ,
    UARTCMD_WORDLEN,
    UARTCMD_WORDLENQ,
    UARTCMD_FLOWCTL,
    UARTCMD_FLOWCTLQ,
    UARTCMD_PARITY,
    UARTCMD_PARITYQ,
    UARTCMD_STOPBIT,
    UARTCMD_STOPBITQ,
    UARTCMD_RESERVE
    
}UartCmdSubTypeEnum;

typedef enum
{
    CANCMD_TYPE = 0,
    CANCMD_TYPEQ,
    CANCMD_SENDID,
    CANCMD_SENDIDQ,
    CANCMD_BAUD,
    CANCMD_BAUDQ,
    CANCMD_GROUP,
    CANCMD_GROUPQ,
    CANCMD_TARGETID,
    CANCMD_TARGETIDQ,
    CANCMD_GROUPID,
    CANCMD_GROUPIDQ,
    CANCMD_RADIOID,
    CANCMD_RADIOIDQ,
    CANCMD_RESERVE
    
}CanCmdSubTypeEnum;

typedef enum
{
    MOTORCMD_MICROSTEPS = 0,
    MOTORCMD_MICROSTEPSQ,
    MOTORCMD_GEARRATIO,
    MOTORCMD_GEARRATIOQ,
    MOTORCMD_STEPS,
    MOTORCMD_STEPSQ,
    MOTORCMD_PEAKSPEED,
    MOTORCMD_PEAKSPEEDQ,
    MOTORCMD_TYPE,
    MOTORCMD_TYPEQ,
    MOTORCMD_RESERVE
    
}MotorCmdSubTypeEnum;

typedef enum
{
    ENCODERCMD_LINENUM = 0,
    ENCODERCMD_LINENUMQ,
    ENCODERCMD_CHANNUM,
    ENCODERCMD_CHANNUMQ,
    ENCODERCMD_TYPE,
    ENCODERCMD_TYPEQ,
    ENCODERCMD_RESERVE
    
}EncoderCmdSubTypeEnum;

typedef enum
{
    PVTCMD_MODE = 0,
    PVTCMD_MODEQ,
    PVTCMD_POINT,
    PVTCMD_POINTQ,
    PVTCMD_POSN,
    PVTCMD_POSNQ,
    PVTCMD_SPEED,
    PVTCMD_SPEEDQ,
    PVTCMD_TIME,
    PVTCMD_TIMEQ,
    PVTCMD_REMAINPOINTQ,
    PVTCMD_OUTPUTPOINTQ,
    PVTCMD_STARTPOINT,
    PVTCMD_STARTPOINTQ,
    PVTCMD_ENDPOINT,
    PVTCMD_ENDPOINTQ,
    PVTCMD_NCYCLES,
    PVTCMD_NCYCLESQ,
    PVTCMD_WARNPOINT,
    PVTCMD_WARNPOINTQ,
    PVTCMD_CLEAR,
    PVTCMD_WARN,
    PVTCMD_CALCEND,
    PVTCMD_RESERVE
    
}PvtCmdSubTypeEnum;

typedef enum
{
    TRAPZCMD_POINT = 0,
    TRAPZCMD_POINTQ,
    TRAPZCMD_POSN,
    TRAPZCMD_SPEED,
    TRAPZCMD_TIME,
    TRAPZCMD_RESERVE
    
}TrapzCmdSubTypeEnum;

typedef enum
{
    MOTIONCMD_RUN = 0,
    MOTIONCMD_STOP,
    MOTIONCMD_EMRG,
    MOTIONCMD_EMRGQ,
    MOTIONCMD_MAXSPEED,
    MOTIONCMD_MAXSPEEDQ,
    MOTIONCMD_MINSPEED,
    MOTIONCMD_MINSPEEDQ,
    MOTIONCMD_MAXPOSN,
    MOTIONCMD_MAXPOSNQ,
    MOTIONCMD_MINPOSN,
    MOTIONCMD_MINPOSNQ,
    MOTIONCMD_MAXTORQUE,
    MOTIONCMD_MAXTORQUEQ,
    MOTIONCMD_MINTORQUE,
    MOTIONCMD_MINTORQUEQ,
    MOTIONCMD_ORIGIN,
    MOTIONCMD_ORIGINQ,
    MOTIONCMD_REPORT,
    MOTIONCMD_REPORTQ,
    MOTIONCMD_RPPERIOD,
    MOTIONCMD_RPPERIODQ,
    MOTIONCMD_OOSTEPSQ,      //Out Of Steps Query
    MOTIONCMD_STEPSQ,
    MOTIONCMD_VELORITYQ,
    MOTIONCMD_TORQUEQ,
    MOTIONCMD_TEMPQ,
    MOTIONCMD_RESERVE
    
    
}MotionCmdSubTypeEnum;

typedef enum
{
    OOSCMD_OUTNUM = 0,
    OOSCMD_OUTNUMQ,
    OOSCMD_RESPONSE,
    OOSCMD_RESPONSEQ,
    OOSCMD_RESERVE
    
}OOStepCmdSubTypeEnum;

typedef enum
{
    OTPCMD_STATE = 0,
    OTPCMD_STATEQ,
    OTPCMD_THRESHOLD,
    OTPCMD_THRESHOLDQ,
    OTPCMD_RESPONSE,
    OTPCMD_RESPONSEQ,
    OTPCMD_RESERVE
    
}OtpCmdSubTypeEnum;

typedef enum
{
    DSENSORCMD_STATE = 0,
    DSENSORCMD_STATEQ,
    DSENSORCMD_TYPE,
    DSENSORCMD_TYPEQ,
    DSENSORCMD_RESPONSE,
    DSENSORCMD_RESPONSEQ,
    DSENSORCMD_RESERVE
    
}DsensorCmdSubTypeEnum;

typedef enum
{
    ASENSORCMD_STATE = 0,
    ASENSORCMD_STATEQ,
    ASENSORCMD_THRESHOLD,
    ASENSORCMD_THRESHOLDQ,
    ASENSORCMD_RESPONSE,
    ASENSORCMD_RESPONSEQ,
    ASENSORCMD_RESERVE
    
}AsensorCmdSubTypeEnum;

typedef enum
{
    CALBRCMD_BACKLASH = 0,
    CALBRCMD_BLEND,
    CALBRCMD_MECHERROR,
    CALBRCMD_MEEND,
    CALBRCMD_RESERVE
    
}CalbrCmdSubTypeEnum;

typedef enum
{
    UPDATECMD_START = 0,
    UPDATECMD_READY,
    UPDATECMD_DATA,
    UPDATECMD_END,
    UPDATECMD_JUMP,
    UPDATECMD_APPADDR,
    UPDATECMD_FPGAADDR,
    UPDATECMD_RESERVE
    
}UpdateCmdSubTypeEnum;

typedef enum
{
    DEBUGCMD_SET = 0,
    DEBUGCMD_RESERVE
    
}DebugCmdSubTypeEnum;

/*-------------��������ö��-------------*/
typedef enum
{
    LINK_CAN,
    LINK_UART
    
}LinkTypeEnum;

/*-------------����ģʽö��-------------*/
typedef enum
{
    WORK_NORMAL = 0,    //��ͨģʽ
    WORK_UNIFORM,       //����ģʽ
    WORK_POSITION,      //λ�÷���ģʽ
    WORK_TORQUE         //���ط���ģʽ
    
}WorkModeEnum;

/*-------------�ϵ�״̬ö��-------------*/
typedef enum
{
    POWERON_DEFAULT = 0,    //ʹ��Ĭ��ֵ
    POWERON_LAST,           //ʹ���ϴ�ֵ
    
}PowerOnModeEnum;

/*-------------��Ʒ����ö��-------------*/
typedef enum
{
    MODEL_SINGEL,    //���������
    MODEL_MULTI      //��������
    
}ProductModelEnum;

/*-------------UART������ö��-------------*/
typedef enum
{
    UARTBAUD_4800 = 0,    //4800bps
    UARTBAUD_7200,
    UARTBAUD_9600,
    UARTBAUD_14400,
    UARTBAUD_19200,
    UARTBAUD_38400,
    UARTBAUD_57600,
    UARTBAUD_115200,
    UARTBAUD_128000
    
}UartBaudEnum;

/*-------------UART���ݳ���ö��-------------*/
typedef enum
{
    WORDLEN_8 = 0,    //4800bps
    WORDLEN_9
    
}WordLenEnum;

/*-------------UART������ö��-------------*/
typedef enum
{
    STOPBIT_10 = 0,
    STOPBIT_05,
    STOPBIT_20,
    STOPBIT_15
    
}StopBitEnum;

/*-------------UARTУ�鷽ʽö��-------------*/
typedef enum
{
    PARITY_NONE = 0,
    PARITY_EVEN,
    PARITY_ODD
    
}ParityEnum;

/*-------------UARTֹͣλö��-------------*/
typedef enum
{
    FLOWCTL_NONE = 0,
    FLOWCTL_RTS,
    FLOWCTL_CTS,
    FLOWCTL_RTS_CTS
    
}FlowCtlEnum;

/*-------------CAN����ö��-------------*/
typedef enum
{
    CAN_TYPE_A = 0,
    CAN_TYPE_B
    
}CanTypeEnum;

/*-------------CAN������ö��-------------*/
typedef enum
{
    CANBAUD_1000 = 0,    //1000kBps
    CANBAUD_500,
    CANBAUD_250,
    CANBAUD_125,
    CANBAUD_100,
    CANBAUD_50,
    CANBAUD_20,
    CANBAUD_10
    
}CanBaudEnum;


/*-------------��������ö��-------------*/
typedef enum
{
    STEPANGLE_18 = 0,    //1.8��
    STEPANGLE_09,        //0.9��
    STEPANGLE_15,        //1.5��
    STEPANGLE_07         //0.75��
    
}StepAngleEnum;

/*-------------���΢��ö��-------------*/
typedef enum
{
    MICROSTEP_1 = 0,
    MICROSTEP_2,
    MICROSTEP_4,
    MICROSTEP_8,
    MICROSTEP_16,
    MICROSTEP_32,
    MICROSTEP_64,
    MICROSTEP_128,
    MICROSTEP_256
    
}MicroStepEnum;

/*-------------�������ö��-------------*/
typedef enum
{
    MOTOR_42,
    MOTOR_57,
    MOTOR_60
    
}MotorTypeEnum;

/*-------------����������ö��-------------*/
typedef enum
{
    ECLINE_1000,   //1000��
    ECLINE_2000    //2000��
    
}EncoderLineEnum;

/*-------------������ͨ����ö��-------------*/
typedef enum
{
    ECCHAN_1,   //��ͨ��
    ECCHAN_3    //��ͨ��
    
}EncoderChanEnum;

/*-------------����������ö��-------------*/
typedef enum
{
    ENCODER_NONE,    //�ޱ�����
    ENCODER_INC,     //�����ͱ�����
    ENCODER_ABS      //�����ͱ�����
    
}EncoderTypeEnum;

/*-------------PVTģʽö��-------------*/
typedef enum
{
    PVT_SINGEL,
    PVT_NCYCLE,
    PVT_INFINITY,
    PVT_FIFO
    
}PvtModeEnum;

/*-------------���з���ö��-------------*/
typedef enum
{
    DIR_FORWARD = 0,
    DIR_REVERSE
    
}DirectionStruct;

/*-------------�ϱ�ģʽö��-------------*/
typedef enum
{
    REPORT_OUTNUM = 0,
    REPORT_STEPS,
    REPORT_VELORITY,
    REPORT_TORQUE,
    REPORT_TEMP,
    REPORT_RESERVE
    
}ReportTypeEnum;

/*-------------�ϱ�����ö��-------------*/
typedef enum
{
    PERIOD_20MS = 0,
    PERIOD_50MS,
    PERIOD_100MS,
    PERIOD_200MS,
    PERIOD_500MS,
    PERIOD_1000MS
    
}ReportPeriodEnum;

/*-------------��������ö��-------------*/
typedef enum
{
    DTYPE_RISE = 0,
    DTYPE_FALL,
    DTYPE_HIGH,
    DTYPE_LOW
    
}TriggerTypeEnum;

/*-------------��������Ӧö��-------------*/
typedef enum
{
    RESPONSE_NONE = 0,
    RESPONSE_ALARM,
    RESPONSE_STOP,
    RESPONSE_ALARMSTOP,
    RESPONSE_RUN
    
}ResponseTypeEnum;



#endif
/*****************************************END OF FILE****************************************/
