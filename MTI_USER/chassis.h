#ifndef _Chassis_H__
#define _Chassis_H__

#include "main.h"

typedef enum
{
	Chassis_BlackOut,//底盘断电
	Chassis_Working//运动状态
}e_Chassis_State;//底盘状态

typedef enum
{
	Chassis_Follow,//跟随断电
	Chassis_Twist//扭腰状态
}e_ChassisMotion_State;//底盘运动状态

typedef struct Chassis_Speed_TypeDef
{
	float vx;//左右平移速度
	float vy;//前后平移速度
	float vw;//旋转速度
}Chassis_Speed_TypeDef;//底盘速度结构体

typedef struct Chassis_TypeDef
{
	//底盘状态
	e_Chassis_State State;
	e_ChassisMotion_State Mode;
	//底盘速度参数
	Chassis_Speed_TypeDef Para;	
	PID_InitTypeDef Twist_PID;
}Chassis_TypeDef;//底盘结构体

extern Chassis_TypeDef P_stChassis;//底盘参数结构体

void velctrl_task(void *p_arg);
void Chassis_Control(float vx,float vy,float vw);
void configChassis_ParaInit(void);

#endif
