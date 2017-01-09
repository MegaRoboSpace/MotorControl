/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtcmd.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.12.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <string.h>
#include "pvtcmd.h"
#include "pvtparaverify.h"
#include "softtimer.h"
#include "protocolstack.h"



/****************************************�ⲿ��������*****************************************/
extern SoftTimerStr  g_pvtCalcEndTimer;
extern PvtInfoStruct g_pvtInfo;



/*****************************************�ֲ��궨��******************************************/



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
SubCmdProFunc pPvtCmdFunc[PVTCMD_RESERVE];
SubCmdProFunc pTrapzCmdFunc[PVTCMD_RESERVE];



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
�� �� ��: PvtModeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtModeSet(u8 cmdDataLen, u8 *pCmdData)
{
    PvtModeEnum pvtMode;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtModeVerify(cmdDataLen, pCmdData, (void *)&pvtMode))
    {
        g_pvtInfo.pvtMode = pvtMode;
    }
}



/*********************************************************************************************
�� �� ��: PvtModeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtModeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_MODEQ;
    dataLen = sizeof(g_pvtInfo.pvtMode);
    pData = (u8 *)&g_pvtInfo.pvtMode;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtPointSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtPointSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: PvtPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u16 index = *(u16 *)pCmdData;
    u8  dataLen;
    u8  *pData;

    
    if ((sizeof(u16) == cmdDataLen) && (index < PVT_POINT_BUFFER_SIZE))
    {
        cmdMainType = CMD_PVT;
        
        cmdSubType = PVTCMD_POSNQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].position);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].position;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
        
        cmdSubType = PVTCMD_SPEEDQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].speed);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].speed;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
        
        cmdSubType = PVTCMD_TIMEQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].time);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].time;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: PvtPositionSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 position;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtPositionVerify(cmdDataLen, pCmdData, (void *)&position))
    {
        if (g_pvtInfo.tailPoint < PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.pvtPoint[g_pvtInfo.tailPoint].position = position;
        }
    }
}


/*********************************************************************************************
�� �� ��: PvtPositionQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtPositionQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u16 index = *(u16 *)pCmdData;
    u8  dataLen;
    u8  *pData;

    
    if ((sizeof(u16) == cmdDataLen) && (index < PVT_POINT_BUFFER_SIZE))
    {
        cmdMainType = CMD_PVT;
        cmdSubType = PVTCMD_POSNQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].position);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].position;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: PvtSpeedSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 speed;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtSpeedVerify(cmdDataLen, pCmdData, (void *)&speed))
    {
        if (g_pvtInfo.tailPoint < PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.pvtPoint[g_pvtInfo.tailPoint].speed = speed;
        }
    }
}


/*********************************************************************************************
�� �� ��: PvtSpeedQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtSpeedQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u16 index = *(u16 *)pCmdData;
    u8  dataLen;
    u8  *pData;

    
    if ((sizeof(u16) == cmdDataLen) && (index < PVT_POINT_BUFFER_SIZE))
    {
        cmdMainType = CMD_PVT;
        cmdSubType = PVTCMD_SPEEDQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].speed);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].speed;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: PvtTimeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtTimeSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 time;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtTimeVerify(cmdDataLen, pCmdData, (void *)&time))
    {
        if (g_pvtInfo.tailPoint < PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.pvtPoint[g_pvtInfo.tailPoint].time = time;
            g_pvtInfo.tailPoint++;
            g_pvtInfo.remainPoint--;
            if ((PVT_POINT_BUFFER_SIZE == g_pvtInfo.tailPoint) &&
                (g_pvtInfo.startPoint > 0))
            {
                g_pvtInfo.tailPoint = 0;
                g_pvtInfo.bRewind = true;
            }
        }
    }
}


/*********************************************************************************************
�� �� ��: PvtTimeQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtTimeQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u16 index = *(u16 *)pCmdData;
    u8  dataLen;
    u8  *pData;

    
    if ((sizeof(u16) == cmdDataLen) && (index < PVT_POINT_BUFFER_SIZE))
    {
        cmdMainType = CMD_PVT;
        cmdSubType = PVTCMD_TIMEQ;
        dataLen = sizeof(g_pvtInfo.pvtPoint[index].time);
        pData = (u8 *)&g_pvtInfo.pvtPoint[index].time;
        CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: PvtStartPointSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtStartPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 startPoint;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtStartPointVerify(cmdDataLen, pCmdData, (void *)&startPoint))
    {
        g_pvtInfo.startPoint = startPoint;
    }
}


/*********************************************************************************************
�� �� ��: PvtStartPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtStartPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_STARTPOINTQ;
    dataLen = sizeof(g_pvtInfo.startPoint);
    pData = (u8 *)&g_pvtInfo.startPoint;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtEndPointSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtEndPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 endPoint;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtEndPointVerify(cmdDataLen, pCmdData, (void *)&endPoint))
    {
        g_pvtInfo.endPoint = endPoint;
    }
}


/*********************************************************************************************
�� �� ��: PvtEndPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtEndPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_ENDPOINTQ;
    dataLen = sizeof(g_pvtInfo.endPoint);
    pData = (u8 *)&g_pvtInfo.endPoint;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtNcyclesSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtNcyclesSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 ncycle;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtNcyclesVerify(cmdDataLen, pCmdData, (void *)&ncycle))
    {
        g_pvtInfo.ncycle = ncycle;
    }
}


/*********************************************************************************************
�� �� ��: PvtNcyclesQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtNcyclesQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_NCYCLESQ;
    dataLen = sizeof(g_pvtInfo.ncycle);
    pData = (u8 *)&g_pvtInfo.ncycle;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtRemainPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtRemainPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_REMAINPOINTQ;
    dataLen = sizeof(g_pvtInfo.remainPoint);
    pData = (u8 *)&g_pvtInfo.remainPoint;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtOutputPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtOutputPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_OUTPUTPOINTQ;
    dataLen = sizeof(g_pvtInfo.outputPoint);
    pData = (u8 *)&g_pvtInfo.outputPoint;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtWarnPointSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtWarnPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 warnPoint;

    
    //���в�����֤
    if (PARA_VERIFY_NO_ERROR == PvtWarnPointVerify(cmdDataLen, pCmdData, (void *)&warnPoint))
    {
        g_pvtInfo.warnPoint = warnPoint;
    }
}


/*********************************************************************************************
�� �� ��: PvtWarnPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtWarnPointQuery(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;
    u8 dataLen;
    u8 *pData;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_WARNPOINTQ;
    dataLen = sizeof(g_pvtInfo.warnPoint);
    pData = (u8 *)&g_pvtInfo.warnPoint;
    CmdFrameSend(cmdMainType, cmdSubType, dataLen, pData);
}


/*********************************************************************************************
�� �� ��: PvtWarn;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtWarn(u8 cmdDataLen, u8 *pCmdData)
{
    CmdTypeEnum cmdMainType;
    PvtCmdSubTypeEnum cmdSubType;

    
    cmdMainType = CMD_PVT;
    cmdSubType = PVTCMD_WARN;
    CmdFrameSend(cmdMainType, cmdSubType, 0, NULL);
}


/*********************************************************************************************
�� �� ��: PvtClear;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtClear(u8 cmdDataLen, u8 *pCmdData)
{    
    g_pvtInfo.bRewind = false;
    memset(g_pvtInfo.pvtPoint, 0, sizeof(g_pvtInfo.pvtPoint));
    g_pvtInfo.headPoint = 0;
    g_pvtInfo.tailPoint = 0;
    g_pvtInfo.remainPoint = 0;
}


/*********************************************************************************************
�� �� ��: PvtCalcEnd;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtCalcEnd(u8 cmdDataLen, u8 *pCmdData)
{
    //������ʱ��
    StimerDelete(&g_pvtCalcEndTimer);

    //֪ͨFPGA��ʼ���
}


/*********************************************************************************************
�� �� ��: PvtCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtCmdInit(void)
{
    pPvtCmdFunc[PVTCMD_MODE]         = PvtModeSet;
    pPvtCmdFunc[PVTCMD_MODEQ]        = PvtModeQuery;
    pPvtCmdFunc[PVTCMD_POINT]        = PvtPointSet;
    pPvtCmdFunc[PVTCMD_POSN]         = PvtPositionSet;
    pPvtCmdFunc[PVTCMD_POSNQ]        = PvtPositionQuery;
    pPvtCmdFunc[PVTCMD_SPEED]        = PvtSpeedSet;
    pPvtCmdFunc[PVTCMD_SPEEDQ]       = PvtSpeedQuery;
    pPvtCmdFunc[PVTCMD_TIME]         = PvtTimeSet;
    pPvtCmdFunc[PVTCMD_TIMEQ]        = PvtTimeQuery;
    pPvtCmdFunc[PVTCMD_REMAINPOINTQ] = PvtRemainPointQuery;
    pPvtCmdFunc[PVTCMD_OUTPUTPOINTQ] = PvtOutputPointQuery;
    pPvtCmdFunc[PVTCMD_STARTPOINT]   = PvtStartPointSet;
    pPvtCmdFunc[PVTCMD_STARTPOINTQ]  = PvtStartPointQuery;
    pPvtCmdFunc[PVTCMD_ENDPOINT]     = PvtEndPointSet;
    pPvtCmdFunc[PVTCMD_ENDPOINTQ]    = PvtEndPointQuery;
    pPvtCmdFunc[PVTCMD_NCYCLES]      = PvtNcyclesSet;
    pPvtCmdFunc[PVTCMD_NCYCLESQ]     = PvtNcyclesQuery;
    pPvtCmdFunc[PVTCMD_WARNPOINT]    = PvtWarnPointSet;
    pPvtCmdFunc[PVTCMD_WARNPOINTQ]   = PvtWarnPointQuery;
    pPvtCmdFunc[PVTCMD_CLEAR]        = PvtClear;
    pPvtCmdFunc[PVTCMD_WARN]         = PvtWarn;
    pPvtCmdFunc[PVTCMD_CALCEND]      = PvtCalcEnd;
}

            
/*********************************************************************************************
�� �� ��: PvtCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void PvtCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < PVTCMD_RESERVE) && (pPvtCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pPvtCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}


/*********************************************************************************************
�� �� ��: TrapzPointSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzPointSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: TrapzPointQuery;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzPointQuery(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: TrapzPositionSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzPositionSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: TrapzSpeedSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: TrapzTimeSet;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzTimeSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
�� �� ��: TrapzCmdInit;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzCmdInit(void)
{
    pPvtCmdFunc[TRAPZCMD_POINT]  = TrapzPointSet;
    pPvtCmdFunc[TRAPZCMD_POINTQ] = TrapzPointQuery;
    pPvtCmdFunc[TRAPZCMD_POSN]   = TrapzPositionSet;
    pPvtCmdFunc[TRAPZCMD_SPEED]  = TrapzSpeedSet;
    pPvtCmdFunc[TRAPZCMD_TIME]   = TrapzTimeSet;
}

            
/*********************************************************************************************
�� �� ��: TrapzCmdProc;
ʵ�ֹ���: ��; 
�������: ��;
�������: ��;
�� �� ֵ: ��;
˵    ��: ��;
*********************************************************************************************/
void TrapzCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < TRAPZCMD_RESERVE) && (pTrapzCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pTrapzCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************�ļ�β********************************************/
