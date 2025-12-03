#include "M3508.h"

//电机具体配置 初始化电机配置 Can数据解析加入电机位置 对应函数使用
//用户定义电机结构体
//前腿定义在can1,后退定义在can2

//can1 底盘
M3508_TypeDef Can1_Moto1 = {1};//Can1_Moto 左前
M3508_TypeDef Can1_Moto2 = {2};//Can1_Moto 左后
M3508_TypeDef Can1_Moto3 = {3};//Can1_Moto 右前
M3508_TypeDef Can1_Moto4 = {4};//Can1_Moto 右后
M3508_TypeDef Can1_Moto5 = {5};//Can1_Moto 同步轮
M3508_TypeDef Can1_Moto6 = {6};//Can1_Moto 同步轮
//can2
M3508_TypeDef Can2_Moto1 = {1};//Can2_Moto 下摩擦轮
M3508_TypeDef Can2_Moto2 = {2};//Can2_Moto 左摩擦轮
M3508_TypeDef Can2_Moto3 = {3};//Can2_Moto 右摩擦轮
M3508_TypeDef Can2_Moto4 = {4};//Can2_Moto 上摩擦轮
M3508_TypeDef Can2_Moto5 = {5};//Can2_Moto  
M3508_TypeDef Can2_Moto6 = {6};//Can2_Moto
M3508_TypeDef Can2_Moto7 = {7};//Can2_Moto

//电机参数初始化
void M3508_ParaInit(void)
{	
	//Can1
	//Can1_Moto1
	fnPID_SetPara_P_I_D(&Can1_Moto1.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto1.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto1.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto1.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto1.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto1.AnglePID,3000);
	//Can1_Moto2
	fnPID_SetPara_P_I_D(&Can1_Moto2.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto2.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto2.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto2.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto2.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto2.AnglePID,3000);
	//Can1_Moto3
	fnPID_SetPara_P_I_D(&Can1_Moto3.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto3.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto3.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto3.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto3.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto3.AnglePID,3000);
	//Can1_Moto4
	fnPID_SetPara_P_I_D(&Can1_Moto4.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto4.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto4.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto4.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto4.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto4.AnglePID,3000);
	//Can1_Moto5
	fnPID_SetPara_P_I_D(&Can1_Moto5.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto5.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto5.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto5.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto5.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto5.AnglePID,3000);
	//Can1_Moto6
	fnPID_SetPara_P_I_D(&Can1_Moto6.SpeedPID,11,0,0.6);
	fnPID_SetPara_IM(&Can1_Moto6.SpeedPID,1000);
	fnPID_SetPara_OM(&Can1_Moto6.SpeedPID,8000);
	fnPID_SetPara_P_I_D(&Can1_Moto6.AnglePID,8,0,0.4);
	fnPID_SetPara_IM(&Can1_Moto6.AnglePID,1000);
	fnPID_SetPara_OM(&Can1_Moto6.AnglePID,5000);
	
	//Can2
	//Can2_Moto1
	fnPID_SetPara_P_I_D(&Can2_Moto1.SpeedPID,15,0,0.4);//P原值15
	fnPID_SetPara_IM(&Can2_Moto1.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto1.SpeedPID,10000);
	fnPID_SetPara_P_I_D(&Can2_Moto1.AnglePID,12,0,0.6);//P原值12
	fnPID_SetPara_IM(&Can2_Moto1.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto1.AnglePID,9000);
	//Can2_Moto2
	fnPID_SetPara_P_I_D(&Can2_Moto2.SpeedPID,17,0,0.01);
	fnPID_SetPara_IM(&Can2_Moto2.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto2.SpeedPID,10000);
	fnPID_SetPara_P_I_D(&Can2_Moto2.AnglePID,8,0,0.01);
	fnPID_SetPara_IM(&Can2_Moto2.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto2.AnglePID,5000);
	//Can2_Moto3
	fnPID_SetPara_P_I_D(&Can2_Moto3.SpeedPID,15,0,0.4);
	fnPID_SetPara_IM(&Can2_Moto3.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto3.SpeedPID,7000);
	fnPID_SetPara_P_I_D(&Can2_Moto3.AnglePID,10,0,0.2);
	fnPID_SetPara_IM(&Can2_Moto3.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto3.AnglePID,7000);
	//Can2_Moto4（M2006电机）
	fnPID_SetPara_P_I_D(&Can2_Moto4.SpeedPID,10,0,0.4);
	fnPID_SetPara_IM(&Can2_Moto4.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto4.SpeedPID,4000);
	fnPID_SetPara_P_I_D(&Can2_Moto4.AnglePID,8,0,0.5);//P原值为8
	fnPID_SetPara_IM(&Can2_Moto4.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto4.AnglePID,2000);//原值2000
  //Can2_Moto5
	fnPID_SetPara_P_I_D(&Can2_Moto5.SpeedPID,13,0,0.4);
	fnPID_SetPara_IM(&Can2_Moto5.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto5.SpeedPID,10000);
	fnPID_SetPara_P_I_D(&Can2_Moto5.AnglePID,8,0,0.2);
	fnPID_SetPara_IM(&Can2_Moto5.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto5.AnglePID,7000);
	//Can2_Moto6
	fnPID_SetPara_P_I_D(&Can2_Moto6.SpeedPID,18,0,0.4);
	fnPID_SetPara_IM(&Can2_Moto6.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto6.SpeedPID,7000);
	fnPID_SetPara_P_I_D(&Can2_Moto6.AnglePID,8,0,0.2);
	fnPID_SetPara_IM(&Can2_Moto6.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto6.AnglePID,7000);
	//Can2_Moto7
	fnPID_SetPara_P_I_D(&Can2_Moto7.SpeedPID,18,0,0.4);
	fnPID_SetPara_IM(&Can2_Moto7.SpeedPID,1000);
	fnPID_SetPara_OM(&Can2_Moto7.SpeedPID,7000);
	fnPID_SetPara_P_I_D(&Can2_Moto7.AnglePID,8,0,0.2);
	fnPID_SetPara_IM(&Can2_Moto7.AnglePID,1000);
	fnPID_SetPara_OM(&Can2_Moto7.AnglePID,7000);

}

//Can数据解析
void fnMotor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
{
	if(canx == CAN1)
	{
			//根据对应ID,进行数据解析
			switch(msg->StdId)
			{
				case CAN1_MOTO1_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto1,msg);//原始数据解析
				}break;
				
				case CAN1_MOTO2_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto2,msg);//原始数据解析
				}break;
				
				case CAN1_MOTO3_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto3,msg);//原始数据解析
				}break;
				
				case CAN1_MOTO4_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto4,msg);//原始数据解析
				}break;
				case CAN1_MOTO5_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto5,msg);//原始数据解析
				}break;
				case CAN1_MOTO6_ID:
				{
					s_fnM3508_RawDataDecode(&Can1_Moto6,msg);//原始数据解析
				}break;
				default:
						{
						}break;
			  }
	}
		else if(canx == CAN2)
	{
		  //根据对应ID,进行数据解析
      switch(msg->StdId)
			{
				case CAN2_MOTO1_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto1,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO2_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto2,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO3_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto3,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO4_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto4,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO5_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto5,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO6_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto6,msg);//原始数据解析
				}break;
				
				case CAN2_MOTO7_ID:
				{
					s_fnM3508_RawDataDecode(&Can2_Moto7,msg);//原始数据解析
				}break;
				default:
						{
						}break;
			  }
	}
	
}

//电机控制函数 ************************************************************

//电机速度控制函数 ************
void USE_CAN1_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	Control_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}


void USE_CAN2_SpeedCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	Control_SetCurrentVal(CAN2,st_data->CAN_ID,ctrl_val);//控制执行电机
}

//电机角度控制函数 ************************************************************3508电机角度控制函数 双环PID控制
/////////////////////////角度环前环 ******
void USE_CAN1_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量 
	
	Control_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}

void USE_CAN2_ArmMotorCotrol_M3508( M3508_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	fnPID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	fnPID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	fnPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = fnPID_GetOutput(&st_data->SpeedPID);//获取控制量 
	
	Control_SetCurrentVal(CAN2,st_data->CAN_ID,ctrl_val);//控制执行电机
}

/////////////////////////角度后环 ******

void USE_CAN1_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_angle)
{
	float pid_output;
	
	fnPID_SetTarget(&st_data->AnglePID,target_angle);//设置角度环目标值
	fnPID_SetFeedback(&st_data->AnglePID,st_data->RecvData.Shaft_Angle);//获取角度反馈
	fnPID_Calc(&st_data->AnglePID);//计算PID输出
	
	pid_output = fnPID_GetOutput(&st_data->AnglePID);//获取角度环输出
	
	USE_CAN1_ArmMotorCotrol_M3508(st_data,pid_output);//将角度环输出作为速度环目标值
}
void USE_CAN2_AngleCotrol_M3508( M3508_TypeDef* st_data,float target_angle)
{
	float pid_output;
	
	fnPID_SetTarget(&st_data->AnglePID,target_angle);//设置角度环目标值
	fnPID_SetFeedback(&st_data->AnglePID,st_data->RecvData.Shaft_Angle);//获取角度反馈
	fnPID_Calc(&st_data->AnglePID);//计算PID输出
	
	pid_output = fnPID_GetOutput(&st_data->AnglePID);//获取角度环输出
	
	USE_CAN2_ArmMotorCotrol_M3508(st_data,pid_output);//将角度环输出作为速度环目标值
}

/////////////////////////////////////////以上为主要配置
//**************************************************************************************
/////////////////////////////////////////以下为主要配置

//电机电调设置控制电流值--直接控制电流,电流会直接提供力,会直接提供加速度
void Control_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)//输出电流值,并发送
//	Control_SetCurrentVal(CAN2,3,1000);
{ 
	static CanSend_Type MotorSendData1_4;
	static CanSend_Type MotorSendData5_8;
	static CanSend_Type MotorSendData1_4_CAN2;
	static CanSend_Type MotorSendData5_8_CAN2;
	
	//若ID为1-4之间则使用标识符0x200，id为5-8之间时使用标识符0x1ff
	
	if (CANx==CAN1)
	{
		MotorSendData1_4.CANx = 1;
		MotorSendData5_8.CANx = 1;
		MotorSendData1_4.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
		MotorSendData1_4.SendCanTxMsg.DLC = 8;
		MotorSendData1_4.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData1_4.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		MotorSendData5_8.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
		MotorSendData5_8.SendCanTxMsg.DLC = 8;
		MotorSendData5_8.SendCanTxMsg.IDE = CAN_ID_STD;
		MotorSendData5_8.SendCanTxMsg.RTR = CAN_RTR_Data;
		
		switch(motor_id)
		{
			case 1:
			{
				MotorSendData1_4.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 2:
			{
				MotorSendData1_4.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 3:
			{
				MotorSendData1_4.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 4:
			{
				MotorSendData1_4.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData1_4.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
			
			case 5:
			{
				MotorSendData5_8.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
			}break;
			
			case 6:
			{
				MotorSendData5_8.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
			}break;
			
			case 7:
			{
				MotorSendData5_8.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
			}break;
			
			case 8:
			{
				MotorSendData5_8.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
				MotorSendData5_8.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
			}break;
				
		}

		//数据发送
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData1_4.SendCanTxMsg));
		s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData5_8.SendCanTxMsg));	
		}
	
	//为can2
		
		else
		{
			MotorSendData1_4_CAN2.CANx = 2;
			MotorSendData5_8_CAN2.CANx = 2;
			MotorSendData1_4_CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
			MotorSendData1_4_CAN2.SendCanTxMsg.DLC = 8;
			MotorSendData1_4_CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
			MotorSendData1_4_CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
			
			MotorSendData5_8_CAN2.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
			MotorSendData5_8_CAN2.SendCanTxMsg.DLC = 8;
			MotorSendData5_8_CAN2.SendCanTxMsg.IDE = CAN_ID_STD;
			MotorSendData5_8_CAN2.SendCanTxMsg.RTR = CAN_RTR_Data;
			

			
			switch(motor_id)
			{
				case 1:
				{
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
				}break;
				
				case 2:
				{
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
				}break;
				
				case 3:
				{
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
				}break;
				
				case 4:
				{
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
					MotorSendData1_4_CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
				}break;
				
				case 5:
				{
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[0] = (uint8_t)(cm_i >> 8);
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[1] = (uint8_t)cm_i;
				}break;
				
				case 6:
				{
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[2] = (uint8_t)(cm_i >> 8);
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[3] = (uint8_t)cm_i;
				}break;
				
				case 7:
				{
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[4] = (uint8_t)(cm_i >> 8);
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[5] = (uint8_t)cm_i;
				}break;
				
				case 8:
				{
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[6] = (uint8_t)(cm_i >> 8);
					MotorSendData5_8_CAN2.SendCanTxMsg.Data[7] = (uint8_t)cm_i;
				}break;
					
			}

			//数据发送
			s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData1_4_CAN2.SendCanTxMsg));
			s_fnMotor_CANSend(CANx,(CanTxMsg* )&(MotorSendData5_8_CAN2.SendCanTxMsg));	
		}
}

//3508电机原始数据解析函数
static void s_fnM3508_RawDataDecode(M3508_TypeDef* st_data,CanRxMsg * msg)
{
	uint8_t i;
	int32_t temp_sum = 0;
	int16_t diff_val = 0;
	
	st_data->RecvData.Encoder_Val = (int16_t)((msg->Data[0]<<8)|(msg->Data[1]));//编码器值
	st_data->RecvData.Rotate_Speed = (int16_t)((msg->Data[2]<<8)|(msg->Data[3]));//电机反馈速度
	st_data->RecvData.Armature_Current = (int16_t)((msg->Data[4]<<8)|(msg->Data[5]));//电机反馈电流
	st_data->RecvData.Motor_Temperature = (int8_t)(msg->Data[6]);//电机温度

		//角度连续化处理	
	diff_val = st_data->RecvData.Encoder_Val - st_data->RecvData.Last_Encoder_Val;//获取前后两次编码器角度差值
	
	st_data->RecvData.Last_Encoder_Val = st_data->RecvData.Encoder_Val;//获取差值后记录上一次编码器值
	//记录旋转圈数
	if(diff_val < -4000)
	{
		st_data->RecvData.Number_Of_Turns ++;
	}
	else if(diff_val > 4000)
	{
		st_data->RecvData.Number_Of_Turns --;
	}
	//获取连续化处理后的转子角度
	st_data->RecvData.Rotate_Angle = st_data->RecvData.Number_Of_Turns * 360.f + st_data->RecvData.Encoder_Val/8192.f * 360.f;
	//转子角度除以电机减速比，就是电机轴转过的角度
	st_data->RecvData.Shaft_Angle = st_data->RecvData.Rotate_Angle/MOTOR_3508_REDUCTIONRATE;

	//电机速度滤波
	st_data->RecvData.Rotate_SpeedBuf[st_data->RecvData.Rotate_BufCount ++] = st_data->RecvData.Rotate_Speed;
	
	if(st_data->RecvData.Rotate_BufCount == ROTATE_SPEEDBUF_LEN)
	{
		st_data->RecvData.Rotate_BufCount = 0;
	}
	
	for(i = 0;i < ROTATE_SPEEDBUF_LEN; i++)
	{
		temp_sum +=	st_data->RecvData.Rotate_SpeedBuf[i];
	}
	st_data->RecvData.Rotate_FliterSpeed = (int32_t)(temp_sum/ROTATE_SPEEDBUF_LEN);

}


//底层CAN发送函数
static void s_fnMotor_CANSend(CAN_TypeDef *CANx, CanTxMsg *stMotorSendData)
{
	uint16_t i=0;
	u8 nMailBox=0;
	nMailBox=CAN_Transmit(CANx, stMotorSendData);
	while((CAN_TransmitStatus(CANx,nMailBox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;	//等待发送结束
	}
}


