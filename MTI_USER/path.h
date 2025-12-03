#ifndef _Path_H__
#define _Path_H__

#ifdef  __Path_GLOBALS
#define __Path_GLOBALS
#else
#define __Path_EXT extern
#endif

#include "math.h"
#include "stdint.h"
#include "uart.h"
#include "point2point.h"

//第一段任务路径
#define MAX_PLAN_VEL (1500)

#define FIRST_TASK_PATH_NUM (78)

__Path_EXT Pose_t First_Task_Path[FIRST_TASK_PATH_NUM];


Pose_t GetPosPresent(void);

#endif
