#include "chassis.h"
#include "signal.h" 


#define CHASSIS_DISABLE 0//底盘控制失能，方便调试

#define CHASSIS_SPEED_MAX_X 8000 //底盘X方向最大速度
#define CHASSIS_SPEED_MAX_Y 8000 //底盘Y方向最大速度
#define CHASSIS_SPEED_RAW   1000//1000 //底盘旋转多大速度

Chassis_TypeDef P_stChassis ={Chassis_BlackOut};//底盘参数结构体

static void Chassis_SetWorkState(Chassis_TypeDef* st_data,e_Chassis_State state);//设置底盘工作状态
//static float Chassis_Twisting(Chassis_TypeDef* st_data);//底盘旋转
//static float Remote_StateSwitch(void);//底盘状态切换

void configChassis_ParaInit(void)
{
	fnPID_SetPara_P_I_D(&P_stChassis.Twist_PID,100,0,0);//参数关系不大
	fnPID_SetPara_OM(&P_stChassis.Twist_PID,500);
	fnPID_SetPara_IM(&P_stChassis.Twist_PID,20000);
}

//底盘控制任务 前进速度，后退速度，旋转速度
void Task_ChassisCtrl(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;//防止编译器警告
	
//	Laser_ON();
	while(1)
	{	
			float vx,vy,vw;
		
		switch(fnRemote_GetSwitchVal(Right_Switch))//嵌套多个中断应该会导致各中断冲突响应不及时而失控，用can2分开控制即可
		{
			case Up://遥控
			{
					Chassis_SetWorkState(&P_stChassis,Chassis_Working);
					vx = fnRemote_GetSensingVal(LeftSensing_X)/660. * CHASSIS_SPEED_MAX_X;
					vy = fnRemote_GetSensingVal(LeftSensing_Y)/660. * CHASSIS_SPEED_MAX_Y;
					vw = fnRemote_GetSensingVal(RightSensing_X)/660. * CHASSIS_SPEED_RAW;
			}break;
			
			case Middle://   
			{				
				
			}break;
			
			case Down://底盘掉电
			{
				Chassis_SetWorkState(&P_stChassis,Chassis_BlackOut);
			}break;
		}

#if CHASSIS_DISABLE
#else
		Chassis_Control(vx,vy,vw);//底盘控制
#endif
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_HMSM_STRICT,&err); //延时1ms	中断优先级高于任务优先级，执行任务函数等待时间延长感觉才可以进入其他中断函数，故改为5ms
//		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次

	}
}

//static float Chassis_Twisting(Chassis_TypeDef* st_data)//底盘角度控制，仅修改反馈即可
//{
//	fnPID_SetTarget(&st_data->Twist_PID,Remote_StateSwitch());
//	fnPID_SetFeedback(&st_data->Twist_PID,P_stHi219m.Yaw);
//	
//	fnPID_Calc(&st_data->Twist_PID);

//	st_data->Twist_PID.Output=-st_data->Twist_PID.Output;
//	//误差小于2度时置输出0
//	deadline_limit(st_data->Twist_PID.CurrentError,st_data->Twist_PID.Output,1);

//	return 2*st_data->Twist_PID.Output;
//}

//底盘运动控制  输入x,y轴速度和旋转速度w，结算出四轮相应速度
void Chassis_Control(float vx,float vy,float vw)
{
	static int32_t chassis_motor_speed[4];
	
	//速度解算
	chassis_motor_speed[0] = vy * 0.7f - vx * 0.7f + vw; //左前
	chassis_motor_speed[1] = vy * 0.7f + vx * 0.7f + vw; //左后
	chassis_motor_speed[2] = -vy * 0.7f - vx * 0.7f + vw;//右前
	chassis_motor_speed[3] = -vy * 0.7f + vx * 0.7f + vw;//右后
	
	switch(P_stChassis.State)
	{
		case Chassis_BlackOut:
		{
			fnMotor_SetCurrentVal(CAN1,P_stMotor_ChassisLB.CAN_ID,0);
			fnMotor_SetCurrentVal(CAN1,P_stMotor_ChassisRB.CAN_ID,0);
			fnMotor_SetCurrentVal(CAN1,P_stMotor_ChassisLF.CAN_ID,0);
			fnMotor_SetCurrentVal(CAN1,P_stMotor_ChassisRF.CAN_ID,0);
		}
			break;
		case Chassis_Working:
		{
			fnM3508_SpeedCotrol(&P_stMotor_ChassisLF,chassis_motor_speed[0]);
			fnM3508_SpeedCotrol(&P_stMotor_ChassisLB,chassis_motor_speed[1]);
			fnM3508_SpeedCotrol(&P_stMotor_ChassisRF,chassis_motor_speed[2]);
			fnM3508_SpeedCotrol(&P_stMotor_ChassisRB,chassis_motor_speed[3]);
		}break;
	}
}


//底盘设置工作状态
static void Chassis_SetWorkState(Chassis_TypeDef* st_data,e_Chassis_State state)
{
	st_data->State = state;
}

////底盘设置运动模式
//static void Chassis_SetMode(Chassis_TypeDef* st_data,e_ChassisMotion_State mode)
//{
//	st_data->Mode = mode;
//}

//static float Remote_StateSwitch(void)
//{
//	float target;

//	switch(fnRemote_GetSwitchVal(Left_Switch))
//	{
//		case Up:
//		{
//			target=230;
//		}break;
//		case Middle:
//		{
//			target=180;
//		}break;
//		case Down:
//		{
//			target=130;
//		}break;
//	}
//	return target;
//}

///*
//三轮速度分解 
//通过接近开关、行程开关、激光测距对坐标校正 校正的共用体需要在进行测试
//对于角度闭环，按照期望角度及给定速度走行，当达到距离允许值后切换下一点，先进行测试看效果
//*/
//void VelCal(Pose_t *path , Pose_t startPos , Pose_t lastPos)
//{
//	float alpha=0.0f;
//	float v1=0.0f;
//	float v2=0.0f;
//	float v3=0.0f;	
//	alpha=LineAngle(startPos.point,lastPos.point)+lastPos.direction;
//	v1=MAX_PLAN_VEL*cos(alpha * CHANGE_TO_ANGLE);
//	v2=MAX_PLAN_VEL*cos((120-alpha) * CHANGE_TO_ANGLE);
//	v3=MAX_PLAN_VEL*cos((120+alpha) * CHANGE_TO_ANGLE);	
//  Motor_SpeedCotrol(&Motor_ChassisLF,v1);
//	Motor_SpeedCotrol(&Motor_ChassisLB,v2);
//	Motor_SpeedCotrol(&Motor_ChassisRF,v3);
//}

//		int i = 0;	
//void Judge_Pathpoint(Pose_t *path , Pose_t startPos , Pose_t lastPos,int Num)
//{

//		float dis2FinalX = startPos.point.x - lastPos.point.x;
//		float dis2FinalY = startPos.point.y - lastPos.point.y;

//	if(sqrtf(dis2FinalX*dis2FinalX + dis2FinalY*dis2FinalY)<50.0f)//||?
//	{ 
//			i++;
//			if(i==Num)
//				i=0;
//	}
//}
//typedef enum
//{
//		Start_task,
//		First_task,
//	  Second_task,
//	  Third_task,
//	  Fourth_task,
//}walktask_t;
//全局变量结构体
//typedef struct
//	{
//	walktask_t walktask;
//	
//	}Robot_t;
//	
//	Robot_t Robot;
//void Walk(void)
//{

//	switch(Robot.walktask)
//	{
//		case Start_task:
//		{
//			USART_OUT(USART6,(uint8_t *)"ACT0\r\n");
//			Robot.walktask = First_task;
//		}
//		case First_task:
//		{			

//			VelCal(First_Task_Path, First_Task_Path[i], First_Task_Path[i+1]);

//			Judge_Pathpoint(First_Task_Path, GetPosPresent(), First_Task_Path[i+1],FIRST_TASK_PATH_NUM);
//			if(i==FIRST_TASK_PATH_NUM)
//			{			
//				Robot.walktask = Second_task;
//			return;
//			}
//			break;
//		}
//		case Second_task:
//		{
//		
//		
//		  break;
//		}
//		default:
//			break;
//	}
//}

