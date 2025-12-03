#include "ChassisCtrl.h"



Speed_con TOur;
Speed_con TOur_key;
Speed_con TOur_phone;
Speed_con TOur_remoto;
Speed_con DJ_remoto;/***/

Chassis_TypeDef P_stChassis ={Chassis_BlackOut};//底盘参数结构体

float Angle_difference=0;
float Mn=0;
float lastAngle_difference=0;
float Feedback_angle=0;
float Angle_GetOutput=0;
float Targetangle=0;
void Chassis_twistt(Chassis_TypeDef* st_data,float kp,float ki)
{
//		kp=70;
//		ki=90;
		Targetangle=votion;
		Feedback_angle = P_stHi219m.Continuous_Yaw-180.0f;    
		Angle_difference=Targetangle-Feedback_angle;
		Angle_GetOutput=kp*Angle_difference+ki*(Angle_difference-lastAngle_difference);
		lastAngle_difference=Angle_difference;
		if(Angle_difference<0.5f&&Angle_difference>-0.5f){Angle_difference=0;}
		if(Angle_GetOutput>2000){Angle_GetOutput=2000;}
		if(Angle_GetOutput<-2000){Angle_GetOutput=-2000;}
		TOur.vw =Angle_GetOutput;
}


//底盘运动控制  输入x,y轴速度和旋转速度w，结算出四轮相应速度
void Chassis_Control(float vx,float vy,float vw)
{

	static int32_t chassis_motor_speed[5];
	
	//速度解算
	chassis_motor_speed[0] = vy * 0.7f - vx * 0.7f - vw; //左前
	chassis_motor_speed[1] = vy * 0.7f + vx * 0.7f -vw; //左后
	chassis_motor_speed[2] = -vy * 0.7f - vx * 0.7f - vw;//右前
	chassis_motor_speed[3] = -vy * 0.7f + vx * 0.7f - vw;//右后


	USE_CAN1_SpeedCotrol_M3508(&Can1_Moto1,chassis_motor_speed[3]);
	USE_CAN1_SpeedCotrol_M3508(&Can1_Moto2,chassis_motor_speed[1]);
	USE_CAN1_SpeedCotrol_M3508(&Can1_Moto3,chassis_motor_speed[2]);
	USE_CAN1_SpeedCotrol_M3508(&Can1_Moto4,chassis_motor_speed[0]);

}


