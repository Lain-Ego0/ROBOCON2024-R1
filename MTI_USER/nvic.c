#include "main.h"


void BSP_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//中断优先级分组
	
	//CAN1 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;		//CAN1接收中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;		//CAN1发送中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//CAN2 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
  //USART1 NVIC
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                          
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;   //pre-emption priority 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
  NVIC_Init(&NVIC_InitStructure);	
	
	//UART8 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =	1;
	NVIC_InitStructure.NVIC_IRQChannelCmd =	ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//Usart6 NVIC
  NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
	
	//Usart7 NVIC
  NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=5;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
	
		//USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
//	
//	//TIM2 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//串口2中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
//				

//	
	
}
