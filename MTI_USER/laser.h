#ifndef _LASER_H__
#define _LASER_H__

//接收激光数据
#define GET_LASER_VALUE_NUM      2
#define GET_LASER_DATA_NUM       8

typedef union{
	uint8_t data[GET_LASER_DATA_NUM];//4字节
	float  value[GET_LASER_VALUE_NUM];//1浮点
}LaserSend_t;

//激光值
typedef struct
{
	float laserOne;
	float laserTwo;
	float laserThr;
	float laserFor;
	float laserFiv;
	float laserSix;
	float laserSev;
	float laserEig;
}laserValue_t;

void floatTobyte(void);

#endif
