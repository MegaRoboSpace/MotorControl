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
#include "pvtparaverify.h"



/****************************************�ⲿ��������*****************************************/
extern volatile u64  g_systemMilliSecTick;
extern PvtInfoStruct g_pvtInfo;



/*****************************************�ֲ��궨��******************************************/
#define    SQUARE(num)               (num * num)
#define    CUBE(num)                 (num * num * num)
#define    TARGET_REAL_OFFSET        0.1           //����PVTÿ���ٶ��ǣ�ʵ�ʲ�����Ŀ�경��֮��������



/*************************************�ֲ����������Ͷ���**************************************/
typedef struct
{
    f32             setpIndex;     //�������
    DirectionStruct direction;
    
}SetpInfoStr;



/******************************************�ֲ�����*******************************************/
SetpInfoStr setpInfo;

#if DEBUG_MODE
u32 totalOutput = 0;
#endif



/******************************************����ʵ��*******************************************/
/*********************************************************************************************
��������    PvtPointCalc��
ʵ�ֹ��ܣ�  ����ĳ��ʱ�̵ĵ����Ҫ�����λ�ã�
���������  �ޣ�
���������  �ޣ�   
��������ֵ���ޣ�  
*********************************************************************************************/
SetpInfoStr PvtPointCalc(f32 startPost, f32 startSpeed, f32 threeTermCoef, f32 twoTermCoef, f32 curTime)
{    
    f32 curPost;    
    f32 cubeCurTime = CUBE(curTime);
    f32 squareCurTime = SQUARE(curTime);
    SetpInfoStr setpInfo;


    //p(t) = (2(p0 - p1)/T-3 + (v0 + v1)/T-2)*t-3 + (3(p1 - p0)/T-2 - (2v0 + v1)/T) * t-2 + v0t + p0
    //T-3����T�����η���������ͬ��ͬһ����ÿ����ʽ��ϵ����һ���ģ������ڵ��ú���ǰ�Ѿ���������
    curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;


    //�����λ������Ǹ���˵���Ƿ����˶�
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
��������    PvtResultCalc��
ʵ�ֹ��ܣ�  ����ĳ��ʱ�̵ĵ����Ҫ������ٶȣ�
���������  �ޣ�
���������  �ޣ�   
��������ֵ���ޣ�  
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
    

    //��ȡPVT�б��ͷ��β
    headIndex = g_pvtInfo.headPoint;

    if (headIndex != g_pvtInfo.tailPoint)    //ͷ������β˵��������Ч����
    {
#if DEBUG_MODE
        //���㿪ʼ FOR DEBUG
        GPIOB->BSRR = GPIO_Pin_5;
        g_pvtInfo.targetStep = 1;
#endif
        
        //�ٶ�Ϊ0ʱ����ʼ�ٶȰ�0�㣬�������ϴμ�������һ�����ٶ���
        if (0 == g_pvtInfo.pvtPoint[headIndex].speed)
        {
            startSpeed = 0;
        }
        else
        {
            startSpeed = 1 / g_pvtInfo.lastStepSpeed;    //�洢����ʱ�䣬������Ҫ����
        }
        startPost = g_pvtInfo.targetStep - 1;    //��ʼʱtargetStepΪ1��λ�þ�Ϊ0
        
        
        //һ�ξͼ���һ�Σ�Ȼ���ȥ�����±������
        tailIndex = headIndex + 1;
        if (tailIndex >= PVT_POINT_BUFFER_SIZE)
        {
            tailIndex = 0;
        }

        //���ݹ���ģʽ����ʼ��PVT�ֶ� NICK MARK
        if (WORK_TORQUE != workMode)
        {
            //�Ƚ���ǰPVT��Ӧ��λ�ð��ձ������������зֶ�

            //
            if ((WORK_NORMAL == workMode) || (WORK_UNIFORM == workMode))
            {
                //
                //if (/*��У׼����*/)
                {
                    //����ÿ�ε�RADIAN_TO_STEP
                }
                //else
                {
                    //RADIAN_TO_STEP = һȦ�Ĳ��� / 2��
                }
            }
            else
            {
                //RADIAN_TO_STEP = 1
            }
            
        }

        /**********************************һ��PVT���㿪ʼ***********************************************/        
        //��ֹλ�á��ٶ�
        endPost  = g_pvtInfo.pvtPoint[tailIndex].position * g_pvtInfo.radianToStep - startPost;
        endSpeed = g_pvtInfo.pvtPoint[tailIndex].speed * g_pvtInfo.radianToStep;
        
        motionTime = g_pvtInfo.pvtPoint[tailIndex].time - g_pvtInfo.lastStepTime;    //�ϴμ���Ľ���ʱ��

        poseOffset = endPost - startPost;     //��������һ��PVT�еĲ�����Ҳ����Ҫ�������Ĳ���
        if (poseOffset < 0)
        {
            direction = REVERSE;
        }
        else
        {
            direction = FORWARD;
        }
        
        if (direction != g_pvtInfo.lastStepDir)    //�����˶�
        {
            //����֮��Ŀ�경����Ϊ1�����·���
            g_pvtInfo.targetStep = 1;
            g_pvtInfo.lastStepDir = direction;
        }
        
        
        //��ʼ��ʱ��
        lastTime = 0;
        minTime = 0;
        if (1 == g_pvtInfo.targetStep)    //��һ����ʱ����Ҫ��ȫʱ�䷶Χ�ڲ���
        {
            curTime = motionTime / poseOffset;
            maxTime = motionTime;
        }
        else
        {
            curTime = g_pvtInfo.lastStepSpeed;
            maxTime = curTime + g_pvtInfo.lastStepSpeed;
        }

        //��ǰ���������Ͷ������ϵ��
        cubeMotionTime = CUBE(motionTime);
        squareMotionTime = SQUARE(motionTime);
        threeTermCoef = ((startSpeed + endSpeed) / squareMotionTime) - (poseOffset * 2 / cubeMotionTime);
        twoTermCoef = (poseOffset * 3 / squareMotionTime) - (startSpeed * 2 + endSpeed) / motionTime;

        for (i = 0;i < (u32)poseOffset;i++)
        {
            cubeCurTime = CUBE(curTime);
            squareCurTime = SQUARE(curTime);
            
            curTime += g_pvtInfo.lastStepSpeed;    //����һ����ʱ�����ϼ�����һ�����ٶ���Ϊ��һ���ļ����ʼʱ��
        
            //setpInfo = PvtPointCalc(startPost, startSpeed, threeTermCoef, twoTermCoef, curTime);
            curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;
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
                curPost = threeTermCoef * cubeCurTime  + twoTermCoef * squareCurTime + startSpeed * curTime + startPost;
            }    
            g_pvtInfo.targetStep++;    //��ʼ������һ��Ŀ��
            
            g_pvtInfo.lastStepSpeed = curTime - lastTime;    //��¼��һ������һ���ļ��ʱ�䣬Ҳ�����ٶ�
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
        g_pvtInfo.lastStepTime = curTime;
        
        g_pvtInfo.headPoint++;
        if (g_pvtInfo.headPoint >= PVT_POINT_BUFFER_SIZE)
        {
            g_pvtInfo.headPoint = 0;
        }
        /**********************************һ��PVT�������***********************************************/ 

        //���PVT List�л���δ����ĵ㣬�򱣴汾�μ�������������ٶ�
        //��Ϊ�´μ������ʼ����������
        if (g_pvtInfo.headPoint == g_pvtInfo.tailPoint)    //ͷβ�����˵��List��û����Ч������
        {
            g_pvtInfo.targetStep    = 1;
            g_pvtInfo.lastStepSpeed = 0;
            g_pvtInfo.lastStepTime  = 0;
            g_pvtInfo.errorTime     = 0;
            g_pvtInfo.lastStepDir   = FORWARD;
        }

#if DEBUG_MODE
        //������� FOR DEBUG
        GPIOB->BRR = GPIO_Pin_5;
#endif
    }
}


/*********************************************************************************************
��������    PvtDebugMode��
ʵ�ֹ��ܣ�  ����ĳ��ʱ�̵ĵ����Ҫ������ٶȣ�
���������  �ޣ�
���������  �ޣ�   
��������ֵ���ޣ�  
*********************************************************************************************/
void PvtDebugMode(void)
{
    
}



/*******************************************�ļ�β********************************************/
