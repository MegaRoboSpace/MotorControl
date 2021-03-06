/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  debugcmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include <string.h>
#include "debugcmd.h"
#include "cmdparse.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pDebugCmdFunc[DEBUGCMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: DebugSet;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DebugSet(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: DebugCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DebugCmdInit(void)
{
    memset(pDebugCmdFunc, 0, sizeof(pDebugCmdFunc));

    pDebugCmdFunc[DEBUGCMD_SET] = DebugSet;
}

            
/*********************************************************************************************
函 数 名: DebugCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void DebugCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < DEBUGCMD_RESERVE) && (pDebugCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pDebugCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************文件尾********************************************/