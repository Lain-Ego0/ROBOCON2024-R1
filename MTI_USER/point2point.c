/********************************************************************
*Copyright(C）2014-2016,沈阳艾克申机器人技术开发有限责任公司
*FileName：	   point2point.c
*Author：      Peng Xu
*Date：        2016/10/21
*Description：
*		       差速轮闭环直线函数
*			   使用前需要更改AngleClosedLoop()函数（角度闭环函数），对于电机pid的调整
*！！注意：初始使用时，请小速度调试，避免因P、D参数不适合或者错误导致运动对象异常运动造成危险
*Version：     Beta版
*
********************************************************************/


#include "math.h"
#include "point2point.h" 
#include "path.h" 
#include "motor.h" 



/**
* @name 	AngleAdd
* @brief	对-180,180交界处作处理
* @param	target_angle:目标角度;
					right_angle:直角;
* @retval 目标直线加90度，求出垂线方向
*/
static float AngleAdd(float target_angle, float right_angle)
{
	float result = 0.0f;
	result = target_angle + right_angle;
	if (result < -180.0f)  result += 360.0f;
	if (result >  180.0f)  result -= 360.0f;
	return result;	
}

/**
* @name 	AngleSub
* @brief	对-180,180交界处作处理
* @param	minuend: 被减数;
			subtrahend: 减数 A - B,A为被减数，B为减数;
* @retval 做角度差值 目标角度-当前角度
*/
float AngleSub(float minuend, float subtrahend)
{
	float result = 0.0f;
	result = minuend - subtrahend;
	if (result >  180.0f)  result -= 360.0f;
	if (result < -180.0f)  result += 360.0f;
	return result;
}

/**
* @name 	TwoLineIntersection2
* @brief	计算两条直线的交点
* @param	line1:直线1;
			line2:直线2;
* @retval  获取两垂直线交点
*/
static Point_t TwoLineIntersection(Pose_t line1, Pose_t line2)
{
	Point_t intersection;
	//斜率
	float k1 = 0.0f;
	float k2 = 0.0f;

	//因为浮点运算,未对与x轴垂直的直线处理，即不可能为零
	k1 = tan(line1.direction * CHANGE_TO_RADIAN);
	k2 = tan(line2.direction * CHANGE_TO_RADIAN);

	intersection.x = (line1.point.x*k1 - line1.point.y - line2.point.x * k2 + line2.point.y) / (k1 - k2);
	intersection.y = k1 * (intersection.x - line1.point.x) + line1.point.y;

	return intersection;
}


/**
* @name 	LineAngle
* @brief	计算两点直线方向角度
* @param	pointStart:起始点：
					pointEnd:终止点;
* @retval 两点斜率
*/
static float LineAngle(Point_t pointStart, Point_t pointEnd)
{
	float a = 0.0f;
	float b = 0.0f;
	
	a = pointEnd.y - pointStart.y;
	b = pointEnd.x - pointStart.x;
	//atan2f范围可以包含-180到180  
	return (atan2f(a, b)); 
}

static float s_angleErrOld = 0.0f; 
void Point2Ponit_Deinit()
{
	s_angleErrOld = 0.0f;
}

/**
  * @name 	    AngleClosedLoop（可以作为姿态闭环）
  * @brief  	角度闭环
  * @param  	presentAngle: 当前角度;（主要为定位当前角度）
				targetAngle: 目标角度;
				vellP: 旋转速度比例;
				vellBase:前进速度;
虽以差速轮为模型，但也可作为姿态环的程序一开始的期望角度均为零，使它保持在零度，参数调得好一般不会出现波动的情况
当位姿变化时使之以固定角速度旋转(即速度环)，得一直调用保证期望角度
  * @retval 	
  */
static float AngleClosedLoop(float presentAngle,float targetAngle,float vellP)
{
#define P1    1000
#define P2    500
#define P3    2500
//#define VRATE 31.38f //为电机减速比
//	
//	
//	//实际速度转换
//	vellBase = VRATE * vellBase;
	//目标角度与实际角度的差值
	float angleErr = 0.0f;				
	//目标角度与实际角度的差值开二次根
	float angleErrSqrt = 0.0f;			
	//上一周期目标角度与实际角度的差值
	float angleErrErr = 0.0f;			
	//旋转速度
	float vellErr = 0.0f;				
	
	//求目标角度与实际角度的差值
	angleErr = AngleSub(targetAngle , presentAngle);

	//进行开根处理，目的压缩偏差量。
	if(angleErr > 0.0f)										
	{
		angleErrSqrt = sqrt(angleErr);
	}
	else
	{
		angleErrSqrt = -sqrt(fabsf(angleErr));
	}
	
	//求本周期角度差值与上周期角度差值的差值
	angleErrErr = angleErr - s_angleErrOld;				
	
	//当偏差过大时用P调解，当偏差不大是用PD调解
	if(fabsf(angleErr) > 10.0f)								
	{
		vellErr = angleErrSqrt * P1 * vellP;
	}
	else
	{
		vellErr = angleErrSqrt * P2 * vellP + angleErrErr * P3;
	}
	
	s_angleErrOld = angleErr;
	
	return vellErr;
}



/**
  * @name 	MvByLine
  * @brief  	直线闭环，速度为正
  * @param  	presentLine：当前姿态；
				targetLine：v目标点目标方向，等同于目标直线；
				speed:直线速度;
  * @retval 	返回值为当前点到目标点距离。单位mm  得10ms调用一次
达到需要的距离偏差时切换下一点
  */

int i = 0;	
void Judge_Pathpoint(Pose_t *path , Pose_t presentLine , Pose_t targetLine,int Num)
	{
		float dis2FinalX = presentLine.point.x - targetLine.point.x;
		float dis2FinalY = presentLine.point.y - targetLine.point.y;
	if(sqrtf(dis2FinalX*dis2FinalX + dis2FinalY*dis2FinalY)<30.0f)//||?
	{ 
			i++;
			if(i==Num)
				i=0;
	}
}

void PathFollowing(Pose_t *path,Pose_t presentLine, Pose_t targetLine)
{
	float v1=0.0f;
	float v2=0.0f;
	float v3=0.0f;
	float vw=0;
	
	//当前点到目标直线的垂线
	Pose_t verticalLine;
	//中点	
	Point_t  midpoint;
	//控制的目标角度
	float targetAngle = 0.0f;	
	//目标直线加90度，求出垂线方向
	verticalLine.direction = AngleAdd(targetLine.direction, 90.0f);
	//把当前点赋给垂线
	verticalLine.point = presentLine.point;		
	//计算垂线与目标直线交点
	midpoint = TwoLineIntersection(targetLine, verticalLine);
	//计算中点横坐标	
	midpoint.x = (midpoint.x + targetLine.point.x) * 0.5f;													  
	//计算中点纵坐标
	midpoint.y = (midpoint.y + targetLine.point.y) * 0.5f;													  
	//计算当前点到中点方向
	targetAngle = LineAngle(presentLine.point, midpoint);			
	if(targetAngle>=0)
	{
			if(targetLine.point.y>midpoint.y)//Y正半轴
				targetAngle=targetAngle;//0~90
			if(targetLine.point.y<midpoint.y)//Y负半轴
				targetAngle=targetAngle-180;//-90~-180
	}		
	else if(targetAngle<0)
	{
			if(targetLine.point.y>midpoint.y)//Y正半轴
				targetAngle=180+targetAngle;//90~180
			if(targetLine.point.y<midpoint.y)//Y负半轴
				targetAngle=-targetAngle;//0~-90
	}	
	//进行角度闭环控制
  vw=AngleClosedLoop(targetLine.direction,presentLine.direction,2.0f);
	//速度分解
	v1=MAX_PLAN_VEL*cos(targetAngle * CHANGE_TO_ANGLE);
	v2=MAX_PLAN_VEL*cos((120-targetAngle) * CHANGE_TO_ANGLE);
	v3=MAX_PLAN_VEL*cos((120+targetAngle) * CHANGE_TO_ANGLE);	
  Motor_SpeedCotrol(&Motor_ChassisLF,v1-vw);
	Motor_SpeedCotrol(&Motor_ChassisLB,v2-vw);
	Motor_SpeedCotrol(&Motor_ChassisRF,v3-vw);
}

/**
* @brief  AngleLimit限制角度在-180~180
  * @note
* @param  
* @retval 
  */
void AngleLimit(float *angle)
{
	static uint8_t recursiveTimes = 0;
	
	recursiveTimes++;
	
	if(recursiveTimes<100)
	{
		if(*angle>180.0f)
		{
			*angle-=360.0f;
			AngleLimit(angle);
		}
		else if(*angle<-180.0f)
		{
			*angle+=360.0f;
			AngleLimit(angle);
		}
	}
	
	recursiveTimes--;
}
/**
* @brief  ReturnLimitAngle返回限制角度
  * @note
* @param  
* @retval 
  */
float ReturnLimitAngle(float angle)
{
	static uint8_t recursiveTimes = 0;
	
	recursiveTimes++;
	
	if(recursiveTimes<100)
	{
		if(angle>180.0f)
		{
			angle = ReturnLimitAngle(angle - 360.0f);
		}
		else if(angle<-180.0f)
		{
			angle = ReturnLimitAngle(angle + 360.0f);
		}
	}
	
	recursiveTimes--;
	
	return angle;
}


	
	Robot_t Robot;
void Walk()
{
//	 static LaserSend_t laser={0};
	 
	switch(Robot.walktask)
	{
		case Start_task:
		{
//			laser.value[0]=176.00;
//			USART_OUT(USART6,(uint8_t *)"ACTJangle\r\n");
			USART_OUT(USART6,(uint8_t *)"ACT0\r\n");
			Robot.walktask = First_task;
		}
		case First_task:
		{			
			float dis2FinalX = GetX() - First_Task_Path[FIRST_TASK_PATH_NUM -1].point.x;
			float dis2FinalY = GetY() - First_Task_Path[FIRST_TASK_PATH_NUM -1].point.y;
			
			Judge_Pathpoint(First_Task_Path,GetPosPresent(),First_Task_Path[i+1],FIRST_TASK_PATH_NUM);
			PathFollowing(First_Task_Path,GetPosPresent(),First_Task_Path[i+1]);
			if((sqrtf(dis2FinalX*dis2FinalX + dis2FinalY*dis2FinalY)<50.0f))
			{
//				&&JudgeSpeedLessEqual(700.0f))\
//						||(fabs(GetX())>=8700.0f&&JudgeSpeedLessEqual(700.0f)))
//				if(gRobot.courtID == BLUE_COURT)
//				{
//					OutputVel2Wheel(700.0f,180.0f,0.0f);
//				}
//				else if(gRobot.courtID == RED_COURT)
//				{
//					OutputVel2Wheel(700.0f,0.0f,0.0f);
//				}	
				
//				gRobot.teleCommand.nextFlag = TELENOCMD;
				
				Robot.walktask = Second_task;	

				return;
			} 
			break;
		}
		case Second_task:
		{
		
		
		  break;
		}
		default:
			break;
	}
}

