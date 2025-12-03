#include "hi219m.h"

uint8_t P_uintH219MDataBuffer[HI219M_RX_BUF_LEN];				//H219数据缓存数组 
uint16_t P_uintH219BuffLength; //数据长度

Hi219m_TypeDef P_stHi219m;


void Hi219m_ParaInit(void)
{
	imu_data_decode_init();
}

//陀螺仪角度处理
void fnHi219m_DataDecode(Hi219m_TypeDef* st_data)
{
	float Eular[3];
	int16_t Gyo[3];
  //int16_t Acc[3];
	
	
	get_raw_gyo(Gyo);
	get_eular(Eular);
	
	st_data->Last_Yaw = st_data->Yaw;
	
	st_data->Roll = Eular[1];
	st_data->Yaw = 180 + Eular[2];
	st_data->Pitch = 360 - Eular[0];
	
	st_data->Yaw_Gyo = -Gyo[2]/10.f;
	st_data->Pitch_Gyo = Gyo[1]/10.f;
	st_data->Roll_Gyo = -Gyo[0]/10.f;

	
	if(st_data->Yaw - st_data->Last_Yaw >= 330)
	{
		st_data->Round --;
	}
	else if(st_data->Yaw - st_data->Last_Yaw <= -330)
	{
		st_data->Round ++;
	}
	
	st_data->Continuous_Yaw = st_data->Yaw + st_data->Round *360;
	
}

