#include "main.h"

/*************************************************************************
*  函数名称：BSP_CAN_Init
*  功能说明：CAN初始化
*  参数说明：无 
*  函数返回：无	 
*  备    注：无 过滤器 发送状态寄存器 错误状态寄存器
*************************************************************************/
void BSP_CAN_Init(void)
{
//CAN1初始化
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure; 
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
	CAN_DeInit(CAN1);	//初始化CAN1
	CAN_StructInit(&CAN_InitStructure);	//初始化CAN1结构体
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = ENABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	//波特率参数
	CAN_InitStructure.CAN_BS1 = CAN_BS1_10tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
	CAN_InitStructure.CAN_Prescaler = 3;   //CAN BaudRate 45/(1+10+4)/3=1Mbps
	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	//滤波ID设置为0
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);	//使能CAN接收中断
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 	//使能CAN发送中断
    
		//CAN2
	CAN_DeInit(CAN2);	//初始化CAN1
	CAN_StructInit(&CAN_InitStructure);	//初始化CAN1结构体
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	//波特率参数
	CAN_InitStructure.CAN_BS1 = CAN_BS1_10tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
	CAN_InitStructure.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
	CAN_Init(CAN2, &CAN_InitStructure);
	CAN_FilterInitStructure.CAN_FilterNumber=14;//14?
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	//滤波ID设置为0
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);	//使能CAN接收中断
	CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE); 	//使能CAN发送中断
  
}
