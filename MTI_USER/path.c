#include "path.h"


void PathLineInterpolation(Pose_t *path , Pose_t startPos , Pose_t endPos ,\
						   float percent1 , float percent2 , float posture1 , float posture2)//插值
{
	Pose_t inter1 , inter2 = {0};
	path[0] = startPos;
	path[3] = endPos;
	
	inter1.point.x = startPos.point.x + percent1 * (endPos.point.x - startPos.point.x);
	inter1.point.y = startPos.point.y + percent1 * (endPos.point.y - startPos.point.y);
	inter1.direction = posture1;
	inter1.vel = MAX_PLAN_VEL;
	
	inter2.point.x = startPos.point.x + percent2 * (endPos.point.x - startPos.point.x);
	inter2.point.y = startPos.point.y + percent2 * (endPos.point.y - startPos.point.y);
	inter2.direction = posture2;
	inter2.vel = MAX_PLAN_VEL;	
	
	path[1] = inter1;
	path[2] = inter2;

}

//void PathInit(uint8_t courtId)//红蓝场取反
//{
//	if(courtId==RED_COURT)
//	{
//		for(uint8_t i=0;i<GET_FIRST_SHAGAI_PATH_NUM;i++)
//		{
//			getFirstShagaiPath[i].point.x = -(getFirstShagaiPath[i].point.x);
//			getFirstShagaiPath[i].direction = -(getFirstShagaiPath[i].direction);			
//		}
//		for(uint8_t i=0;i<GO2_TZ_PATH_NUM;i++)
//		{
//			go2TZPath[i].point.x = -(go2TZPath[i].point.x);
//			go2TZPath[i].direction = -(go2TZPath[i].direction);			
//		}
//		for(uint8_t i=0;i<THROW_FIRST_SHAGAI_PATH_NUM;i++)
//		{
//			throwFirstShagaiPath[i].point.x = -(throwFirstShagaiPath[i].point.x);
//			throwFirstShagaiPath[i].direction = -(throwFirstShagaiPath[i].direction);			
//		}
//		for(uint8_t i=0;i<GET_2ND_SHAGAI_PATH_NUM;i++)
//		{
//			get2ndShagaiPath[i].point.x = -(get2ndShagaiPath[i].point.x);
//			get2ndShagaiPath[i].direction = -(get2ndShagaiPath[i].direction);			
//		}
//		for(uint8_t i=0;i<THROW_2ND_SHAGAI_PATH_NUM;i++)
//		{
//			throw2ndShagaiPath[i].point.x = -(throw2ndShagaiPath[i].point.x);
//			throw2ndShagaiPath[i].direction = -(throw2ndShagaiPath[i].direction);			
//		}
//		for(uint8_t i=0;i<GET_3RD_SHAGAI_PATH_NUM;i++)
//		{
//			get3rdShagaiPath[i].point.x = -(get3rdShagaiPath[i].point.x);
//			get3rdShagaiPath[i].direction = -(get3rdShagaiPath[i].direction);			
//		}
//		for(uint8_t i=0;i<THROW_3RD_SHAGAI_PATH_NUM;i++)
//		{
//			throw3rdShagaiPath[i].point.x = -(throw3rdShagaiPath[i].point.x);
//			throw3rdShagaiPath[i].direction = -(throw3rdShagaiPath[i].direction);			
//		}		
//	}
//}

Pose_t GetPosPresent()
{
	Pose_t pos;
	pos.point.x = GetX();
	pos.point.y = GetY();
	pos.direction   = GetAngle();
//	pos.vel = 0.0f;
	return pos;
}

//第一段轨迹
Pose_t First_Task_Path[FIRST_TASK_PATH_NUM]=
{
{0.0f,	0.0f,	0.0f,	0.0f},
{	-259.51f	,	295.43f	,	0.0f	,	MAX_PLAN_VEL	},
{	-519.02f	,	590.87f	,	0.0f	,	MAX_PLAN_VEL	},
{	-778.53f	,	886.30f	,	0.0f	,	MAX_PLAN_VEL	},
{	-863.98f	,	969.71f	,	0.0f	,	MAX_PLAN_VEL	},
{	-961.19f	,	1039.06f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1067.86f	,	1092.73f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1181.49f	,	1129.45f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1299.40f	,	1148.37f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1418.81f	,	1149.02f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1536.92f	,	1131.40f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1650.94f	,	1095.93f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1758.19f	,	1043.43f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1856.16f	,	975.15f	,	0.0f	,	MAX_PLAN_VEL	},
{	-1942.52f	,	892.68f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2015.26f	,	797.98f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2072.66f	,	693.26f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2113.36f	,	581.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2164.73f	,	446.12f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2240.11f	,	323.05f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2336.93f	,	216.01f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2451.83f	,	128.68f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2580.89f	,	64.06f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2719.65f	,	24.38f	,	0.0f	,	MAX_PLAN_VEL	},
{	-2863.36f	,	11.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3007.07f	,	24.38f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3145.83f	,	64.06f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3274.89f	,	128.68f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3389.80f	,	216.01f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3486.61f	,	323.05f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3561.99f	,	446.12f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3613.36f	,	581.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3655.97f	,	698.82f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3715.94f	,	808.82f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3791.86f	,	908.47f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3882.00f	,	995.48f	,	0.0f	,	MAX_PLAN_VEL	},
{	-3984.28f	,	1067.84f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4096.33f	,	1123.87f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4215.58f	,	1162.30f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4339.27f	,	1182.22f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4464.55f	,	1183.18f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4588.53f	,	1165.17f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4708.35f	,	1128.58f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4821.25f	,	1074.28f	,	0.0f	,	MAX_PLAN_VEL	},
{	-4924.63f	,	1003.51f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5016.10f	,	917.89f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5101.07f	,	835.64f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5195.16f	,	763.99f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5297.05f	,	703.95f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5405.32f	,	656.35f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5518.44f	,	621.88f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5634.85f	,	600.99f	,	0.0f	,	MAX_PLAN_VEL	},
{	-5752.90f	,	594.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-6317.43f	,	594.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-6881.96f	,	594.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7446.49f	,	594.00f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7569.96f	,	603.23f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7690.68f	,	630.73f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7805.97f	,	675.88f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7913.26f	,	737.68f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8010.16f	,	814.76f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8094.52f	,	905.39f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8164.46f	,	1007.56f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8218.42f	,	1118.99f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8255.20f	,	1237.22f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8273.99f	,	1359.60f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8274.36f	,	1483.41f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8256.31f	,	1605.91f	,	0.0f	,	MAX_PLAN_VEL	},
{	-8092.04f	,	2337.21f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7927.77f	,	3068.52f	,	0.0f	,	MAX_PLAN_VEL	},
{	-7763.50f	,	3799.83f	,	0.0f	,	(0.4f*MAX_PLAN_VEL)	},
{	-7742.72f	,	3905.56f	,	0.0f	,	(0.4f*MAX_PLAN_VEL)	},
{	-7727.65f	,	4012.38f	,	0.0f	,	(0.4f*MAX_PLAN_VEL)	},
{	-7718.36f	,	4120.00f	,	0.0f	,	(0.4f*MAX_PLAN_VEL)	},
{	-7714.90f	,	4228.10f	,	0.0f	,	(0.4f*MAX_PLAN_VEL)	},
{	-7712.93f	,	4618.73f	,	0.0f	,	(0.35f*MAX_PLAN_VEL)	},
{	-7710.97f	,	5009.36f	,	0.0f	,	(0.35f*MAX_PLAN_VEL)	},
{	-7709.00f	,	5400.00f	,	0.0f	,	0.0f	}
};


