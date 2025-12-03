#ifndef __ChassisCtrl_H__
#define __ChassisCtrl_H__

#include "main.h"
extern float position_angle;//当前角度
typedef struct Speed_con
{	float vx;//左右平移速度
	float vy;//前后平移速度
	float vw;//旋转速度
}Speed_con;//底盘速度结构体

typedef enum
{
	Chassis_BlackOut,//底盘断电
	Chassis_Working,//运动状态
	Chassis_fire,//
	Chassis_firedown,//
}e_Chassis_State;//底盘状态

typedef enum
{
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
extern Speed_con TOur;
extern Speed_con TOur_phone;
extern Speed_con TOur_remoto;
extern Speed_con TOur_key;
extern Speed_con DJ_remoto;/***/

//死区设置 小于一定范围的值置零

void Chassis_Control(float vx,float vy,float vw);
void Chassis_twistt(Chassis_TypeDef* st_data,float kp,float ki);

#endif

