#ifndef _POINTRABBIT_H
#define _POINTRABBIT_H
#include "main.h"
//角度制转换为弧度制系数
#define CHANGE_TO_RADIAN    0.017453f   
//弧度制转换为角度制系数
#define CHANGE_TO_ANGLE     57.2958f
//一号电机
#define MOTOR_ONE            1u
//二号电机
#define MOTOR_TWO            2u

//点的结构体 单位mm
typedef struct ActPoint
{
	float x;
	float y;
}ActPoint;


//点斜式结构体 ，斜率用角度制的角度代替
typedef struct ActLine2
{
	ActPoint point;
	//角度制
	float    angle;
}ActLine2;

extern void Update_PositionX(float New_X);
extern void Update_PositionY(float New_Y);
extern void Update_PositionA(float New_A);
void Updata_Rabbit_ZERO(void);
void RabbitATatget_zero(void);

float MvByLine(ActLine2 presentLine, ActLine2 targetLine, float speed);
//外部接口函数，电机速度控制
extern void VelCrl(unsigned char ElmoNum,int vel);

#endif
