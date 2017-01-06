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
#include "pvtparaverify.h"



/****************************************外部变量声明*****************************************/
extern volatile u64  g_systemMilliSecTick;
extern PvtInfoStruct g_pvtInfo;



/*****************************************局部宏定义******************************************/
#define    SQUARE(num)               (num * num)
#define    CUBE(num)                 (num * num * num)
#define    TARGET_REAL_OFFSET        0.1           //计算PVT每步速度是，实际步数和目标步数之间最大误差



/*************************************局部常量和类型定义**************************************/
typedef struct
{
    f32             setpIndex;     //步数编号
    DirectionStruct direction;
    
}SetpInfoStr;



/******************************************局部变量*******************************************/
SetpInfoStr setpInfo;

#if DEBUG_MODE
u32 totalOutput = 0;
#endif



/******************************************函数实现*******************************************/
/*********************************************************************************************
函数名：    PvtPointCalc；
实现功能：  计算某个时刻的电机需要到达的位置；
输入参数：  无；
输出参数：  无；   
函数返回值：无；  
*********************************************************************************************/
SetpInfoStr PvtPointCalc(f32 startPost, f32 startSpeed, f32 threeTermCoef, f32 twoTermCoef, f32 curTime)
{    
    f32 curPost;    
    f32 cubeCurTime = CUBE(curTime);
    f32 squareCurTime = SQUARE(curTime);
    SetpInfoStr setpInfo;


    //p(t) = (2(p0 - p1)/T-3 + (v0 + v1)/T-2)*t-3 + (3(p1 - p0)/T-2 - (2v0 + v1)/T) * t-2 + v0t + p0
    //T-3代表T的三次方，其他类同，同一段中每个项式的系数是一样的，所以在调用函数前已经计算完了
    curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;


    //算完后位置如果是负数说明是反向运动
    if (curPost < 0)
    {
        setpInfo.direction = REVERSE;
        curPost = -curPost;
    }
    else
    {
        setpInfo.direction = FORWARD;
    }
    
    setpInfo.setpIndex = curPost;

    return setpInfo;
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
    u32 realOutput;
    f32 calcOutput;
    u64 i;
    u16 headIndex;
    u16 tailIndex;
    f32 startPost;
    f32 endPost;
    f32 startSpeed;
    f32 endSpeed;
    f32 curTime;
    f32 motionTime;
    
    f32 poseOffset;
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
    

    //获取PVT列表的头和尾
    headIndex = g_pvtInfo.headPoint;

    if (headIndex != g_pvtInfo.tailPoint)    //头不等于尾说明还有有效数据
    {
#if DEBUG_MODE
        //计算开始 FOR DEBUG
        GPIOB->BSRR = GPIO_Pin_5;
        g_pvtInfo.targetStep = 1;
#endif
        
        //速度为0时，起始速度按0算，否则按照上次计算的最后一步的速度算
        if (0 == g_pvtInfo.pvtPoint[headIndex].speed)
        {
            startSpeed = 0;
        }
        else
        {
            startSpeed = 1 / g_pvtInfo.lastStepSpeed;    //存储的是时间，所以需要倒数
        }
        startPost = g_pvtInfo.targetStep - 1;    //初始时targetStep为1，位置就为0
        
        
        //一次就计算一段，然后出去处理下别的任务
        tailIndex = headIndex + 1;
        if (tailIndex >= PVT_POINT_BUFFER_SIZE)
        {
            tailIndex = 0;
        }

        //根据工作模式将初始的PVT分段 NICK MARK
        if (WORK_TORQUE != workMode)
        {
            //先将当前PVT对应的位置按照编码器线数进行分段

            //
            if ((WORK_NORMAL == workMode) || (WORK_UNIFORM == workMode))
            {
                //
                //if (/*有校准数据*/)
                {
                    //计算每段的RADIAN_TO_STEP
                }
                //else
                {
                    //RADIAN_TO_STEP = 一圈的步数 / 2π
                }
            }
            else
            {
                //RADIAN_TO_STEP = 1
            }
            
        }

        /**********************************一段PVT计算开始***********************************************/        
        //终止位置、速度
        endPost  = g_pvtInfo.pvtPoint[tailIndex].position * g_pvtInfo.radianToStep - startPost;
        endSpeed = g_pvtInfo.pvtPoint[tailIndex].speed * g_pvtInfo.radianToStep;
        
        motionTime = g_pvtInfo.pvtPoint[tailIndex].time - g_pvtInfo.lastStepTime;    //上次计算的结束时间

        poseOffset = endPost - startPost;     //代表了这一段PVT中的步数，也就是要求解出来的步数
        if (poseOffset < 0)
        {
            direction = REVERSE;
        }
        else
        {
            direction = FORWARD;
        }
        
        if (direction != g_pvtInfo.lastStepDir)    //反向运动
        {
            //反向之后目标步数变为1，更新方向
            g_pvtInfo.targetStep = 1;
            g_pvtInfo.lastStepDir = direction;
        }
        
        
        //初始化时间
        lastTime = 0;
        minTime = 0;
        if (1 == g_pvtInfo.targetStep)    //第一步的时候需要在全时间范围内查找
        {
            curTime = motionTime / poseOffset;
            maxTime = motionTime;
        }
        else
        {
            curTime = g_pvtInfo.lastStepSpeed;
            maxTime = curTime + g_pvtInfo.lastStepSpeed;
        }

        //提前算好三次项和二次项的系数
        cubeMotionTime = CUBE(motionTime);
        squareMotionTime = SQUARE(motionTime);
        threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
        twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

        for (i = 0;i < (u32)poseOffset;i++)
        {
            cubeCurTime = CUBE(curTime);
            squareCurTime = SQUARE(curTime);
            
            curTime += g_pvtInfo.lastStepSpeed;    //在上一步的时间轴上加上上一步的速度作为这一步的计算初始时间
        
            //setpInfo = PvtPointCalc(startPost, startSpeed, threeTermCoef, twoTermCoef, curTime);
            curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;
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
                curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;
            }    
            g_pvtInfo.targetStep++;    //开始计算下一个目标
            
            g_pvtInfo.lastStepSpeed = curTime - lastTime;    //记录这一步和上一步的间隔时间，也就是速度
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
        g_pvtInfo.lastStepTime = curTime;
        
        g_pvtInfo.headPoint++;
        if (g_pvtInfo.headPoint >= PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.headPoint = 0;
        }
        /**********************************一段PVT计算结束***********************************************/ 

        //如果PVT List中还有未计算的点，则保存本次计算最后步数和其速度
        //作为下次计算的起始，否则清零
        if (g_pvtInfo.headPoint == g_pvtInfo.tailPoint)    //头尾相等则说明List中没有有效数据了
        {
            g_pvtInfo.targetStep    = 1;
            g_pvtInfo.lastStepSpeed = 0;
            g_pvtInfo.lastStepTime  = 0;
            g_pvtInfo.errorTime     = 0;
            g_pvtInfo.lastStepDir   = FORWARD;
        }

#if DEBUG_MODE
        //计算结束 FOR DEBUG
        GPIOB->BRR = GPIO_Pin_5;
#endif
    }
}


/*********************************************************************************************
函数名：    PvtDebugMode；
实现功能：  计算某个时刻的电机需要到达的速度；
输入参数：  无；
输出参数：  无；   
函数返回值：无；  
*********************************************************************************************/
void PvtDebugMode(void)
{
    
}



/*******************************************文件尾********************************************/
