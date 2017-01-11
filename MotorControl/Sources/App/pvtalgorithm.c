/*********************************************************************************************
Copyright (C) 2016������þ٤�����˿Ƽ����޹�˾
�� �� ��:  pvtalgorithm.c��
��������:  ;
�����б�:  ;
��ǰ�汾:  1.0.0;
�汾�Ķ�:  ;
��    ��:  CJ;
�������:  2016.08.15;
��ʷ�汾:  ��;
*********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pvtalgorithm.h"



/****************************************�ⲿ��������*****************************************/
extern volatile u64    g_systemMilliSecTick;
extern PvtInfoStruct   g_pvtInfo;
extern MotorInfoStruct g_motorInfo;



/*****************************************�ֲ��궨��******************************************/
#define    SQUARE(num)               (num * num)
#define    CUBE(num)                 (num * num * num)
#define    TARGET_REAL_OFFSET        0.01           //����PVTÿ���ٶ��ǣ�ʵ�ʲ�����Ŀ�경��֮��������



/*************************************�ֲ����������Ͷ���**************************************/



/******************************************�ֲ�����*******************************************/
#if DEBUG_MODE
u32  totalOutput = 0;
bool bCalibrate = false;
f32  outputSpeed[12000] = {0};
u32  indexOffset = 2;
u64  calcTime = 0;
#endif



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
��������    PvtPointCalc��
ʵ�ֹ��ܣ�  ����ĳ��ʱ�̵ĵ����Ҫ�����λ�ã�
���������  �ޣ�
���������  �ޣ�   
��������ֵ���ޣ�  
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
    

    //ת������
    startPosn  *= radianToStep;
    startSpeed *= radianToStep;
    endPosn    *= radianToStep;
    endSpeed   *= radianToStep;
    poseOffset = endPosn - startPosn;
    calcCount = (u32)endPosn - (u32)startPosn;
    motionTime = endTime - startTime;

    //��ʼ��ʱ��
    lastTime = g_pvtInfo.lastStepTime - startTime;
    minTime = 0;
    if (1 == g_pvtInfo.targetStep)    //��һ����ʱ����Ҫ��ȫʱ�䷶Χ�ڲ���
    {
        curTime = motionTime / poseOffset;
        maxTime = motionTime;
    }
    else
    {
        curTime = lastTime;
        maxTime = curTime + g_pvtInfo.lastStepSpeed * 2;
    }

    //��ǰ���������Ͷ������ϵ��
    cubeMotionTime = CUBE(motionTime);
    squareMotionTime = SQUARE(motionTime);
    threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
    twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

    for (i = 0;i < calcCount;i++)
    {        
        curTime += g_pvtInfo.lastStepSpeed;    //����һ����ʱ�����ϼ�����һ�����ٶ���Ϊ��һ���ļ����ʼʱ��
    
        //setpInfo = PvtPointCalc(startPost, startSpeed, threeTermCoef, twoTermCoef, curTime);
        cubeCurTime = CUBE(curTime);
        squareCurTime = SQUARE(curTime);
        curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
        while (fabs(curPost - g_pvtInfo.targetStep) > TARGET_REAL_OFFSET)    //��Ŀ��ֵ�����̫���������
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
        g_pvtInfo.targetStep++;    //��ʼ������һ��Ŀ��
        
        g_pvtInfo.lastStepSpeed = curTime - lastTime;    //��¼��һ������һ���ļ��ʱ�䣬Ҳ�����ٶ�

#if DEBUG_MODE
        outputSpeed[g_pvtInfo.targetStep - indexOffset] = g_pvtInfo.lastStepSpeed;
#endif

        minTime = curTime;
        lastTime = curTime;
        maxTime = curTime + g_pvtInfo.lastStepSpeed * 2;
        
        //ʱ��Ĳ�������:�����Ͻ���ʱ����Ϊ�ٶ���û�����ģ��������Դ�ڹ�һ�������������
        calcOutput = g_pvtInfo.lastStepSpeed * g_pvtInfo.fpgaPwmClock;

        //���������ޱ���
        if (calcOutput > g_pvtInfo.fpgaPwmClock)
        {
            calcOutput = g_pvtInfo.fpgaPwmClock;
            
            //ϵͳ��������λ NICK MARK
        }
        else if (calcOutput < 1)
        {
            calcOutput = 1;
            
            //ϵͳ��������λ NICK MARK
        }
        
        realOutput = (u32)(calcOutput + 0.5f);    //ʵ�����ֵ�Ǽ�������ֵ������������֮���ֵ
        g_pvtInfo.errorTime += calcOutput - realOutput;
        if (g_pvtInfo.errorTime > 1)    //���ģ���Ҫ�ڵ�ǰ����һ
        {
            realOutput++;
            g_pvtInfo.errorTime--;
        }
        else if (g_pvtInfo.errorTime < -1)    //���ģ���Ҫ�ڵ�ǰ����һ
        {
            realOutput--;
            g_pvtInfo.errorTime++;
        }

        //��realOutput���а�װ�£���Чλ��Ϊ24bits����25bitΪ���� NICK MARK

#if DEBUG_MODE
        totalOutput += realOutput;
#endif
    }
    g_pvtInfo.lastStepTime = curTime + startTime; 
}


/*********************************************************************************************
��������    PvtResultCalc��
ʵ�ֹ��ܣ�  ����ĳ��ʱ�̵ĵ����Ҫ������ٶȣ�
���������  �ޣ�
���������  �ޣ�   
��������ֵ���ޣ�  
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
    

    //��ȡPVT�б��ͷ��β
    headIndex = g_pvtInfo.headPoint;

    if (headIndex != g_pvtInfo.tailPoint)    //ͷ������β˵��������Ч����
    {
#if DEBUG_MODE
        //���㿪ʼ FOR DEBUG
        GPIOB->BSRR = GPIO_Pin_5;

        if (headIndex != 0)
        {
            indexOffset = g_pvtInfo.targetStep + 1;
        }

        calcTime = g_systemMilliSecTick;
#endif         
        
        //һ�ξͼ���һ�Σ�Ȼ���ȥ�����±������
        tailIndex = headIndex + 1;
        if (tailIndex >= PVT_POINT_BUFFER_SIZE)
        {
            tailIndex = 0;
        }

        if (1 == g_pvtInfo.targetStep)
        {
            //��¼��PVT��ʼ���λ��
            g_pvtInfo.startPosition = g_pvtInfo.pvtPoint[headIndex].position;
        }

        //��ȡ��ǰҪ�������һ��PVT���������
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
        
        if (direction != g_pvtInfo.lastStepDir)    //�����˶�
        {
            //����֮��Ŀ�경����Ϊ1�����·���
            g_pvtInfo.targetStep = 1;
            g_pvtInfo.lastStepDir = direction;
        }

        //���У׼�ˣ�Ҳ�ͱ�Ȼ�б�����
        if (bCalibrate)
        {
            //����ʼPVT���зֶ�(����ģʽ����Ҫ���зֶ�)
            if (WORK_POSITION != workMode)
            {
                motionPosn = poseOffset * g_motorInfo.encoderInfo.linePerRadian + g_pvtInfo.remainLine;
                motionCount = (u32)motionPosn;
                if (motionCount != motionPosn)
                {
                    bHaveRemain = true;
                    g_pvtInfo.remainLine = motionPosn - motionCount;
                }

                //����ת����
                radianToStep = g_motorInfo.encoderInfo.linePerRadian;
                startPosn  *= radianToStep;
                startSpeed *= radianToStep;
                endPosn    *= radianToStep;
                endSpeed   *= radianToStep;
                poseOffset *= radianToStep;

                lineStartPosn  = startPosn;
                lineStartSpeed = startSpeed;

                //��ʼ��ʱ��
                minTime = 0;
                lastTime = g_pvtInfo.lastLineTime - startTime;
                if (1 == g_pvtInfo.targetLine)    //��һ����ʱ����Ҫ��ȫʱ�䷶Χ�ڲ���
                {
                    curTime = motionTime / motionPosn;
                    maxTime = motionTime;
                }
                else
                {
                    curTime = lastTime;
                    maxTime = curTime + g_pvtInfo.lastLineSpeed * 2;
                }

                //��ǰ���������Ͷ������ϵ��
                cubeMotionTime = CUBE(motionTime);
                squareMotionTime = SQUARE(motionTime);
                threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
                twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

                for (i = 0;i < motionCount;i++)
                {
                    curTime += g_pvtInfo.lastLineSpeed;    //����һ�ߵ�ʱ�����ϼ�����һ�ߵ��ٶ���Ϊ��һ�ߵļ����ʼʱ��
                
                    cubeCurTime = CUBE(curTime);
                    squareCurTime = SQUARE(curTime);
                    curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPosn;
                    while (fabs(curPost - g_pvtInfo.targetLine) > TARGET_REAL_OFFSET)    //��Ŀ��ֵ�����̫���������
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
                    //��ȡ���ٶ�
                    lineEndSpeed = 3 * threeTermCoef * squareCurTime + 2 * twoTermCoef * curTime + startSpeed;
                    
                    g_pvtInfo.targetLine++;    //��ʼ������һ��Ŀ��
                    
                    g_pvtInfo.lastLineSpeed = curTime - lastTime;    //��¼��һ�ߺ���һ�ߵļ��ʱ�䣬Ҳ�����ٶ�
                    lastTime = curTime;
                    minTime  = curTime;
                    maxTime  = curTime + g_pvtInfo.lastLineSpeed * 2;

                    //���㵱ǰ��
                    radianToStep = 128;    //128 for debug NICK MARK
                    PvtPointCalc(lineStartPosn, lineStartSpeed, curPost, lineEndSpeed, lineStartTime,
                                 curTime + startTime, radianToStep, direction);
                    lineStartPosn  = curPost;
                    lineStartSpeed = lineEndSpeed;
                    lineStartTime = curTime + startTime;
                }
                g_pvtInfo.lastLineTime = curTime + startTime;
                
                //�������һ��
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
        else    //û��У׼�Ļ�����Ҫ���ձ�����ÿ��֮��Ļ��Ƚ���ʼPVT���зֶ�
        {
            //û�б����������б�������PVTģʽΪ��ͨ������
            if ((ENCODER_NONE == g_motorInfo.encoderInfo.type) || (WORK_POSITION != workMode))
            {
                //�����ܲ�������ת��ϵ��
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
            //����һ��PVT
            PvtPointCalc(startPosn, startSpeed, endPosn, endSpeed, startTime,
                         endTime, radianToStep, direction);
        }        
    
        g_pvtInfo.headPoint++;
        if (g_pvtInfo.headPoint >= PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.headPoint = 0;
        }

        //���Ĳ���һ����ʱ����Ҫ���� NICK MARK
        
        if (g_pvtInfo.headPoint == g_pvtInfo.tailPoint)    //ͷβ�����˵��List��û����Ч������
        {
            g_pvtInfo.targetStep    = 1;
            g_pvtInfo.lastStepSpeed = 0;
            g_pvtInfo.lastStepTime  = 0;
            g_pvtInfo.errorTime     = 0;
            g_pvtInfo.lastStepDir   = DIR_FORWARD;
        }

#if DEBUG_MODE
        calcTime = g_systemMilliSecTick - calcTime;
        
        //������� FOR DEBUG
        GPIOB->BRR = GPIO_Pin_5;
#endif
    }
}



/*******************************************�ļ�β********************************************/
