#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdio.h>
#include "stdbool.h"
#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include "pid.h"

#define ROTATE_SPEEDBUF_LEN  6 //速度滤波数组缓存长度

#define MOTOR_3508_REDUCTIONRATE 19.f //3508电机减速比为19：1

#define MOTOR_CANSEND_IDENTIFIER1_4 0x200 // 电调ID 1~4使用此标识符
#define MOTOR_CANSEND_IDENTIFIER5_8 0x1ff // 电调ID 5~8使用此标识符

//用户ID定义
#define MOTOR_CHASSIS_LF_CAN_ID 0x201 //底盘左前电机CAN口ID
#define MOTOR_CHASSIS_RF_CAN_ID 0x202 //底盘右前电机CAN口ID
#define MOTOR_CHASSIS_LB_CAN_ID 0x203 //底盘左后电机CAN口ID
#define MOTOR_CHASSIS_RB_CAN_ID 0x204 //底盘右后电机CAN口ID

#define MOTOR_PINCH_TURN_CAN_ID 0x205 //翻转电机CAN口ID
#define MOTOR_PINCH_CAN_ID 			0x206 //夹取电机CAN口ID
//#define MOTOR_LIFT_CAN_ID 			0x207 //抬升电机CAN口ID

typedef struct 
{
  uint8_t     CANx;               //CAN编号     1 CAN1      2 CAN2
	CanTxMsg    SendCanTxMsg;       //发送数据
}CanSend_Type;

//3508电机原始数据处理结构体
typedef struct Motor_Data_TypeDef
{
	//原始数据
	int16_t Encoder_Val;//编码器值
	int16_t Rotate_Speed;//转子速度
	int16_t Armature_Current;//电枢电流
	int8_t Motor_Temperature; //电机温度
	
	int16_t Last_Encoder_Val;//上一次编码器值
	int32_t Number_Of_Turns;//电机旋转圈数
	float Rotate_Angle;//电机转度 0-360度
	float Shaft_Angle;//电机转过的角度
	
	//速度滤波
	int16_t Rotate_FliterSpeed;//滤波后的速度
	int16_t Rotate_SpeedBuf[ROTATE_SPEEDBUF_LEN];
	int16_t Rotate_BufCount;//数组数据计数
	
}Motor_DataRecv_TypeDef;

//3508电机数据结构体
typedef struct Motor_TypeDef
{
	int8_t CAN_ID;//CAN ID号
	uint8_t Reduction_Rate;//电机减速比
	Motor_DataRecv_TypeDef RecvData;//电机数据储存
	PID_InitTypeDef SpeedPID;//速度环PID控制数据
	PID_InitTypeDef AnglePID;//角度环PID控制数据
	
}Motor_TypeDef;

extern Motor_TypeDef Motor_ChassisLF;//底盘左前电机
extern Motor_TypeDef Motor_ChassisRB;//底盘右前电机
extern Motor_TypeDef Motor_ChassisRF;//底盘右后电机
extern Motor_TypeDef Motor_ChassisLB;//底盘左后电机
extern Motor_TypeDef Motor_PinchTurn;//翻转电机
extern Motor_TypeDef Motor_Pinch;		//夹取电机


void configMotor_ParaInit(void);

void Motor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg);
void Motor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i);

void Motor_SpeedCotrol( Motor_TypeDef* st_data,float target_speed);
void Motor_ArmSpeedCotrol( Motor_TypeDef* st_data,float target_speed);
void Motor_AngleCotrol( Motor_TypeDef* st_data,float target_angle);

static void Motor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData);
static void Motor_RawDataDecode(Motor_TypeDef* st_data,CanRxMsg * msg);
//static void Motor_HandleData(Motor_TypeDef* st_data);

#endif
