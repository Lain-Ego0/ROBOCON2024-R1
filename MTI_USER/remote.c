#include "remote.h"

#define MOUSE_CLEARSHACK_TIME 600 //按键消抖时长

uint8_t P_uintRemote_Data_Buf[2][REMOTE_DATA_RX_LEN];//遥控器缓存数组
Remote_TypeDef P_stRemoteData_Recv;//遥控器数据保存
Remote_TypeDef P_stRemoteData_Recv_Last;//上一次遥控器数据
uint16_t Key_temp;
//原始数据解析
void fnRemote_RawDataDecode(Remote_TypeDef* st_data,uint8_t* sz_recvdata)
{
	st_data->ch1 = ((sz_recvdata[0] | sz_recvdata[1]<<8) & 0x7ff) - 1024;
	st_data->ch2 = ((sz_recvdata[1]>>3 | sz_recvdata[2]<<5) & 0x7ff) - 1024;
	st_data->ch3 = ((sz_recvdata[2]>>6 | sz_recvdata[3]<<2 | sz_recvdata[4]<<10) & 0x7ff) - 1024;
	st_data->ch4 = ((sz_recvdata[4]>>1 | sz_recvdata[5]<<7) & 0x7ff) - 1024;
	
	st_data->switch_left = ((sz_recvdata[5] >> 4) & 0x000C)>>2;
	st_data->switch_right = ((sz_recvdata[5] >> 4) & 0x0003);
	
	st_data->mouse.x = sz_recvdata[6] | (sz_recvdata[7]<<8);
	st_data->mouse.y = sz_recvdata[8] | (sz_recvdata[9]<<8);
	st_data->mouse.z = sz_recvdata[10] | (sz_recvdata[11]<<8);
	
	st_data->mouse.press_left = sz_recvdata[12];
	st_data->mouse.press_right = sz_recvdata[13];
	
	st_data->keyBoard.key_code = sz_recvdata[14] | sz_recvdata[15] << 8;
	st_data->wheel = ((sz_recvdata[16] | sz_recvdata[17]<<8)& 0x7ff) - 1024;
	st_data->ch5=sz_recvdata[16];
	st_data->ch6=sz_recvdata[17];
		//遥控器数据处理
	Key_temp=	st_data->keyBoard.key_code;

	st_data->Key.W 		 =  Key_temp&0x0001;
	st_data->Key.S 		 = (Key_temp&0x0002)>>1;
	st_data->Key.A 		 = (Key_temp&0x0004)>>2;
	st_data->Key.D 		 = (Key_temp&0x0008)>>3;
	st_data->Key.Shift = (Key_temp&0x0010)>>4;
	st_data->Key.Ctrl  = (Key_temp&0x0020)>>5;
	st_data->Key.Q 		 = (Key_temp&0x0040)>>6;
	st_data->Key.E 		 = (Key_temp&0x0080)>>7;
	st_data->Key.R		 = (Key_temp&0x0100)>>8;
	st_data->Key.F 		 = (Key_temp&0x0200)>>9;
	st_data->Key.G 		 = (Key_temp&0x0400)>>10;
	st_data->Key.Z 		 = (Key_temp&0x0800)>>11;
	st_data->Key.X 		 = (Key_temp&0x1000)>>12;
	st_data->Key.C 		 = (Key_temp&0x2000)>>13;
	st_data->Key.V 		 = (Key_temp&0x4000)>>14;
	st_data->Key.B 		 = (Key_temp&0x8000)>>15;
	st_data->Key.Switch  = !GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
	st_data->Key.press_left = sz_recvdata[12];
}

////遥控器原始数据处理 //滤波消抖动等
//void fnRemote_HandleData(Remote_TypeDef* st_data)
//{
//	//按键跳变检测
//}

//遥控器获取摇杆值
int16_t fnRemote_GetSensingVal(e_Sensing_State state)
{
	switch(state)
	{
		case RightSensing_X:
			return P_stRemoteData_Recv.ch1;
		
		case RightSensing_Y:
			return P_stRemoteData_Recv.ch2;
		
		case LeftSensing_X:
			return P_stRemoteData_Recv.ch3;
		
		case LeftSensing_Y:
			return P_stRemoteData_Recv.ch4;
		
		default:
			return -1;
	}
}
//遥控器获取上部开关值
uint8_t fnRemote_GetSwitchVal(e_Switch_State state)
{
	if(state == Left_Switch)
	{
		return P_stRemoteData_Recv.switch_left;
	}
	else if(state == Right_Switch)
	{
		return P_stRemoteData_Recv.switch_right;
	}
	else 
	{
		return 0;
	}
}
//获取鼠标值
uint8_t fnRemote_GetMouseVal(e_Mouse_State state)
{
	switch(state)
	{
		case Mouse_X:
		{
			return P_stRemoteData_Recv.mouse.x;
		}
		case Mouse_Y:
		{
			return P_stRemoteData_Recv.mouse.y;
		}
		
		default:return 0;
	}
}

//检测鼠标是否被按下
uint8_t fnRemote_MouseCheckPush(e_Mouse_State state)
{
	switch(state)
	{
		case Mouse_Left:
		{
			return P_stRemoteData_Recv.mouse.press_left;
		}
		case Mouse_Right:
		{
			return P_stRemoteData_Recv.mouse.press_right;
		}
		
		default:return 0;
	}
}

//检测按键是否被按下，

//开关跳变检测
//鼠标跳变检测
//键盘值跳变检测
void Remote_MouseJumpVal_Dete(Remote_TypeDef* st_data,Remote_TypeDef* st_data_last,e_Mouse_State state)
{
	fnRemote_MouseCheckPush(state);
	static uint16_t time_count[2];
	
	if(time_count[0]++ >= MOUSE_CLEARSHACK_TIME) //左鼠标跳变检测
	{
		switch(state)
	{
		case Mouse_Left:
		{
		if((st_data->mouse.press_left) && (!(st_data_last->mouse.press_left)))
        {
            st_data->mouse.jumppress_left = 1;
            time_count[0] = 0;
        }
        else
        {
            st_data->mouse.jumppress_left = 0;
        }
	 }
		case Mouse_Right:
		{
			if((st_data->mouse.press_right) && (!(st_data_last->mouse.press_right)))
        {
            st_data->mouse.jumppress_right = 1;
            time_count[0] = 0;
        }
        else
        {
            st_data->mouse.jumppress_right = 0;
        }
		}
				default:
				{
				};break;
  }
 }
}

//开关跳变

//按键滤波
//按键滤波
uint8_t Key_Fliter(float vaule,float last_last_vaule)
{
	if(vaule==1 && last_last_vaule==1)
	{
			return 1;
	}
	else
	{
			return 0;
	
	}	
}

//W S A D Shift Ctrl Q E R F
//0 1 2 3 4     5    6 7 8 9
//G 10 Z 11 X 12 C 13 V 14 B 15

u8 key_jump_flag(u8 *Key_Check,u8 Key_Vaule_Fliter)//作用是判断是否执行
{
	u8 key_return;
	if(*Key_Check==1&&Key_Vaule_Fliter==0)
		*Key_Check=0;
	if(*Key_Check==0&&Key_Vaule_Fliter==1)
	{
		*Key_Check=1;
		Key_Vaule_Fliter=1;
		key_return=1;
	}
	else
		key_return=0;

	return key_return;
}

u8 Key_Jump_Flag_Get(Remote_TypeDef* st_data,u8 Key_Number,u8 Jump_Max)//获取跳变值
{
	static u8 Key_Check[18];//跳变检验值,要多少定义多少
	uint8_t Key[18]={st_data->Key.W,st_data->Key.S,st_data->Key.A,st_data->Key.D,st_data->Key.Shift,
	st_data->Key.Ctrl,st_data->Key.Q,st_data->Key.E,st_data->Key.R,st_data->Key.F,st_data->Key.G,
	st_data->Key.Z,st_data->Key.X,st_data->Key.C,st_data->Key.V,st_data->Key.B,st_data->Key.Switch,st_data->Key.press_left};
	
	static u8 *Key_Flag_indicator;
	static u8 *Key_Fliter_indicator;
	if(Key_Number>17)Key_Number=17;
	Key_Flag_indicator=st_data->Flag_Key+Key_Number;
	Key_Fliter_indicator=Key+Key_Number;
	if(Jump_Max==0)return key_jump_flag(&Key_Check[Key_Number],*Key_Fliter_indicator);
	*Key_Flag_indicator+=key_jump_flag(&Key_Check[Key_Number],*Key_Fliter_indicator);
	if(*Key_Flag_indicator>Jump_Max) *Key_Flag_indicator=0;
	return *Key_Flag_indicator;
}


