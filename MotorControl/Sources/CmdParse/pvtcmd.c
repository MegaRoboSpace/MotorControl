/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtcmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "pvtcmd.h"
#include "pvtparaverify.h"
#include "softtimer.h"
#include "protocolstack.h"



/****************************************外部变量声明*****************************************/
extern SoftTimerStr  g_pvtCalcEndTimer;
extern PvtInfoStruct g_pvtInfo;



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pPvtCmdFunc[PVTCMD_RESERVE];
SubCmdProFunc pTrapzCmdFunc[PVTCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: PvtModeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtModeSet(u8 cmdDataLen, u8 *pCmdData)
{
    PvtModeEnum pvtMode;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtModeVerify(cmdDataLen, pCmdData, (void *)&pvtMode))
    {
        g_pvtInfo.pvtMode = pvtMode;
    }
}



/*********************************************************************************************
函 数 名: PvtModeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtPointSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtPointSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: PvtPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtPositionSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtPositionSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 position;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtPositionVerify(cmdDataLen, pCmdData, (void *)&position))
    {
        if (g_pvtInfo.tailPoint < PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.pvtPoint[g_pvtInfo.tailPoint].position = position;
        }
    }
}


/*********************************************************************************************
函 数 名: PvtPositionQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtSpeedSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 speed;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtSpeedVerify(cmdDataLen, pCmdData, (void *)&speed))
    {
        if (g_pvtInfo.tailPoint < PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.pvtPoint[g_pvtInfo.tailPoint].speed = speed;
        }
    }
}


/*********************************************************************************************
函 数 名: PvtSpeedQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtTimeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtTimeSet(u8 cmdDataLen, u8 *pCmdData)
{
    f32 time;

    
    //进行参数验证
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
函 数 名: PvtTimeQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtStartPointSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtStartPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 startPoint;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtStartPointVerify(cmdDataLen, pCmdData, (void *)&startPoint))
    {
        g_pvtInfo.startPoint = startPoint;
    }
}


/*********************************************************************************************
函 数 名: PvtStartPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtEndPointSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtEndPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 endPoint;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtEndPointVerify(cmdDataLen, pCmdData, (void *)&endPoint))
    {
        g_pvtInfo.endPoint = endPoint;
    }
}


/*********************************************************************************************
函 数 名: PvtEndPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtNcyclesSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtNcyclesSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 ncycle;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtNcyclesVerify(cmdDataLen, pCmdData, (void *)&ncycle))
    {
        g_pvtInfo.ncycle = ncycle;
    }
}


/*********************************************************************************************
函 数 名: PvtNcyclesQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtRemainPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtOutputPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtWarnPointSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtWarnPointSet(u8 cmdDataLen, u8 *pCmdData)
{
    u32 warnPoint;

    
    //进行参数验证
    if (PARA_VERIFY_NO_ERROR == PvtWarnPointVerify(cmdDataLen, pCmdData, (void *)&warnPoint))
    {
        g_pvtInfo.warnPoint = warnPoint;
    }
}


/*********************************************************************************************
函 数 名: PvtWarnPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtWarn;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtClear;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtCalcEnd;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void PvtCalcEnd(u8 cmdDataLen, u8 *pCmdData)
{
    //结束软定时器
    StimerDelete(&g_pvtCalcEndTimer);

    //通知FPGA开始输出
}


/*********************************************************************************************
函 数 名: PvtCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: PvtCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: TrapzPointSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void TrapzPointSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: TrapzPointQuery;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void TrapzPointQuery(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: TrapzPositionSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void TrapzPositionSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: TrapzSpeedSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void TrapzSpeedSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: TrapzTimeSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void TrapzTimeSet(u8 cmdDataLen, u8 *pCmdData)
{

}


/*********************************************************************************************
函 数 名: TrapzCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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
函 数 名: TrapzCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
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



/*******************************************文件尾********************************************/
