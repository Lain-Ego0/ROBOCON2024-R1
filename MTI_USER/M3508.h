#ifndef __M3508_H__
#define __M3508_H__

#include <stdio.h>
#include "stdbool.h"
#include "stm32f4xx.h"
#include "pid.h"

#define MOTOR_3508_REDUCTIONRATE 19.f //3508电机减速比为19：1
#define MOTOR_CANSEND_IDENTIFIER1_4 0x200 // 电调ID 1~4使用此标识符
#define MOTOR_CANSEND_IDENTIFIER5_8 0x1ff // 电调ID 5~8使用此标识符

//用户ID定义
#define CAN1_MOTO1_ID 0x201 //CAN1_MOTO1_ID机配置ID口
#define CAN1_MOTO2_ID 0x202 //CAN1_MOTO2_ID机配置ID口
#define CAN1_MOTO3_ID 0x203 //CAN1_MOTO3_ID机配置ID口
#define CAN1_MOTO4_ID 0x204 //CAN1_MOTO4_ID机配置ID口
#define CAN1_MOTO5_ID 0x205 //CAN1_MOTO4_ID机配置ID口
#define CAN1_MOTO6_ID 0x206 //CAN1_MOTO4_ID机配置ID口


#define CAN2_MOTO1_ID 0x201 //CAN2_MOTO1_ID机配置ID口
#define CAN2_MOTO2_ID 0x202 //CAN2_MOTO2_ID机配置ID口（M2006）
#define CAN2_MOTO3_ID 0x203 //CAN2_MOTO3_ID机配置ID口
#define CAN2_MOTO4_ID 0x204 //CAN2_MOTO4_ID机配置ID口
#define CAN2_MOTO5_ID 0x205 //CAN2_MOTO5_ID机配置ID口
#define CAN2_MOTO6_ID 0x206 //CAN2_MOTO6_ID机配置ID口
#define CAN2_MOTO7_ID 0x207 //CAN2_MOTO7_ID机配置ID口

#define ROTATE_SPEEDBUF_LEN  6 //速度滤波数组缓存长度



typedef struct 
{
  uint8_t     CANx;               //CAN编号     1 CAN1      2 CAN2
  CanTxMsg    SendCanTxMsg;       //发送数据
}CanSend_Type;

//3508电机原始数据处理结构体
typedef struct M3508_Data_TypeDef
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

}M3508_DataRecv_TypeDef;

//3508电机数据结构体
typedef struct M3508_TypeDef
{
	int8_t CAN_ID;//CAN ID号
	uint8_t Reduction_Rate;//电机减速比
	M3508_DataRecv_TypeDef RecvData;//电机数据储存
	PID_InitTypeDef SpeedPID;//速度环PID控制数据
	PID_InitTypeDef AnglePID;//角度环PID控制数据
}M3508_TypeDef;



extern M3508_TypeDef Can1_Moto1;//电机配置ID口
extern M3508_TypeDef Can1_Moto2;//电机配置ID口
extern M3508_TypeDef Can1_Moto3;//电机配置ID口
extern M3508_TypeDef Can1_Moto4;//电机配置ID口
extern M3508_TypeDef Can1_Moto5;//电机配置ID口
extern M3508_TypeDef Can1_Moto6;//电机配置ID口

extern M3508_TypeDef Can2_Moto1;//电机配置ID口
extern M3508_TypeDef Can2_Moto2;//电机配置ID口（M2006）
extern M3508_TypeDef Can2_Moto3;//电机配置ID口
extern M3508_TypeDef Can2_Moto4;//电机配置ID口
extern M3508_TypeDef Can2_Moto5;//电机配置ID口
extern M3508_TypeDef Can2_Moto6;//电机配置ID口
extern M3508_TypeDef Can2_Moto7;//电机配置ID口

void M3508_ParaInit(void);

void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg);
void Control_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i);
/////////////////////////速度环
void USE_CAN1_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed);
void USE_CAN2_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed);
/////////////////////////角度环前环
void USE_CAN1_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_speed);
void USE_CAN2_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_angle);
/////////////////////////角度环后环
void USE_CAN1_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_speed);
void USE_CAN2_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_angle);

static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData);
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg);

#endif
