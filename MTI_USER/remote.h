#ifndef __RM_REMOTE_H__
#define __RM_REMOTE_H__

#include "main.h"

#define REMOTE_DATA_RX_LEN 30u
#define REMOTE_DATAFRAME_LEN 18u //数据帧长度
#define KEYNumber_W 0
#define KEYNumber_S 1
#define KEYNumber_A 2
#define KEYNumber_D 3
#define KEYNumber_Shift 4
#define KEYNumber_Ctrl 5
#define KEYNumber_Q 6
#define KEYNumber_E 7
#define KEYNumber_R 8
#define KEYNumber_F 9
#define KEYNumber_G 10
#define KEYNumber_Z 11
#define KEYNumber_X 12
#define KEYNumber_C 13
#define KEYNumber_V 14
#define KEYNumber_B 15


#define KEYNumber_Switch 16
#define KEYNumber_MouseLeft 17
//遥控数据结构体
typedef struct Remote_TypeDef
{
	int16_t ch1;	//each ch value from -660 -- +660
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;
	int16_t ch5;
	int16_t ch6;
	int16_t x;
	int16_t y;
	
	uint8_t switch_left;	//3 value
	uint8_t switch_right;
	
	int16_t wheel;
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t press_left;
		uint8_t press_right;
        
		uint8_t jumppress_left;
		uint8_t jumppress_right;
	}mouse;
	
	struct 
	{
/**********************************************************************************
   * ?ü?ìí¨μà:15   14   13   12   11   10   9   8   7   6     5     4   3   2   1
   *          V    C    X	  Z    G    F    R   E   Q  CTRL  SHIFT  D   A   S   W
************************************************************************************/
		uint16_t key_code;              //?-ê??ü?μ
		uint16_t jumpkey_code;          //ì?±?oóμ??ü?μ
	}keyBoard;
	struct
	{
		uint8_t W;
		uint8_t S;
		uint8_t A;
		uint8_t D;
		uint8_t Ctrl;
		uint8_t Shift;
		uint8_t Q;
		uint8_t E;
		uint8_t R;
		uint8_t F;
		uint8_t G;
		uint8_t Z;
		uint8_t X;
		uint8_t C;
		uint8_t V;
		uint8_t B;
		uint8_t Switch;
		uint8_t press_left;
	}
	Key;
	u8 Flag_Key[18];
}Remote_TypeDef;
//////////////////////

		typedef enum
	{
		Key_Jump_W=0,
		Key_Jump_S,
		Key_Jump_A,
		Key_Jump_D,
		Key_Jump_Shift,
		Key_Jump_Ctrl,
		Key_Jump_Q,
		Key_Jump_E,
		Key_Jump_R,
		Key_Jump_F,
		Key_Jump_G,
		Key_Jump_Z,
		Key_Jump_X,
		Key_Jump_C,
		Key_Jump_V,
		Key_Jump_B,
		
	}Key_Jump;

typedef enum
{
	RightSensing_Y, //右摇杆上下
	RightSensing_X,//右摇杆左右
	LeftSensing_Y,//左摇杆上下
	LeftSensing_X//左摇杆左右
}e_Sensing_State;

//开关状态枚举
typedef enum
{
	Left_Switch, //左开关
	Right_Switch //右开关
}e_Switch_State;

//开关值枚举
typedef enum
{
	Up = 1, //上
	Middle = 2, //中
	Down = 3//下
}e_Switch_Val;

typedef enum
{
	Mouse_X,
	Mouse_Y,
	Mouse_Left,
	Mouse_Right,
}e_Mouse_State;

typedef struct 
{
    int16_t Filter_NewVlaue;
    int16_t Filter_LastVlaue;
    int16_t Filter_Count;
}ButtonFilter_TypeDef;

typedef struct 
{
    int16_t Filter_NewVlaue_s;
    int16_t Filter_LastVlaue_s;
    int16_t Filter_Count_s;
}ButtonFilter_TypeDef_shoot;


typedef struct 
{
	e_Mouse_State Mouse; 
    int16_t Jump_NewVlaue;
    int16_t Jump_LastVlaue;
    int16_t jump_Count;
}MouseJumpFilter_TypeDef;

typedef struct 
{
	e_Switch_State Switch; 
    int16_t Jump_NewVlaue;
    int16_t Jump_LastVlaue;
    int16_t jump_Count;
}SwitchJumpFilter_TypeDef;


extern uint8_t P_uintRemote_Data_Buf[2][REMOTE_DATA_RX_LEN];
extern Remote_TypeDef P_stRemoteData_Recv;//遥控器数据保存
extern Remote_TypeDef P_stRemoteData_Recv_Last;

void fnRemote_RawDataDecode(Remote_TypeDef* st_data,uint8_t* sz_recvdata);
int16_t fnRemote_GetSensingVal(e_Sensing_State state);
uint8_t fnRemote_GetSwitchVal(e_Switch_State state);
uint8_t fnRemote_MouseCheckPush(e_Mouse_State state);
uint8_t fnRemote_GetMouseVal(e_Mouse_State state);
u8 Key_Jump_Flag_Get(Remote_TypeDef* st_data,u8 Key_Number,u8 Jump_Max);//获取跳变值
void Remote_MouseJumpVal_Dete(Remote_TypeDef* st_data,Remote_TypeDef* st_data_last,e_Mouse_State state);
void Key_Jumping(float Key, float Key_flag);

#endif


