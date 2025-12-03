#include "user_task.h"
#include "imu_data_decode.h"

//信号量
SemaphoreHandle_t P_shH219DataDecode_Binary;
int work_states=1;//work_states为1是掉电状态

//int states_change_for_DJ(void)
//{
//	int DJ_work_state=1;
//	int temp;
//	temp=fnRemote_GetSwitchVal(Left_Switch);
//	
//	if(temp==3)
//	{
//		DJ_work_state=1;
//	}

//	return DJ_work_state;

//}

//主控制任务，整车运动参数控制
void Task_Main(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{	
		if(Remote_control_data[8]==1)
		{
			
		USE_CAN2_SpeedCotrol_M3508(&Can2_Moto6,4000);//同步轮
		}
		if(Remote_control_data[8]==0)
		{	
			
		USE_CAN2_SpeedCotrol_M3508(&Can2_Moto6,0);//同步轮
		}
		
		
		
    if(P_stRemoteData_Recv.Key.R == 1){Updata_Rabbit_ZERO();}//按键清空
		work_states=Remote_control_data[4];//左拨杆拨到最上面
//		work_states=states_change_for_DJ();//fnRemote_GetSwitchVal(Left_Switch);
	
		if(work_states==1)
		{
			Control_SetCurrentVal(CAN1,Can1_Moto1.CAN_ID,0);
			Control_SetCurrentVal(CAN1,Can1_Moto2.CAN_ID,0);
			Control_SetCurrentVal(CAN1,Can1_Moto3.CAN_ID,0);
			Control_SetCurrentVal(CAN1,Can1_Moto4.CAN_ID,0);
			Control_SetCurrentVal(CAN1,Can1_Moto5.CAN_ID,0);
			Control_SetCurrentVal(CAN1,Can1_Moto6.CAN_ID,0);

			Control_SetCurrentVal(CAN2,Can2_Moto1.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto2.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto3.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto4.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto5.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto6.CAN_ID,0);
			Control_SetCurrentVal(CAN2,Can2_Moto7.CAN_ID,0);
		}
		
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}

//计时任务
void Task_TimeCount(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{

		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}

//陀螺仪数据解析任务
void Task_Hi219mDataDecode(void *Parameters)
{
	BaseType_t stError=pdFALSE;
	uint16_t i = 0;
	uint8_t ch;
	
	while(1)
	{
		if(P_shH219DataDecode_Binary!=NULL)
		{
			stError=xSemaphoreTake(P_shH219DataDecode_Binary,portMAX_DELAY);	//获取信号量
			if(stError==pdTRUE)												//获取信号量成功
			{
				for (i = 0;i < P_uintH219BuffLength;i++)  
				{  
					ch = P_uintH219MDataBuffer[i]; 
					Packet_Decode(ch);
					
					fnHi219m_DataDecode(&P_stHi219m); //获取陀螺仪值
				} 
			}
		}
		else if(stError==pdFALSE)
		{
			vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
		}
	}
}



//////键盘跳变值获取
void Task_DataGet(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{	
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Q,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_E,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_R,1);//原值50
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_F,100);//原来的值为100
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_G,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Z,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_X,1);	
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_C,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_B,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_V,1);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Shift,3);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Ctrl,2);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_Switch,100);
		Key_Jump_Flag_Get(&P_stRemoteData_Recv,KEYNumber_MouseLeft,1);
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
}



//底盘调控运行
float votion,lastvotion=0;//votion为输入源
float votion_phone,votion_remoto,votion_key;//DJ_votion_remoto;//***
float votionbb=0;
float votionaa=0;
float votioncc=0;
int tf=0,tb=0;
int af=0,ab=0;
//发射
int a=1500;//上
int b=3000;//左
int c=3000;//右
int d=1500;//下
//int launch_states=0;

void Task_ChassisCtrl(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{ 

		//遥控控制

		TOur_remoto.vx=Remote_control_data[1]/660.f * 5000;
		TOur_remoto.vy=Remote_control_data[2]/660.f * 5000;
		votion_remoto=Remote_control_data[3]/660.f * 0.1f;
		
//		//大疆遥控
//		DJ_remoto.vx = fnRemote_GetSensingVal(LeftSensing_X)/660. * 4000;//左摇杆值处理
//		DJ_remoto.vy = fnRemote_GetSensingVal(LeftSensing_Y)/660. * 4000;//左摇杆值处理
//		DJ_votion_remoto = -fnRemote_GetSensingVal(RightSensing_X)/660. * 0.09;//右摇杆值处理旋转

//		launch_states=fnRemote_GetSensingVal(RightSensing_Y)/660. * 4000;
			
		//键盘控制
//		if(P_stRemoteData_Recv.Key.W == 1){TOur_key.vy = 330/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.S == 1){TOur_key.vy = -330/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.W==0&&P_stRemoteData_Recv.Key.S==0){TOur_key.vy = 0/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.W==1&&P_stRemoteData_Recv.Key.S==1){TOur_key.vy = 0/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.D == 1){TOur_key.vx = 330/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.A == 1){TOur_key.vx = -330/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.A==0&&P_stRemoteData_Recv.Key.D==0){TOur_key.vx = 0/660. * 5000;}
//		if(P_stRemoteData_Recv.Key.A==1&&P_stRemoteData_Recv.Key.D==1){TOur_key.vx = 0/660. * 5000;}
//		
//		if(P_stRemoteData_Recv.Key.Q==1){votion_key = 0.1;}//原系数值为0.09
//		if(P_stRemoteData_Recv.Key.E==1){votion_key = -0.1;}//原系数值为0.09
//		if(P_stRemoteData_Recv.Key.Q==0&&P_stRemoteData_Recv.Key.E==0){votion_key =0;}
		
		//F5左转90°，F7右转90°·
		if(Remote_control_data[12]==1){tf++;if(tf>=72&&af==1){votion=votion+90;tf=0;af=0;}}//超过72ms转90°
		if(Remote_control_data[12]==0){votion=votion;af=1;}
		if(Remote_control_data[14]==1){tb++;if(tb>=72&&ab==1){votion=votion-90;tb=0;ab=0;}}
		if(Remote_control_data[14]==0){votion=votion;ab=1;}
		
/////////////////////////////////////////自制遥控/////////////////////////////////////////////////////////////////////
		//发射
//		if(Remote_control_data[8]==1)
//		{
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto1,a);//下
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto5,-b);	//左
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto3,c);//右
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto4,-d);//上
//			
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto5,4000);//同步轮
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto6,4000);//同步轮
//			
//	
//		}
//		if(Remote_control_data[8]==0)
//		{	
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto1,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto5,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto3,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto4,0);
//			
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto5,0);//同步轮
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto6,0);//同步轮
//	
//		}
//		//抓夹--闭合与打开
//		if(Remote_control_data[9]==1)
//		{
//			GPIO_SetBits(GPIOE,GPIO_Pin_5);
//		}
//		if(Remote_control_data[9]==0)
//		{
//			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//		}
//		//抓夹--抬升

//				
//////////////////////////////////////大疆遥控////////////////////////////////////////////////////////////////
//		if(fnRemote_GetSwitchVal(Left_Switch)==1&&fnRemote_GetSwitchVal(Right_Switch)==1)//抓夹闭合
//		{
//			GPIO_SetBits(GPIOE,GPIO_Pin_5);
//			
//		}
//		if(fnRemote_GetSwitchVal(Left_Switch)==1&&fnRemote_GetSwitchVal(Right_Switch)==2)//抓夹打开
//		{
//			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//			
//		}
//		if(fnRemote_GetSwitchVal(Left_Switch)==2&&fnRemote_GetSwitchVal(Right_Switch)==2)//抓夹抬起
//		{
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto5,-600);
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto6,-600);
//		}
//		if(fnRemote_GetSwitchVal(Left_Switch)==2&&fnRemote_GetSwitchVal(Right_Switch)==1)//抓夹下降
//		{
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto1,0);
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto1,0);
//		}
//		if(launch_states>=200)//发射
//		{
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto1,a);//下
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto2,-b);	//左
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto3,c);//右
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto4,-d);//上
//			
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto5,-4000);//同步轮
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto6,-4000);//同步轮
//		}
//		if(0<=launch_states&&launch_states<200)//发射停止
//		{
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto1,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto2,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto3,0);
//			USE_CAN2_SpeedCotrol_M3508(&Can2_Moto4,0);
//			
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto5,0);//同步轮
//			USE_CAN1_SpeedCotrol_M3508(&Can1_Moto6,0);//同步轮
//		}
//			
			
		TOur.vx =TOur_key.vx+TOur_phone.vx+TOur_remoto.vx+DJ_remoto.vx;//3种VX控制聚合函数
		TOur.vy =TOur_key.vy+TOur_phone.vy+TOur_remoto.vy+DJ_remoto.vy;//3种VY控制聚合函数
		
		votionbb=votion_key+votion_remoto+votion_phone;//+DJ_votion_remoto;//3种角度控制聚合函数，用不到其他的VW

		if(work_states!=1)votion+=votionbb;
		Chassis_twistt(&P_stChassis,70,90);//赋值TOur.vw
		if(work_states!=1)
		Chassis_Control(TOur.vx,TOur.vy,TOur.vw);//底盘调控运行

		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
	
}




void Overturn_Ctrl(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{
		 
//		if(Remote_control_data[10]==1)
//		{
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto2,-160);
//			USE_CAN1_AngleCotrol_M3508(&Can1_Moto6,-160);
//		}
//		if(Remote_control_data[10]==0)
//		{
//			USE_CAN2_AngleCotrol_M3508(&Can2_Moto2,0);
//			USE_CAN1_AngleCotrol_M3508(&Can1_Moto6,0);
//		}
				
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
	
}



void Put_Ring_Ctrl(void *Parameters)
{
	portTickType CurrentControlTick = 0;//当前系统时间	
	
	while(1)
	{
		 

			
		vTaskDelayUntil(&CurrentControlTick, 1/ portTICK_RATE_MS); //控制任务运行周期  1ms运行一次
	}
	
}



