#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "stdint.h"

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"  
#include "croutine.h"


#include "stm32f4xx_it.h"
//SYSTEM
#include "delay.h"
#include "sys.h"

//BSP 
#include "can.h"
#include "gpio.h"
#include "nvic.h"
#include "timer.h"
#include "uart.h"
#include "dma.h"

//Hardware
#include "M3508.h"
#include "remote.h"
#include "hi219m.h"
#include "pid.h"
#include "PointRabbit.h"

//extern
#include "imu_data_decode.h"
#include "packet.h"
#include "user_task.h"

//youwork
#include "ChassisCtrl.h"


//#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//¶ÁÈ¡°´¼ü0
#endif

