#include "main.h"

/*************************************************************************
*  函数名称：BSP_GPIO_Init
*  功能说明：GPIO初始化
*  参数说明：无 
*  函数返回：无	 
*  备    注：
*************************************************************************/
//////////////////////////////////////

////////////请注释清楚，每个都要！！！！

//////////////////////////////////////
void BSP_GPIO_Init(void)
{   
	
	  //时钟使能
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
			//PWM
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//CAN1 RX-PD0 与 TX-PD1
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		//CAN2 PB12 PB13
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2); 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//串口6 TX:PG14  RX:PG9
		GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_USART6);
		GPIO_PinAFConfig(GPIOG,GPIO_PinSource9, GPIO_AF_USART6);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_Init(GPIOG,&GPIO_InitStructure); 
		
		//DBUS USART1 RX:PB7 
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//串口7 TX:PE8  RX:PE7
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_UART7);
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_UART7);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_Init(GPIOE,&GPIO_InitStructure);


		//陀螺仪hi219m UART8 TX:PE1  RX:PE0
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_UART8);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_UART8);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
		
		//继电器  PE5 PE6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		
			//USART2
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
		GPIO_Init(GPIOD,&GPIO_InitStructure);
}

