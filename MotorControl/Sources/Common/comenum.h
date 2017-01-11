/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  comEnum.h;
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2017.01.10;
历史版本:  无;
*********************************************************************************************/
#ifndef __COM_ENUM_H
#define __COM_ENUM_H



/*******************************************宏定义********************************************/
#define    PVT_POINT_BUFFER_SIZE    256  
#define    RECIP_OF_DBL_RADIAN      0.1591549f    //π取值3.1415926
#define    PVT_FPGA_PWM_CLOCK       10000000      //10MHz

#define    QUBELEY_SN_LEN      14
#define    ERROR_CODE_LEN      6     //字节数
#define    SOFTWARE_VER_LEN    4
#define    FPGA_VER_LEN        2
#define    HARDWARE_VER_LEN    2
#define    BOOT_VER_LEN        2

#define    UART_BAUDRATE_NUM       10    //跟数组中值的个数对应
#define    UART_FLOW_CTL_NUM       10    //跟数组中值的个数对应
#define    UART_WORD_LEN_NUM       10    //跟数组中值的个数对应
#define    UART_STOP_BIT_NUM       10    //跟数组中值的个数对应
#define    UART_PARITY_NUM         10    //跟数组中值的个数对应

#define    CAN_ID_TYPE_NUM         2     //跟数组中值的个数对应
#define    CAN_BAUDRATE_NUM        8     //跟数组中值的个数对应

#define    DIGIT_SENSOR_NUM     10
#define    ANALOG_SENSOR_NUM    10



/***************************************常数和类型声明****************************************/
typedef void ( *timeOutFunc)(void);
typedef void (*SubCmdProFunc)(u8 cmdDataLen, u8 *pCmdData);



/***************************************常数和类型声明****************************************/
/*-------------命令系统枚举-------------*/
//主命令枚举
typedef enum
{
    CMD_LINK = 1,      //连接设置命令
    CMD_SYSTME,        //系统设置命令
    CMD_UART,          //RS232设置命令
    CMD_CAN,           //CAN设置命令
    CMD_MOTOR,         //电机设置命令
    CMD_ENCODER,       //编码器设置命令
    CMD_PVT,           //PVT设置命令
    CMD_TRAPZCURVE,    //梯形曲线设置命令
    CMD_MOTION,        //运行设置命令
    CMD_OUTOFSTEP,     //失步设置命令
    CMD_OTP,           //OTP设置命令
    CMD_DSENSOR,       //数字传感器设置命令
    CMD_ASENSOR,       //模拟传感器设置命令
    CMD_CALIBRATE,     //校准命令
    CMD_UPDATE,        //升级命令
    CMD_DEBUG,         //DEBUG命令
    CMD_RESERVE        //保留
    
}CmdTypeEnum;

//子命令枚举
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

/*-------------连接类型枚举-------------*/
typedef enum
{
    LINK_CAN,
    LINK_UART
    
}LinkTypeEnum;

/*-------------工作模式枚举-------------*/
typedef enum
{
    WORK_NORMAL = 0,    //普通模式
    WORK_UNIFORM,       //匀速模式
    WORK_POSITION,      //位置反馈模式
    WORK_TORQUE         //力矩反馈模式
    
}WorkModeEnum;

/*-------------上电状态枚举-------------*/
typedef enum
{
    POWERON_DEFAULT = 0,    //使用默认值
    POWERON_LAST,           //使用上次值
    
}PowerOnModeEnum;

/*-------------产品类型枚举-------------*/
typedef enum
{
    MODEL_SINGEL,    //单电机控制
    MODEL_MULTI      //多电机控制
    
}ProductModelEnum;

/*-------------UART波特率枚举-------------*/
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

/*-------------UART数据长度枚举-------------*/
typedef enum
{
    WORDLEN_8 = 0,    //4800bps
    WORDLEN_9
    
}WordLenEnum;

/*-------------UART流控制枚举-------------*/
typedef enum
{
    STOPBIT_10 = 0,
    STOPBIT_05,
    STOPBIT_20,
    STOPBIT_15
    
}StopBitEnum;

/*-------------UART校验方式枚举-------------*/
typedef enum
{
    PARITY_NONE = 0,
    PARITY_EVEN,
    PARITY_ODD
    
}ParityEnum;

/*-------------UART停止位枚举-------------*/
typedef enum
{
    FLOWCTL_NONE = 0,
    FLOWCTL_RTS,
    FLOWCTL_CTS,
    FLOWCTL_RTS_CTS
    
}FlowCtlEnum;

/*-------------CAN类型枚举-------------*/
typedef enum
{
    CAN_TYPE_A = 0,
    CAN_TYPE_B
    
}CanTypeEnum;

/*-------------CAN波特率枚举-------------*/
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


/*-------------电机步距角枚举-------------*/
typedef enum
{
    STEPANGLE_18 = 0,    //1.8°
    STEPANGLE_09,        //0.9°
    STEPANGLE_15,        //1.5°
    STEPANGLE_07         //0.75°
    
}StepAngleEnum;

/*-------------电机微步枚举-------------*/
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

/*-------------电机类型枚举-------------*/
typedef enum
{
    MOTOR_42,
    MOTOR_57,
    MOTOR_60
    
}MotorTypeEnum;

/*-------------编码器线数枚举-------------*/
typedef enum
{
    ECLINE_1000,   //1000线
    ECLINE_2000    //2000线
    
}EncoderLineEnum;

/*-------------编码器通道数枚举-------------*/
typedef enum
{
    ECCHAN_1,   //单通道
    ECCHAN_3    //三通道
    
}EncoderChanEnum;

/*-------------编码器类型枚举-------------*/
typedef enum
{
    ENCODER_NONE,    //无编码器
    ENCODER_INC,     //增量型编码器
    ENCODER_ABS      //绝对型编码器
    
}EncoderTypeEnum;

/*-------------PVT模式枚举-------------*/
typedef enum
{
    PVT_SINGEL,
    PVT_NCYCLE,
    PVT_INFINITY,
    PVT_FIFO
    
}PvtModeEnum;

/*-------------运行方向枚举-------------*/
typedef enum
{
    DIR_FORWARD = 0,
    DIR_REVERSE
    
}DirectionStruct;

/*-------------上报模式枚举-------------*/
typedef enum
{
    REPORT_OUTNUM = 0,
    REPORT_STEPS,
    REPORT_VELORITY,
    REPORT_TORQUE,
    REPORT_TEMP,
    REPORT_RESERVE
    
}ReportTypeEnum;

/*-------------上报周期枚举-------------*/
typedef enum
{
    PERIOD_20MS = 0,
    PERIOD_50MS,
    PERIOD_100MS,
    PERIOD_200MS,
    PERIOD_500MS,
    PERIOD_1000MS
    
}ReportPeriodEnum;

/*-------------触发类型枚举-------------*/
typedef enum
{
    DTYPE_RISE = 0,
    DTYPE_FALL,
    DTYPE_HIGH,
    DTYPE_LOW
    
}TriggerTypeEnum;

/*-------------传感器响应枚举-------------*/
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
