/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.h 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include "main.h"	 
#include "PointRabbit.h"
void UART7_IRQHandler(void);
#define BUFFER_SIZE 10
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern CanRxMsg CAN1DataRecv; //CAN1数据接收结构体
extern float TF_distance; 
void SysTick_Handler(void);
extern int wifi_remoto[BUFFER_SIZE];

	 typedef struct Positioning_system_TypeDef
{
float X_laps_decimal;
float X_distance_mm;
float Y_laps_decimal;
float Y_distance_mm;

	
}Positioning_system_TypeDef;

extern Positioning_system_TypeDef Positioning;

	 typedef struct P_stHi219msystem
{
float Yaw;
float Pitch;
float Roll;
float Yaw_Gyo;
float Pitch_Gyo;
float Roll_Gyo;
float Last_Yaw;
float Last_Pitch;
float Last_Roll;
float Continuous_Pitch;
float Continuous_Roll;
float Continuous_Yaw;	
	
}P_stHi219msystem;

extern P_stHi219msystem P_stHi219m2;
extern float Remote_control_data[16];
//typedef struct Position_system
//{
//float Position_x;
//float Position_y;
//float ZangleRbbit;
//float XangleRbbit;
//float YangleRbbit;
//float W_ZRbbit;
//}Position_system;

//extern Position_system Rabbit;

//void NMI_Handler(void);
//void HardFault_Handler(void);
//void MemManage_Handler(void);
//void BusFault_Handler(void);
//void UsageFault_Handler(void);
//void SVC_Handler(void);
//void DebugMon_Handler(void);
//void PendSV_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
