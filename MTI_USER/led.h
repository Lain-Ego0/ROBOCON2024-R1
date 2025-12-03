#ifndef __LED_H__
#define __LED_H__

void BSP_LED_Init(void);

#define GREEN_LED_ON()      GPIO_ResetBits(GPIOF, GPIO_Pin_14)	//ÂÌµÆÁÁ
#define GREEN_LED_OFF()     GPIO_SetBits(GPIOF, GPIO_Pin_14)	//ÂÌµÆÃð
#define GREEN_LED_TOGGLE()      GPIO_ToggleBits(GPIOF, GPIO_Pin_14)	//ÂÌµÆÇÐ»»×´Ì¬

#define RED_LED_ON()            GPIO_ResetBits(GPIOE, GPIO_Pin_11)	//ºìµÆÁÁ
#define RED_LED_OFF()           GPIO_SetBits(GPIOE, GPIO_Pin_11)		//ºìµÆÃð
#define RED_LED_TOGGLE()        GPIO_ToggleBits(GPIOE, GPIO_Pin_11)	//ºìµÆÇÐ»»×´Ì¬

#define BOTH_LED_TOGGLE()\
GPIO_ToggleBits(GPIOF, GPIO_Pin_14);\
GPIO_ToggleBits(GPIOE, GPIO_Pin_7)			//ºìÂÌÒ»ÆðÇÐ»»×ªÌ¬//

#endif
