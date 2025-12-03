#include "motor.h"


//用户定义电机结构体
Motor_TypeDef Motor_ChassisRF = {1};//底盘右前电机
Motor_TypeDef Motor_ChassisLF = {2};//底盘左前电机
Motor_TypeDef Motor_ChassisLB = {3};//底盘左后电机
Motor_TypeDef Motor_ChassisRB = {4};//底盘右后电机

Motor_TypeDef Motor_PinchTurn = {5};//翻转电机
Motor_TypeDef Motor_Pinch = {6};		//夹取电机



//电机参数初始化
void configMotor_ParaInit(void)
{
	//底盘电机配置
	//左前
	PID_SetPara_P_I_D(&Motor_ChassisLF.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_ChassisLF.SpeedPID,1000);
	PID_SetPara_OM(&Motor_ChassisLF.SpeedPID,5000);
	//右前
	PID_SetPara_P_I_D(&Motor_ChassisRF.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_ChassisRF.SpeedPID,1000);
	PID_SetPara_OM(&Motor_ChassisRF.SpeedPID,5000);
	//左后
	PID_SetPara_P_I_D(&Motor_ChassisLB.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_ChassisLB.SpeedPID,1000);
	PID_SetPara_OM(&Motor_ChassisLB.SpeedPID,5000);
	//右后
	PID_SetPara_P_I_D(&Motor_ChassisRB.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_ChassisRB.SpeedPID,1000);
	PID_SetPara_OM(&Motor_ChassisRB.SpeedPID,5000);

	//夹取翻转
	PID_SetPara_P_I_D(&Motor_PinchTurn.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_PinchTurn.SpeedPID,1000);
	PID_SetPara_OM(&Motor_PinchTurn.SpeedPID,5000);
	//角度环
	PID_SetPara_P_I_D(&Motor_PinchTurn.AnglePID,11,0,0);
	PID_SetPara_IM(&Motor_PinchTurn.AnglePID,100);
	PID_SetPara_OM(&Motor_PinchTurn.AnglePID,300);
	
	//夹取翻转
	PID_SetPara_P_I_D(&Motor_Pinch.SpeedPID,5,0,0);
	PID_SetPara_IM(&Motor_Pinch.SpeedPID,1000);
	PID_SetPara_OM(&Motor_Pinch.SpeedPID,5000);
	//角度环
	PID_SetPara_P_I_D(&Motor_Pinch.AnglePID,11,0,0);
	PID_SetPara_IM(&Motor_Pinch.AnglePID,100);
	PID_SetPara_OM(&Motor_Pinch.AnglePID,300);

}

//Can数据解析
void Motor_CanRecvDataDecode(CAN_TypeDef* canx,CanRxMsg * msg)
{
	if(canx == CAN1)
	{
	//根据对应ID,进行数据解析
			switch(msg->StdId)
			{
				case MOTOR_CHASSIS_RF_CAN_ID:
				{
					Motor_RawDataDecode(&Motor_ChassisLF,msg);//原始数据解析
				}break;
				case MOTOR_CHASSIS_LF_CAN_ID:
				{
					Motor_RawDataDecode(&Motor_ChassisRF,msg);//原始数据解析
				}break;
				case MOTOR_CHASSIS_LB_CAN_ID:
				{
					Motor_RawDataDecode(&Motor_ChassisLB,msg);//原始数据解析
				}break;
				case MOTOR_CHASSIS_RB_CAN_ID:
				{
					Motor_RawDataDecode(&Motor_ChassisRB,msg);//原始数据解析
				}break;
			//				case MOTOR_PINCH_TURN_CAN_ID:
			//		{
			//			Motor_RawDataDecode(&Motor_PinchTurn,msg);//原始数据解析
			//		}break;
			//				case MOTOR_PINCH_CAN_ID:
			//		{
			//			Motor_RawDataDecode(&Motor_Pinch,msg);//原始数据解析
			//		}break;
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
		case MOTOR_PINCH_TURN_CAN_ID:
		{
			Motor_RawDataDecode(&Motor_PinchTurn,msg);//原始数据解析
		}break;		
		case MOTOR_PINCH_CAN_ID:
		{
			Motor_RawDataDecode(&Motor_Pinch,msg);//原始数据解析
		}break;		
			default:
			{
			}break;
		}
	}
	
}

//电机速度控制函数 
void Motor_SpeedCotrol( Motor_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	PID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	PID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	AbsPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = PID_GetOutput(&st_data->SpeedPID);//获取控制量
	
	Motor_SetCurrentVal(CAN1,st_data->CAN_ID,ctrl_val);//控制执行电机
}

void Motor_ArmSpeedCotrol( Motor_TypeDef* st_data,float target_speed)
{
	float ctrl_val;
	
	PID_SetTarget(&st_data->SpeedPID,target_speed);//设置目标
	PID_SetFeedback(&st_data->SpeedPID,st_data->RecvData.Rotate_FliterSpeed);//获取反馈值;
	AbsPID_Calc(&st_data->SpeedPID);//PID计算
	
	ctrl_val = PID_GetOutput(&st_data->SpeedPID);//获取控制量 
	
	Motor_SetCurrentVal(CAN2,st_data->CAN_ID,ctrl_val);//控制执行电机
}

//3508电机角度控制函数 双环PID控制
void fnM3508_AngleCotrol( Motor_TypeDef* st_data,float target_angle)
{
	float pid_output;
	
	PID_SetTarget(&st_data->AnglePID,target_angle);//设置角度环目标值
	PID_SetFeedback(&st_data->AnglePID,st_data->RecvData.Shaft_Angle);//获取角度反馈
	AbsPID_Calc(&st_data->AnglePID);//计算PID输出
	
	pid_output = PID_GetOutput(&st_data->AnglePID);//获取角度环输出
	
	Motor_ArmSpeedCotrol(st_data,pid_output);//将角度环输出作为速度环目标值
}


//电机电调设置控制电流值
void Motor_SetCurrentVal(CAN_TypeDef *CANx,uint8_t motor_id,int16_t cm_i)
{
	static CanSend_Type MotorSendData1_4;
	static CanSend_Type MotorSendData5_8;

	CANx == CAN1?(MotorSendData1_4.CANx = 1):(MotorSendData1_4.CANx = 2); //若CAN参数为CAN1则编号为1，否则为2
	CANx == CAN1?(MotorSendData5_8.CANx = 1):(MotorSendData5_8.CANx = 2);
	
	MotorSendData1_4.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER1_4;
	MotorSendData1_4.SendCanTxMsg.DLC = 8;
	MotorSendData1_4.SendCanTxMsg.IDE = CAN_ID_STD;
	MotorSendData1_4.SendCanTxMsg.RTR = CAN_RTR_Data;
	
	MotorSendData5_8.SendCanTxMsg.StdId = MOTOR_CANSEND_IDENTIFIER5_8;
	MotorSendData5_8.SendCanTxMsg.DLC = 8;
	MotorSendData5_8.SendCanTxMsg.IDE = CAN_ID_STD;
	MotorSendData5_8.SendCanTxMsg.RTR = CAN_RTR_Data;
	
	//若ID为1-4之间则使用标识符0x200，id为5-8之间时使用标识符0x1ff
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
	Motor_CANSend(CANx,(CanTxMsg* )&(MotorSendData1_4.SendCanTxMsg));
	Motor_CANSend(CANx,(CanTxMsg* )&(MotorSendData5_8.SendCanTxMsg));	
}

//3508电机原始数据解析函数
static void Motor_RawDataDecode(Motor_TypeDef* st_data,CanRxMsg * msg)
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
static void Motor_CANSend(CAN_TypeDef *CANx, CanTxMsg *MotorSendData)
{
	uint16_t i=0;
	u8 nMailBox=0;
	nMailBox=CAN_Transmit(CANx, MotorSendData);
	while((CAN_TransmitStatus(CANx,nMailBox)==CAN_TxStatus_Failed)&&(i<0XFFF))
	{
		i++;	//等待发送结束
	}
}


