#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include "stm32f4xx.h"
#include <stdio.h>
#include <math.h>



typedef struct Signal_TypeDef
{
	float (*Calc) (struct Signal_TypeDef *Signal);//计算公式函数指针
	uint8_t (*isOverFlow) (struct Signal_TypeDef *Signal);//计算公式函数指针
	void (*Reset) (struct Signal_TypeDef *Signal);//计算公式函数指针
	float input;//自增变量
	uint32_t scale;//斜率
	float output;//输出值
}Signal_TypeDef;//信号结构体


extern Signal_TypeDef P_stvx_Ramp ;
extern Signal_TypeDef P_stvy_Ramp ;
extern Signal_TypeDef P_stvw_Ramp ;

void configSignal_ParaInit(void);
void cofigSignal_vxInit(void);
void cofigSignal_vyInit(void);
void fnSiganl_Reset(Signal_TypeDef* st_data);
float fnSignal_Ramp_Generate(Signal_TypeDef* st_data);
void fnSignal_SetScale(Signal_TypeDef* st_data,uint32_t scale);
float fnSignal_BackRamp_Generate(Signal_TypeDef* st_data);
uint8_t fnSiganl_IsOverFlow(Signal_TypeDef* st_data);

#endif
