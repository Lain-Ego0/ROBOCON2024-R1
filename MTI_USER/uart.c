#include "main.h"
#include "task.h"
////加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 通过串口2发送
int fputc(int ch, FILE *f)
{ 	
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	return ch;
}


void BSP_USART_Init(void)
{
   //USART 初始化设置
	USART_InitTypeDef USART_InitStructure;	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8|RCC_APB1Periph_UART7|RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_USART6,ENABLE);

	//DBUS USART1
	USART_DeInit(USART1);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 100000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
	USART_Cmd(USART1,ENABLE);
	
	//H219 UART8
	USART_DeInit(UART8);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 115200;         
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART8,&USART_InitStructure);
	USART_DMACmd(UART8, USART_DMAReq_Rx, ENABLE);
	USART_ITConfig(UART8,USART_IT_IDLE,ENABLE);
	USART_Cmd(UART8,ENABLE);
	

	
	//激光雷达 USART6
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART6, &USART_InitStructure); 
	USART_Cmd(USART6, ENABLE);   	
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ClearFlag(USART6, USART_FLAG_TC);	
	
		//定位系统
	USART_DeInit(UART7);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART7, &USART_InitStructure); 
	USART_Cmd(UART7, ENABLE);   	
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ClearFlag(UART7, USART_FLAG_TC);	
	
	 		//自制遥控 USART2
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); 
	USART_Cmd(USART2, ENABLE);   	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_ClearFlag(USART2, USART_FLAG_TC);	

}

#endif

