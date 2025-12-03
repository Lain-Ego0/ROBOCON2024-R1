#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include "main.h"

extern SemaphoreHandle_t P_shH219DataDecode_Binary;
void Task_Main(void *Parameters);

void Task_TimeCount(void *Parameters);

void Task_DataGet(void *Parameters);
void Task_Hi219mDataDecode(void *Parameters);
void Task_ChassisCtrl(void *Parameters);

void Put_Ring_Ctrl(void *Parameters);
void Overturn_Ctrl(void *Parameters);


extern float votion,lastvotion;
extern float votion_phone,votion_remoto,votion_key;
#endif
