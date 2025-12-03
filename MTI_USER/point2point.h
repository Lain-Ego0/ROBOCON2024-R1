#ifndef _POINT2POINT_H
#define _POINT2POINT_H


#ifdef  __POINT2POINT_GLOBALS
#define __POINT2POINT_GLOBALS
#else
#define __POINT2POINT_EXT extern
#endif
//角度制转换为弧度制系数
#define CHANGE_TO_RADIAN    0.01745329251994f   
//弧度制转换为角度制系数
#define CHANGE_TO_ANGLE     57.29577951308232f				
//圆周率
#define PI					3.14159265358979f

typedef struct
{
	float x;
	float y;
}Point_t;

//点斜式结构体 ，斜率用角度制的角度代替
typedef struct
{
	Point_t point;
	float direction;//角度制 为姿态角度
	float vel;//速度
}Pose_t;

typedef enum
{
		Start_task,
		First_task,
	  Second_task,
//	  Third_task,
//	  Fourth_task,
}walktask_t;
//全局变量结构体
typedef struct
	{
	walktask_t walktask;
	
	}Robot_t;
	
__POINT2POINT_EXT   Robot_t Robot;
	
float MvByLine(Pose_t presentLine, Pose_t targetLine, float speed);
void VelCal(Pose_t *path , Pose_t startPos , Pose_t lastPos);
void Walk(void);


#endif
