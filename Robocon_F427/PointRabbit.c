#include "PointRabbit.h"
#include "math.h"
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
int rabbit_zftr=0;

/////////////////////////以下函数有问题需要修改
/**
* @name 	Update_Position to 0
* @brief	字符串拼接
* @param	Position_system Position_x
* @retval
*/
void Stract(char strDES[],char strSour[],int num)
{
	int i=0,j=0;
	while(strDES[i]!=0) i++;
	for(j=0;j<num;j++)
	strDES[i++]=strSour[j];
}

/**
* @name 	Update_Position to 0
* @brief	对当前的X角度进行更新为New_X
* @param	Position_system Position_x
* @retval
*/
void Update_PositionX(float New_X)
{

	int i = 0;
	char Update_x[8]="ACTX";
//	float X=0.0;
	static union New_set
	{
	float X;
	char data[4];
	}New_set;
	
	New_set.X=New_X;
	
	Stract(Update_x,New_set.data,4);
	for(i = 0;i<8;i++)
	{
	while(USART_GetFlagStatus(UART7,USART_FLAG_TXE) == RESET) 
		USART_SendData(UART7,Update_x[i]);
	}
}

/**
* @name 	Update_Position to 0
* @brief	对当前的Y角度进行更新为New_Y
* @param	Position_system Position_y
* @retval
*/
void Update_PositionY(float New_Y)
{

	int i = 0;
	char Update_y[8]="ACTY";
	
	static union
	{
	float Y;
	char data[4];
	}New_set;
	
	New_set.Y=New_Y;
	
	Stract(Update_y,New_set.data,4) ;
	for(i = 0;i<8;i++)
	{
	while(USART_GetFlagStatus(UART7,USART_FLAG_TXE) == RESET) 
		USART_SendData(UART7,Update_y[i]);
	}
}

/**
* @name 	Update_Position to 0
* @brief	对当前的偏航角度进行更新为New_A
* @param	Position_system Position_a
* @retval
*/
void Update_PositionA(float New_A)
{

	int i = 0;
	char Update_a[8]="ACTJ";
	
	static union
	{
	float A;
	char data[4];
	}New_set;
	
	New_set.A=New_A;
	
	Stract(Update_a,New_set.data,4) ;
	for(i = 0;i<8;i++)
	{
	while(USART_GetFlagStatus(UART7,USART_FLAG_TXE) == RESET) 
		USART_SendData(UART7,Update_a[i]);
	}
}
//////////////////////以上函数有问题需要修改

/**
* @name   Updata_Rabbit_ZERO****
* @brief  对Position的数值进行更新为0
* @param	
* @retval
*/

void Updata_Rabbit_ZERO(void)
{ 
	int i = 0;
	char Update_a[4]="ACT0";
	for(i = 0;i<=3;i++)
	{ 
	   USART_SendData(UART8,Update_a[i]);
	   while(USART_GetFlagStatus(UART8,USART_FLAG_TC) == 0);
	   USART_ClearFlag(UART8,USART_FLAG_TC);
	}
}

///////////////////////////////////初始归0
void RabbitATatget_zero(void)
{
		if(rabbit_zftr==0)
    {
		for(int int_time=0;int_time<=300;int_time++)
		{
	  Updata_Rabbit_ZERO();
		if(int_time==250)rabbit_zftr=1;
		}
		}
}

/**
* @name 	CcltAngleAdd
* @brief	对-180,180交界处作处理
* @param	angle1:角度1;
			angle2:角度2;
* @retval
*/
static float CcltAngleAdd(float angle1, float angle2)
{
	float result = 0.0f;
	result = angle1 + angle2;
	if (result >  180.0f)  result -= 360.0f;
	if (result < -180.0f)  result += 360.0f;
	return result;
	
}


/**
  * @name 		VelTwoCtl
  * @brief  	正数朝前
  * @param  	vellBase:朝前速度；
			    vellErr:符号为正，朝左拐
  * @retval 	
  */
static void VelDecomposeCtl(int vellBase,int vellErr)
{
	//1号电机速度赋值函数
//	VelCrl(MOTOR_ONE,-vellBase + vellErr);				
//	//2号电机速度赋值函数
//	VelCrl(MOTOR_TWO, vellBase + vellErr);				
}


/**
* @name 	CcltAngleSub
* @brief	对-180,180交界处作处理
* @param	minuend: 被减数;
			subtrahend: 减数 A - B,A为被减数，B为减数;
* @retval
*/
float CcltAngleSub(float minuend, float subtrahend)
{
	float result = 0.0f;
	result = minuend - subtrahend;
	if (result >  180.0f)  result -= 360.0f;
	if (result < -180.0f)  result += 360.0f;
	return result;
}

/**
* @name 	CcltTwoLineIntersection2
* @brief	计算两条直线的交点
* @param	line1:直线1;
			line2:直线2;
* @retval
*/
static ActPoint CcltTwoLineIntersection2(ActLine2 line1, ActLine2 line2)
{
	ActPoint intersection;
	//斜率
	float k1 = 0.0f;
	float k2 = 0.0f;

	//因为浮点运算,未对与x轴垂直的直线处理。
	k1 = tan(line1.angle * CHANGE_TO_RADIAN);
	k2 = tan(line2.angle * CHANGE_TO_RADIAN);

	intersection.x = (line1.point.x*k1 - line1.point.y - line2.point.x * k2 + line2.point.y)
						 / (k1 - k2);
	intersection.y = k1 * (intersection.x - line1.point.x) + line1.point.y;

	return intersection;
}


/**
* @name 	CcltLineAngle
* @brief	计算两点直线方向角度
* @param	pointStart:起始点：
			pointEnd:终止点;
* @retval
*/
static float CcltLineAngle(ActPoint pointStart, ActPoint pointEnd)
{
	float a = 0.0f;
	float b = 0.0f;
	
	a = pointEnd.y - pointStart.y;
	b = pointEnd.x - pointStart.x;
	//atan2f范围可以包含-180到180  
	return (atan2f(a, b) * CHANGE_TO_ANGLE); 
}

static float s_angleErrOld = 0.0f; 
void Point2Ponit_Deinit()
{
	s_angleErrOld = 0.0f;
}

/**
  * @name 	    AngleClosedLoop
  * @brief  	角度闭环
  * @param  	presentAngle: 当前角度;
				targetAngle: 目标角度;
				vellP: 旋转速度比例;
				vellBase:前进速度;
  * @retval 	
  */
static void AngleClosedLoop(float presentAngle,float targetAngle,float vellP,float vellBase)
{
#define P1    1000
#define P2    500
#define P3    2500
#define VRATE 31.38f
	
	
	//实际速度转换
	vellBase = VRATE * vellBase;
	//目标角度与实际角度的差值
	float angleErr = 0.0f;				
	//目标角度与实际角度的差值开二次根
	float angleErrSqrt = 0.0f;			
	//上一周期目标角度与实际角度的差值
	//angleErrErr = angleErr - s_angleErrOld;
	float angleErrErr = 0.0f;			
	//旋转速度
	float vellErr = 0.0f;				
	
	//求目标角度与实际角度的差值
	angleErr = CcltAngleSub(targetAngle , presentAngle);

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
	
	//进行速度赋值
	VelDecomposeCtl(vellBase,vellErr);					
	s_angleErrOld = angleErr;
}



/**
  * @name 	MvByLine
  * @brief  	直线闭环，速度为正
  * @param  	presentLine：当前姿态；
				targetLine：v目标点目标方向，等同于目标直线；
				speed:直线速度;
  * @retval 	返回值为当前点到目标点距离。单位mm
  */
float MvByLine(ActLine2 presentLine, ActLine2 targetLine, float speed)
{
	//当前点到目标直线的垂线
	ActLine2 verticalLine;											
	//中点	
	ActPoint  midpoint;											
	//控制的目标角度
	float targetAngle = 0.0f;	
	//当前点到目标点距离	
	float psntToEndDis = 0.0f;																						  
	//目标直线加90度，求出垂线方向
	verticalLine.angle = CcltAngleAdd(targetLine.angle, 90.0f);
	//把当前点赋给垂线
	verticalLine.point = presentLine.point;		
	//计算垂线与目标直	
	midpoint = CcltTwoLineIntersection2(targetLine, verticalLine);
	//计算中点横坐标	
	midpoint.x = (midpoint.x + targetLine.point.x) * 0.5f;													  
	//计算中点纵坐标
	midpoint.y = (midpoint.y + targetLine.point.y) * 0.5f;													  
	//计算当前点到中点方向
	targetAngle = CcltLineAngle(presentLine.point, midpoint);												  
	//当前点到目标点距离
	psntToEndDis = sqrtf((presentLine.point.x - targetLine.point.x) * (presentLine.point.x - targetLine.point.x)
					+ (presentLine.point.y - targetLine.point.y) * (presentLine.point.y - targetLine.point.y));
	//进行角度闭环控制
	AngleClosedLoop(presentLine.angle,targetAngle,2.0f,speed);
	
	return psntToEndDis;
}


