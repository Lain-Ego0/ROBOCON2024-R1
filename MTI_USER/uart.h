#ifndef _USART_INIT_H__
#define _USART_INIT_H__

#include "stm32f4xx_usart.h"

#ifdef  __USART_INIT_GLOBALS
#define __USART_INIT_GLOBALS
#else
#define __USART_INIT_EXT extern
#endif


/*接收定位系统的float数据*/
#define GET_PPS_VALUE_NUM      6
/*接收定位系统的uint8_t数据*/ /* 6 * 4byte = 24*/
#define GET_PPS_DATA_NUM       24


typedef union{
	uint8_t data[GET_PPS_DATA_NUM];
	float  value[GET_PPS_VALUE_NUM];
}PosSend_t;

__USART_INIT_EXT float pos_x; 
__USART_INIT_EXT float pos_x; 
__USART_INIT_EXT float pos_y; 
__USART_INIT_EXT float zangle; 
__USART_INIT_EXT float xangle; 
__USART_INIT_EXT float yangle; 
__USART_INIT_EXT float w_z;


void BSP_USART_Init(void);
void Float_to_Byte(float *data);
void USART_OUT(USART_TypeDef *USARTx, const uint8_t *Data, ...);
char *itoa(int value, char *string, int radix);
float GetX(void);
float GetY(void);
float GetAngle(void);
float GetW_z(void);

#endif

