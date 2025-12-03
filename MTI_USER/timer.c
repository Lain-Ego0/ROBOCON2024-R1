#include "timer.h"
#include "stm32f4xx_rcc.h"

/*
Tout = ((arr+1)*(psc+1))/Tclk ;
Tout = ((4999+1)*(7199+1))/72 = 500000us = 500ms   
*/

void BSP_TIM_Init()
	{
		TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
		TIM_OCInitTypeDef           TIM_OCInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8, ENABLE);
		

		TIM_TimeBaseStructure.TIM_Period = 20000; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
		TIM_TimeBaseStructure.TIM_Prescaler =72-1; //设置用来作为TIMx时钟频率除数的预分频值  不分频
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式	
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
		
			//初始化TIM2 Channel2 PWM模式	 
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
		TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能 
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断
		TIM_Cmd(TIM2, ENABLE);  //使能TIM2
//		
	}




