/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  pvtalgorithm.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.08.15;
历史版本:  无;
*********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pvtalgorithm.h"



/****************************************外部变量声明*****************************************/
extern volatile u64    g_systemMilliSecTick;
extern PvtInfoStruct   g_pvtInfo;
extern MotorInfoStruct g_motorInfo;



/*****************************************局部宏定义******************************************/
#define    SQUARE(num)               (num * num)
#define    CUBE(num)                 (num * num * num)
#define    TARGET_REAL_OFFSET        0.01           //计算PVT每步速度是，实际步数和目标步数之间最大误差



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
#if DEBUG_MODE
u32  totalOutput = 0;
bool bCalibrate = false;
f32  outputSpeed[12000] = {0};
u32  indexOffset = 2;
u64  calcTime = 0;
#endif



/******************************************函数实现*******************************************/
/*********************************************************************************************
函数名：    PvtPointCalc；
实现功能：  计算某个时刻的电机需要到达的位置；
输入参数：  无；
输出参数：  无；   
函数返回值：无；  
*********************************************************************************************/
inline void PvtPointCalc(f32 startPosn, f32 startSpeed, f32 endPosn, f32 endSpeed, f32 startTime,
                  f32 endTime, f32 radianToStep, DirectionStruct direction)
{
    u32 realOutput;
    f32 calcOutput;
    u32 i;
    u32 calcCount;
    f32 curTime;
    
    f32 poseOffset;
    f32 lastTime;
    f32 maxTime;
    f32 minTime;

    f32 motionTime;
    f32 cubeMotionTime;
    f32 squareMotionTime;  
    f32 cubeCurTime;
    f32 squareCurTime;
    f32 curPost;   
    f32 threeTermCoef;
    f32 twoTermCoef;
    

    //转换量纲
    startPosn  *= radianToStep;
    startSpeed *= radianToStep;
    endPosn    *= radianToStep;
    endSpeed   *= radianToStep;
    poseOffset = endPosn - startPosn;
    calcCount = (u32)endPosn - (u32)startPosn;
    motionTime = endTime - startTime;

    //初始化时间
    lastTime = g_pvtInfo.lastStepTime - startTime;
    minTime = 0;
    if (1 == g_pvtInfo.targetStep)    //第一步的时候需要在全时间范围内查找
    {
        curTime = motionTime / poseOffset;
        maxTime = motionTime;
    }
    else
    {
        curTime = lastTime;
        maxTime = curTime + g_pvtInfo.lastStepSpeed * 2;
    }

    //提前算好三次项和二次项的系数
    cubeMotionTime = CUBE(motionTime);
    squareMotionTime = SQUARE(motionTime);
    threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
    twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

    for (i = 0;i < calcCount;i++)
    {        
        curTime += g_pvtInfo.lastStepSpeed;    //在上一步的时间轴上加上上一步的速度作为这一步的计算初始时间
    
        //setpInfo = PvtPointCalc(startPost, startSpeed, threeTermCoef, twoTermCoef, curTime);
        cubeCurTime = CUBE(curTime);
        squareCurTime = SQUARE(curTime);
        curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
        while (fabs(curPost - g_pvtInfo.targetStep) > TARGET_REAL_OFFSET)    //跟目标值得误差太大继续计算
        {
            if ((curPost - g_pvtInfo.targetStep) > TARGET_REAL_OFFSET)
            {
                maxTime = curTime;
                curTime = (curTime + minTime) / 2;
            }
            else
            {
                minTime = curTime;
                curTime = (curTime + maxTime) / 2;
            }
        
            //setpInfo = PvtPointCalc(startPost, startSpeed, threeTermCoef, twoTermCoef, curTime);
            cubeCurTime = CUBE(curTime);
            squareCurTime = SQUARE(curTime);
            curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
        }    
        g_pvtInfo.targetStep++;    //开始计算下一个目标
        
        g_pvtInfo.lastStepSpeed = curTime - lastTime;    //记录这一步和上一步的间隔时间，也就是速度

#if DEBUG_MODE
        outputSpeed[g_pvtInfo.targetStep - indexOffset] = g_pvtInfo.lastStepSpeed;
#endif

        minTime = curTime;
        lastTime = curTime;
        maxTime = curTime + g_pvtInfo.lastStepSpeed * 2;
        
        //时间的补偿问题:理论上讲用时间作为速度是没有误差的，而误差来源于归一化后的四舍五入
        calcOutput = g_pvtInfo.lastStepSpeed * g_pvtInfo.fpgaPwmClock;

        //做个上下限保护
        if (calcOutput > g_pvtInfo.fpgaPwmClock)
        {
            calcOutput = g_pvtInfo.fpgaPwmClock;
            
            //系统错误码置位 NICK MARK
        }
        else if (calcOutput < 1)
        {
            calcOutput = 1;
            
            //系统错误码置位 NICK MARK
        }
        
        realOutput = (u32)(calcOutput + 0.5f);    //实际输出值是计算的输出值进行四舍五入之后的值
        g_pvtInfo.errorTime += calcOutput - realOutput;
        if (g_pvtInfo.errorTime > 1)    //正的，需要在当前步补一
        {
            realOutput++;
            g_pvtInfo.errorTime--;
        }
        else if (g_pvtInfo.errorTime < -1)    //负的，需要在当前步减一
        {
            realOutput--;
            g_pvtInfo.errorTime++;
        }

        //对realOutput进行包装下，有效位数为24bits，第25bit为方向 NICK MARK

#if DEBUG_MODE
        totalOutput += realOutput;
#endif
    }
    g_pvtInfo.lastStepTime = curTime + startTime; 
}


/*********************************************************************************************
函数名：    PvtResultCalc；
实现功能：  计算某个时刻的电机需要到达的速度；
输入参数：  无；
输出参数：  无；   
函数返回值：无；  
*********************************************************************************************/
void PvtResultCalc(WorkModeEnum workMode)
{
    DirectionStruct direction;
    bool bCalcPvt = false;
    bool bHaveRemain = false;
    
    u16 headIndex;
    u16 tailIndex;

    u32 i;
    u32 motionCount;
    
    f32 startPosn;
    f32 startSpeed;
    f32 endPosn;
    f32 endSpeed;
    f32 startTime;
    f32 endTime;
    f32 motionTime;
    f32 poseOffset;
    
    f32 motionPosn;
    f32 lineStartPosn;
    f32 lineStartSpeed;
    f32 lineEndSpeed;
    f32 lineStartTime;
    
    f32 curTime;
    f32 lastTime;
    f32 maxTime;
    f32 minTime;

    f32 cubeMotionTime;
    f32 squareMotionTime;  
    f32 cubeCurTime;
    f32 squareCurTime;
    f32 curPost;   
    f32 threeTermCoef;
    f32 twoTermCoef;
    f32 radianToStep;
    

    //获取PVT列表的头和尾
    headIndex = g_pvtInfo.headPoint;

    if (headIndex != g_pvtInfo.tailPoint)    //头不等于尾说明还有有效数据
    {
#if DEBUG_MODE
        //计算开始 FOR DEBUG
        GPIOB->BSRR = GPIO_Pin_5;

        if (headIndex != 0)
        {
            indexOffset = g_pvtInfo.targetStep + 1;
        }

        calcTime = g_systemMilliSecTick;
#endif         
        
        //一次就计算一段，然后出去处理下别的任务
        tailIndex = headIndex + 1;
        if (tailIndex >= PVT_POINT_BUFFER_SIZE)
        {
            tailIndex = 0;
        }

        if (1 == g_pvtInfo.targetStep)
        {
            //记录下PVT初始点的位置
            g_pvtInfo.startPosition = g_pvtInfo.pvtPoint[headIndex].position;
        }

        //获取当前要计算的这一段PVT的相关数据
        startPosn = g_pvtInfo.pvtPoint[headIndex].position - g_pvtInfo.startPosition;
        startSpeed = g_pvtInfo.pvtPoint[headIndex].speed;
        endPosn  = g_pvtInfo.pvtPoint[tailIndex].position - g_pvtInfo.startPosition;
        endSpeed = g_pvtInfo.pvtPoint[tailIndex].speed;
        startTime = g_pvtInfo.pvtPoint[headIndex].time;
        endTime = g_pvtInfo.pvtPoint[tailIndex].time;
        motionTime = endTime - startTime;
        lineStartTime = startTime;

        poseOffset = endPosn - startPosn;
        if (poseOffset < 0)
        {
            direction = DIR_REVERSE;
        }
        else
        {
            direction = DIR_FORWARD;
        }
        
        if (direction != g_pvtInfo.lastStepDir)    //反向运动
        {
            //反向之后目标步数变为1，更新方向
            g_pvtInfo.targetStep = 1;
            g_pvtInfo.lastStepDir = direction;
        }

        //如果校准了，也就必然有编码器
        if (bCalibrate)
        {
            //将初始PVT进行分段(反馈模式不需要进行分段)
            if (WORK_POSITION != workMode)
            {
                motionPosn = poseOffset * g_motorInfo.encoderInfo.linePerRadian + g_pvtInfo.remainLine;
                motionCount = (u32)motionPosn;
                if (motionCount != motionPosn)
                {
                    bHaveRemain = true;
                    g_pvtInfo.remainLine = motionPosn - motionCount;
                }

                //量纲转换下
                radianToStep = g_motorInfo.encoderInfo.linePerRadian;
                startPosn  *= radianToStep;
                startSpeed *= radianToStep;
                endPosn    *= radianToStep;
                endSpeed   *= radianToStep;
                poseOffset *= radianToStep;

                lineStartPosn  = startPosn;
                lineStartSpeed = startSpeed;

                //初始化时间
                minTime = 0;
                lastTime = g_pvtInfo.lastLineTime - startTime;
                if (1 == g_pvtInfo.targetLine)    //第一步的时候需要在全时间范围内查找
                {
                    curTime = motionTime / motionPosn;
                    maxTime = motionTime;
                }
                else
                {
                    curTime = lastTime;
                    maxTime = curTime + g_pvtInfo.lastLineSpeed * 2;
                }

                //提前算好三次项和二次项的系数
                cubeMotionTime = CUBE(motionTime);
                squareMotionTime = SQUARE(motionTime);
                threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
                twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

                for (i = 0;i < motionCount;i++)
                {
                    curTime += g_pvtInfo.lastLineSpeed;    //在上一线的时间轴上加上上一线的速度作为这一线的计算初始时间
                
                    cubeCurTime = CUBE(curTime);
                    squareCurTime = SQUARE(curTime);
                    curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
                    while (fabs(curPost - g_pvtInfo.targetLine) > TARGET_REAL_OFFSET)    //跟目标值得误差太大继续计算
                    {
                        if ((curPost - g_pvtInfo.targetLine) > TARGET_REAL_OFFSET)
                        {
                            maxTime = curTime;
                            curTime = (curTime + minTime) / 2;
                        }
                        else
                        {
                            minTime = curTime;
                            curTime = (curTime + maxTime) / 2;
                        }
                    
                        cubeCurTime = CUBE(curTime);
                        squareCurTime = SQUARE(curTime);
                        curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
                    }
                    //求取下速度
                    lineEndSpeed = 3 * threeTermCoef * squareCurTime + 2 * twoTermCoef * curTime + startSpeed;
                    
                    g_pvtInfo.targetLine++;    //开始计算下一个目标
                    
                    g_pvtInfo.lastLineSpeed = curTime - lastTime;    //记录这一线和上一线的间隔时间，也就是速度
                    lastTime = curTime;
                    minTime  = curTime;
                    maxTime  = curTime + g_pvtInfo.lastLineSpeed * 2;

                    //计算当前段
                    radianToStep = 128;    //128 for debug NICK MARK
                    PvtPointCalc(lineStartPosn, lineStartSpeed, curPost, lineEndSpeed, lineStartTime,
                                 curTime + startTime, radianToStep, direction);
                    lineStartPosn  = curPost;
                    lineStartSpeed = lineEndSpeed;
                    lineStartTime = curTime + startTime;
                }
                g_pvtInfo.lastLineTime = curTime + startTime;
                
                //计算最后一段
                if (bHaveRemain)
                {
                    radianToStep = 128;    //128 for debug NICK MARK
                    PvtPointCalc(lineStartPosn, lineStartSpeed, endPosn, endSpeed, lineStartTime,
                                 endTime, radianToStep, direction);
                }
            }
            else
            {
                radianToStep = g_motorInfo.encoderInfo.linePerRadian;
                bCalcPvt = true;
            }
        }
        else    //没有校准的话不需要按照编码器每线之间的弧度将初始PVT进行分段
        {
            //没有编码器或者有编码器，PVT模式为普通和匀速
            if ((ENCODER_NONE == g_motorInfo.encoderInfo.type) || (WORK_POSITION != workMode))
            {
                //根据总步数计算转换系数
                radianToStep = g_motorInfo.totalSteps * RECIP_OF_DBL_RADIAN;
                bCalcPvt = true;
            }
            else
            {
                //
                radianToStep = g_motorInfo.encoderInfo.linePerRadian;
                bCalcPvt = true;
            }
        }

        if (bCalcPvt)
        {            
            //计算一段PVT
            PvtPointCalc(startPosn, startSpeed, endPosn, endSpeed, startTime,
                         endTime, radianToStep, direction);
        }        
    
        g_pvtInfo.headPoint++;
        if (g_pvtInfo.headPoint >= PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.headPoint = 0;
        }

        //最后的不足一步的时间需要补上 NICK MARK
        
        if (g_pvtInfo.headPoint == g_pvtInfo.tailPoint)    //头尾相等则说明List中没有有效数据了
        {
            g_pvtInfo.targetStep    = 1;
            g_pvtInfo.lastStepSpeed = 0;
            g_pvtInfo.lastStepTime  = 0;
            g_pvtInfo.errorTime     = 0;
            g_pvtInfo.lastStepDir   = DIR_FORWARD;
        }

#if DEBUG_MODE
        calcTime = g_systemMilliSecTick - calcTime;
        
        //计算结束 FOR DEBUG
        GPIOB->BRR = GPIO_Pin_5;
#endif
    }
}



/*******************************************文件尾********************************************/
