#include "pid.h"

#define PID_OUTPUT_LIMIT_ALLOW 1 //输出限幅开启
#define PID_INTPART_LIMIT_ALLOW 1//积分限幅开启
//宏定义，用于将值val限制在最大值max与最小值min之间
#define limit(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\

/*************************************************************************
*  函数名称：fnPID_SetPara_P_I_D
*  功能说明：设置Kp,Ki,Kd
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_P_I_D(PID_InitTypeDef *pid,float kp,float ki,float kd)
{
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
}

/*************************************************************************
*  函数名称：fnPID_SetPara_OM
*  功能说明：设置输出限幅
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_OM(PID_InitTypeDef *pid,float outputmax)
{
	pid->OutputMax = outputmax ;
}

/*************************************************************************
*  函数名称：fnPID_SetPara_IM
*  功能说明：设置积分限幅
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetPara_IM(PID_InitTypeDef *pid,float intpartmax)
{
	pid->IntPartMax = intpartmax;
}
/*************************************************************************
*  函数名称：fnPID_Calc
*  功能说明：进行PID计算
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
float fnPID_Calc(PID_InitTypeDef *pid)
{	
	//误差
	pid->CurrentError = pid->Target - pid->CurrentValue;
	//比例项
	pid->ProPart = pid->Kp * pid->CurrentError;
	//微分项
	pid->DiffPart = pid->Kd * (pid->CurrentError - pid->LastError);
	//积分项
	pid->IntPart += pid->Ki * pid->CurrentError;
	//积分限幅
	#if PID_INTPART_LIMIT_ALLOW
	limit(pid->IntPart,-pid->IntPartMax,pid->IntPartMax);
	#endif
	//计算输出
	pid->Output = pid->ProPart + pid->IntPart + pid->DiffPart;
	//输出限幅
	#if PID_OUTPUT_LIMIT_ALLOW
	limit(pid->Output,-pid->OutputMax,pid->OutputMax);
	#endif
	
	return pid->Output;
}

/*************************************************************************
*  函数名称：fnPID_SetTarget
*  功能说明：设置PID目标值
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetTarget(PID_InitTypeDef *pid,float target)
{
	pid->Target = target;
}

/*************************************************************************
*  函数名称：fnPID_SetFeedback
*  功能说明：获取PID反馈值
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
void fnPID_SetFeedback(PID_InitTypeDef *pid,float feedback)
{
	pid->CurrentValue = feedback;
}

/*************************************************************************
*  函数名称：fnPID_GetOutput
*  功能说明：获取PID输出
*  参数说明：无 
*  函数返回：无	 
*  备    注：无
*************************************************************************/
float fnPID_GetOutput(PID_InitTypeDef *pid)
{
	return pid->Output;
}
