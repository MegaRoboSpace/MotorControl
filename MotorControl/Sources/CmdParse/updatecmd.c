/*********************************************************************************************
Copyright (C) 2016，北京镁伽机器人科技有限公司
文 件 名:  updatecmd.c；
功能描述:  ;
函数列表:  ;
当前版本:  1.0.0;
版本改动:  ;
作    者:  CJ;
完成日期:  2016.12.15;
历史版本:  无;
*********************************************************************************************/
#include "updatecmd.h"
#include "protocolstack.h"



/****************************************外部变量声明*****************************************/



/*****************************************局部宏定义******************************************/



/*************************************局部常量和类型定义**************************************/



/******************************************局部变量*******************************************/
SubCmdProFunc pUpdateCmdFunc[UPDATECMD_RESERVE];



/******************************************函数实现*******************************************/
/*********************************************************************************************
函 数 名: UpdateStart;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateStart(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: UpdateReady;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateReady(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: UpdateType;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateType(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: UpdateData;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateData(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: UpdateEnd;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateEnd(u8 cmdDataLen, u8 *pCmdData)
{    

}


/*********************************************************************************************
函 数 名: UpdateCmdInit;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateCmdInit(void)
{
    pUpdateCmdFunc[UPDATECMD_START] = UpdateStart;
    pUpdateCmdFunc[UPDATECMD_READY] = UpdateReady;
    pUpdateCmdFunc[UPDATECMD_TYPE]  = UpdateType;
    pUpdateCmdFunc[UPDATECMD_DATA]  = UpdateData;
    pUpdateCmdFunc[UPDATECMD_END]   = UpdateEnd;
}

            
/*********************************************************************************************
函 数 名: UpdateCmdProc;
实现功能: 无; 
输入参数: 无;
输出参数: 无;
返 回 值: 无;
说    明: 无;
*********************************************************************************************/
void UpdateCmdProc(CmdParseFrameStr *pCmdStackFrame)
{    
    u8 dataLen = pCmdStackFrame->dataLen;
    u8 *pData = pCmdStackFrame->payload;

    
    if ((pCmdStackFrame->subType < UPDATECMD_RESERVE) && (pUpdateCmdFunc[pCmdStackFrame->subType] != NULL))
    {    
        pUpdateCmdFunc[pCmdStackFrame->subType](dataLen, pData);
    }
}



/*******************************************文件尾********************************************/