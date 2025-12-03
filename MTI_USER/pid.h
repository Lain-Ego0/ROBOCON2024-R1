#ifndef __PID_H__
#define __PID_H__

#include "stm32f4xx.h"

//PID属性列表
typedef struct PID_TypeDef
{
    float Kp;	//比例系数
    float Ki;	//积分系数
    float Kd;	//微分系数
    float Target;	//当前误差
    float IntPartMax;	//最大积分限制
    float OutputMax;	//PID输出
    float CurrentValue;	//当前值
    float CurrentError;	//当前误差
    float LastError;	//上一次误差
    float ProPart;	//比例项
	float DiffPart;	//微分项
	float IntPart;	//积分项
    float Output;	//PID输出
}PID_InitTypeDef;

void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd);
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax);
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax);
float fnPID_Calc(PID_InitTypeDef *pid);
void fnPID_SetTarget(PID_InitTypeDef *pid,float target);
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback);
float fnPID_GetOutput(PID_InitTypeDef *pid);

#endif
