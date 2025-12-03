#include "stm32f4xx_it.h"
#include "main.h"
#include "task.h"
  Positioning_system_TypeDef Positioning;
  P_stHi219msystem P_stHi219m2;
CanRxMsg CAN1DataRecv; //CAN1数据接收结构体
CanRxMsg CAN2DataRecv; //CAN2数据接收结构体

//////////////////////////////////////

//////////////请注释清楚，每个都要！！！！

/////////////////////////////////////can口

/*************************************************************************
*  函数名称：CAN1_RX0_IRQHandler
*  功能说明：CAN1接收中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：电机CAN传送数据解析
*************************************************************************/

void CAN1_RX0_IRQHandler(void)/////////////////////////////////////can口数据读取，将数据存入相应结构体
{   
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN1,&CAN1DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 	//清除标志位
	}
//	
//	OS_CRITICAL_EXIT();	//退出临界区
}

/*************************************************************************
*  函数名称：CAN1_TX_IRQHandler
*  功能说明：CAN1发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/

void CAN1_TX_IRQHandler(void) //CAN TX//////////////////////////////发送中断(未写入)
{
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
		
//	OS_CRITICAL_EXIT();	//退出临界区
}

/*************************************************************************
*  函数名称：CAN2_RX0_IRQHandler
*  功能说明：CAN2接收中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：电机CAN传送数据解析
*************************************************************************/

void CAN2_RX0_IRQHandler(void)/////////////////////////////////////can口数据读取，将数据存入相应结构体
{   
//	CanRxMsg P_stCAN2DataRecv;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &CAN2DataRecv);	//接收数据
		
		fnMotor_CanRecvDataDecode(CAN2,&CAN2DataRecv);	//电机处理数据
		
		CAN_ClearITPendingBit(CAN2, CAN_IT_FF0);	//清除中断标志位
		CAN_ClearFlag(CAN2, CAN_FLAG_FF0); 	//清除标志位
		 
	}
}

/*************************************************************************
*  函数名称：CAN2_TX_IRQHandler
*  功能说明：CAN2发送中断服务函数
*  参数说明：无
*  函数返回：无	 
*  备    注：无
*************************************************************************/

void CAN2_TX_IRQHandler(void) //CAN TX//////////////////////////////发送中断(未写入)
{
    if(CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
    }
}

//////////////////////////////////////////////////////////////////////////串口


void USART1_IRQHandler(void)//////////////////////////////////////////////串口接收中断运用于DBUS接收器(遥控器),使用了DMA未访问cpu直接写入内存;
{
//	CPU_SR_ALLOC();
//	OS_CRITICAL_ENTER();	//进入临界区
	
	static uint32_t rx_len = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag 
		(void)USART1->SR;
		(void)USART1->DR;
		
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
		{
			DMA_Cmd(DMA2_Stream2, DISABLE);
			rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
			DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;     //relocate the dma memory pointer to the beginning position
			DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 1
			DMA_Cmd(DMA2_Stream2, ENABLE);
			if(rx_len == REMOTE_DATAFRAME_LEN)
			{
				fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[0]);
			}
		}
		//Target is Memory1
		else 
		{
			DMA_Cmd(DMA2_Stream2, DISABLE);
			rx_len = REMOTE_DATA_RX_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
			DMA2_Stream2->NDTR = (uint16_t)REMOTE_DATA_RX_LEN;      //relocate the dma memory pointer to the beginning position
			DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
			DMA_Cmd(DMA2_Stream2, ENABLE);
			if(rx_len == REMOTE_DATAFRAME_LEN)
			{
				fnRemote_RawDataDecode(&P_stRemoteData_Recv,P_uintRemote_Data_Buf[1]);
			}
		}
	}    
//	OS_CRITICAL_EXIT();	//退出临界区
}
///////////////////////////////////////////////////////////////////////////wifi_remoto UART7 TX:PF7  RX:PF6




//#define BUFFER_SIZE 10
//int wifi_remoto[BUFFER_SIZE];

//const uint8_t PACKET_START = 0xAB; // 数据包起始标志符

///**
// * @brief 串口7中断服务程序
// */
//void UART7_IRQHandler(void)
//{
//    static uint8_t state = 0; // 状态机的状态
//    static uint8_t data_index = 0;
//    static uint8_t data_buffer[BUFFER_SIZE * sizeof(int)];

//    if (USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
//    {
//        uint8_t received_data = USART_ReceiveData(UART7);

//        switch (state)
//        {
//            case 0: // 等待数据包起始标志符
//                if (received_data == PACKET_START)
//                {
//                    state = 1;
//                    data_index = 0;
//                }
//                break;

//            case 1: // 接收数据
//                if (data_index < BUFFER_SIZE * sizeof(int))
//                {
//                    data_buffer[data_index] = received_data;
//                    data_index++;
//                }

//                if (data_index == BUFFER_SIZE * sizeof(int))
//                {
//                    // 接收完成
//                    int *states_ptr = (int*)data_buffer;
//                    for (int i = 0; i < BUFFER_SIZE; i++)
//                    {
//                        wifi_remoto[i] = *states_ptr;
//                        states_ptr++;
//                    }

//                    // 重置状态机和缓冲区
//                    state = 0;
//                    data_index = 0;
//                    memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));
//                }
//                break;

//            default:
//                state = 0;
//                data_index = 0;
//                memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));
//                break;
//        }
//    }

//    if (USART_GetITStatus(UART7, USART_IT_ORE) != RESET ||
//        USART_GetITStatus(UART7, USART_IT_FE) != RESET ||
//        USART_GetITStatus(UART7, USART_IT_NE) != RESET ||
//        USART_GetITStatus(UART7, USART_IT_PE) != RESET)
//    {
//        // 数据接收错误，重置状态机和缓冲区
//        state = 0;
//        data_index = 0;
//        memset(data_buffer, 0, BUFFER_SIZE * sizeof(int));
//        USART_ClearITPendingBit(UART7, USART_IT_ORE | USART_IT_FE | USART_IT_NE | USART_IT_PE);
//    }
//}


/////////////////////////////////////////////////////////////////////////陀螺仪hi219m UART8 TX:PE1  RX:PE0
void UART8_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;
	if(USART_GetITStatus(UART8,USART_IT_IDLE) != RESET)//防止非空闲中断时进入
	{
		UART8->DR;
		UART8->SR;
		DMA_Cmd(DMA1_Stream6, DISABLE); 
		
		P_uintH219BuffLength = HI219M_RX_BUF_LEN-(DMA1_Stream6->NDTR);
        //重启DMA
		DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6 | DMA_FLAG_HTIF6);
		while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);
		DMA_SetCurrDataCounter(DMA1_Stream6, HI219M_RX_BUF_LEN);
		DMA_Cmd(DMA1_Stream6, ENABLE);
		
		if(P_shH219DataDecode_Binary!=NULL)//若未创建切换任务会死机
		{
			xSemaphoreGiveFromISR(P_shH219DataDecode_Binary,&xHigherPriorityTaskWoken);	//释放二值信号量
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}		}
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//从这里到下面为激光雷达计算函数（未使用DMA）
//函数并为全部使用全局变量如果需要请去h文件设置
#define TF_HEADER 0x59
float ch; 
float TF_distance = 0;             // TF_测距数据
float TF_strength = 0;             // TF_信号强度
float TF_temperature = 0;          // TF_温度
int TF_checksum = 0;             // TF_自检
float TF_flage = 0x00;              // TF_测距状态
float TF_uart_data;
int TF_dat[9];
int TF_num = 0;
int ass=256;


void USART6_IRQHandler(void) 
{

	if(USART_GetITStatus(USART6, USART_IT_RXNE)==SET) 
{ 
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);    
    ch=USART_ReceiveData(USART6);//仅需将USART_ReceiveData(USART6)换成其他接收函数就行
		TF_dat[TF_num] = ch;
    if(TF_num)
    {
        if(TF_dat[1] != TF_HEADER) TF_num = 0;//2、若第二个数不是 0x59，则TF_num清零，下一次重新检测第一个数
            else  TF_num++;                   //3、第一和第二个数均满足要求，开始将获得的数，逐位赋给TF_dat[2~8]
    }
    if(TF_dat[0] != TF_HEADER) TF_num = 0;
    else if(TF_num==0) TF_num = 1;           //1、若第一个数满足要求0x59，则下一次接收并检测第二个函数

    if (TF_num==9)//获得完9位数后
    {
        TF_num = 0;
        TF_checksum = TF_dat[0]+TF_dat[1]+TF_dat[2]+TF_dat[3]+TF_dat[4]+
                        TF_dat[5]+TF_dat[6]+TF_dat[7];

        if((TF_checksum % ass) == TF_dat[8])//TF_dat[8]是自检位，满足要求后根据公式计算距离等
            {
            TF_distance = TF_dat[3]<<8 | TF_dat[2];
            TF_strength = TF_dat[5]<<8 | TF_dat[4];
            TF_temperature  = TF_dat[7]<<8 | TF_dat[6];
            TF_flage = 1;
            }

    }
    

}
}
/////////////////////////////////////////////////////////////////////////值Positioning_system UART7 TX:PF7  RX:PF6

#define UART_BUFFER_SIZE 256
#define START_BYTE1 0x5A
#define START_BYTE2 0xA5
#define END_BYTE1 0xA6
#define END_BYTE2 0x6A
uint8_t Duart_rx_buffer[UART_BUFFER_SIZE]; // 接收缓冲区

union DFloatBytes {
    float floatValue;
    uint8_t bytes[sizeof(float)];
};
;
float Positioning_system[16]; // 接收12个浮点数数据
extern float Positioning_system[16];
uint32_t Ddata_index = 0;
_Bool Dis_receiving = 0;
_Bool Dis_start_byte1_received = 0;
_Bool Dover_receiving = 0;

void Dprocess_data(void) {
    // 在这里进行数据处理，将接收到的数据赋值Positioning_system组
    union DFloatBytes DfloatData;

    for (int i = 0; i < 16; i++) {
        // 将4个字节转换成float类型的数据
        for (int j = 0; j < sizeof(float); j++) {
            DfloatData.bytes[j] = Duart_rx_buffer[i * sizeof(float) + j];
        }
         Positioning_system[i] = DfloatData.floatValue;
				
				
				
	       Positioning.X_laps_decimal=Positioning_system[0];
				 Positioning.X_distance_mm=Positioning_system[1];
				 Positioning.Y_laps_decimal=Positioning_system[2];
				 Positioning.Y_distance_mm=Positioning_system[3];
				 P_stHi219m2.Yaw=Positioning_system[4];
				 P_stHi219m2.Pitch=Positioning_system[5];
				 P_stHi219m2.Roll=Positioning_system[6];
				 P_stHi219m2.Yaw_Gyo=Positioning_system[7];
				 P_stHi219m2.Pitch_Gyo=Positioning_system[8];
				 P_stHi219m2.Roll_Gyo=Positioning_system[9];
				 P_stHi219m2.Last_Yaw=Positioning_system[10];
				 P_stHi219m2.Last_Pitch=Positioning_system[11];
				 P_stHi219m2.Last_Roll=Positioning_system[12];
			   P_stHi219m2.Continuous_Pitch=Positioning_system[13];
				 P_stHi219m2.Continuous_Roll=Positioning_system[14];
 				 P_stHi219m2.Continuous_Yaw=Positioning_system[15];
    }
}






/**
 * @brief 串口7中断服务程序
 */
void UART7_IRQHandler(void)
{
    if (USART_GetITStatus(UART7, USART_IT_RXNE) != RESET) {
        uint8_t temp_data = USART_ReceiveData(UART7);
        USART_ClearITPendingBit(UART7, USART_IT_RXNE);

        if (Dis_receiving == 1) {
            if (Ddata_index < UART_BUFFER_SIZE) {
                Duart_rx_buffer[Ddata_index++] = temp_data;
            }
        }

        if (temp_data == START_BYTE1) {
            // 如果还未接收到第一个起始字节，则等待接收
            Dis_start_byte1_received = 1;
        } else if (temp_data == START_BYTE2 && Dis_start_byte1_received == 1) {
            Dis_receiving = 1;
            Ddata_index = 0;
        } else if (temp_data == END_BYTE1) {
            Dover_receiving = 1;
        } else if (temp_data == END_BYTE2 && Dover_receiving == 1) {
            // 接收到了完整的数据帧，处理数据
            Dprocess_data();
            
            Dis_receiving = 0;
            Dis_start_byte1_received = 0;
            Dover_receiving = 0;
        }
    }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/////////////////////////////////////////////////////////////////////////定位系统 UART8 TX:PE1  RX:PE0
///////////////////////////////////////////目前定位系统改到uart8，记得去pointrabbit修改发送函数
///**
// * @file 数据解析代码示例.c
// * @brief 定位系统数据解析代码示例
// * @author 技术售后-LiuDun
// * @version 1.1
// * @date 2022-09-22
// *
// * @copyright  Copyright  (c)  2022  Action
// *
// */
///**
// * @brief 解析结果变量，如需跨文件调用，需要外部声明
// */
//Position_system Rabbit;
//float pos_x=0;
//float pos_y=0;
//float zangle=0;
//float xangle=0;
//float yangle=0;
//float w_z=0;

///**
// * @brief 数据解析函数  如更换MCU平台或更换软件库，只需将串口接收到的值传入该函数即可解析
// * @param  rec 串口接收到的字节数据
// */
//void Data_Analyse(uint8_t rec)
//{
//	static uint8_t ch;
//	static union
//	{
//		uint8_t date[24];
//		float ActVal[6];
//	}posture;
//	static uint8_t count=0;
//	static uint8_t i=0;

//	ch=rec;
//	switch(count)
//	{
//		case 0:
//			if(ch==0x0d)
//				count++;
//			else
//				count=0;
//			break;
//		case 1:
//			if(ch==0x0a)
//			{
//				i=0;
//				count++;
//			}
//			else if(ch==0x0d);
//			else
//				count=0;
//			break;
//		case 2:
//			posture.date[i]=ch;
//			i++;
//			if(i>=24)
//			{
//				i=0;
//				count++;
//			}
//			break;
//		case 3:
//			if(ch==0x0a)
//				count++;
//			else
//				count=0;
//			break;
//		case 4:
//			if(ch==0x0d)
//			{
//				zangle=posture.ActVal[0];
//				xangle=posture.ActVal[1];
//				yangle=posture.ActVal[2];
//				pos_x=posture.ActVal[3];
//				pos_y=posture.ActVal[4];
//				w_z=posture.ActVal[5];
//			}
//			count=0;
//			break;
//		default:
//			count=0;
//		break;
//	}
//}

//void UART8_IRQHandler(void)
//{
//u8 r;
//if(USART_GetITStatus(UART8, USART_IT_RXNE) != RESET)
//{
//	r =USART_ReceiveData(UART8);
//	Data_Analyse(r);
//	Rabbit.Position_x=pos_x;
//	Rabbit.Position_y=pos_y;
//	Rabbit.ZangleRbbit= zangle;
//	Rabbit.XangleRbbit=xangle;
//	Rabbit.YangleRbbit= yangle;
//	Rabbit.W_ZRbbit= w_z;

//}
//}


/////////////////////////////////////////////////////////////////////////Remote_control数据接收接收float
#define UART_BUFFER_SIZE 256
#define START_BYTE1 0x5A
#define START_BYTE2 0xA5
#define START_BYTE3 0xB3
#define END_BYTE1 0xA6
#define END_BYTE2 0x6A
#define END_BYTE3 0x9F

uint8_t uart_rx_buffer[UART_BUFFER_SIZE]; // 接收缓冲区

union FloatBytes {
    float floatValue;
    uint8_t bytes[sizeof(float)];
};
float Remote_control_data[16]; // 接收12个浮点数数据

float last_received_data[16]; // 接收12个浮点数数据
uint32_t data_index = 0;
_Bool is_receiving = 0;
_Bool is_start_byte1_received = 0;
_Bool over_receiving = 0;
_Bool over_receiving2 = 0;
_Bool is_start_byte1_received2 = 0;

void process_data(void) {
    // 在这里进行数据处理，将接收到的数据赋值给k210_states数组
    union FloatBytes floatData;

    for (int i = 0; i < 16; i++) {
        // 将4个字节转换成float类型的数据
        for (int j = 0; j < sizeof(float); j++) {
            floatData.bytes[j] = uart_rx_buffer[i * sizeof(float) + j];
        }
        Remote_control_data[i] = floatData.floatValue;
    }
		
		for (int i = 0; i < 16; i++) {
        last_received_data[i] = Remote_control_data[i];
    }
		
		
		
}
void copy_last_data(void) {
    // 复制上一次接收到的数据到k210_states数组
    for (int i = 0; i < 16; i++) {
        Remote_control_data[i] = last_received_data[i];
    }
}

void reset_receive_state(void) {
    data_index = 0;
    is_receiving = 0;
}
uint8_t uart_rx_buffer2[UART_BUFFER_SIZE]; // 接收缓冲区

int ibod=0;
void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        uint8_t temp_data = USART_ReceiveData(USART2);

        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        if (is_receiving) {
            if (data_index < UART_BUFFER_SIZE) {
                uart_rx_buffer[data_index++] = temp_data;
            }
						else {
                // 缓冲区溢出，重置状态
                reset_receive_state();
            }
        }
		
				if (!is_receiving) {
            // 没有新数据时，复制上一次接收到的数据
            copy_last_data();
					ibod++;
        }
        if (temp_data == START_BYTE1) {
            // 如果还未接收到第一个起始字节，则等待接收
            is_start_byte1_received = 1;
        } else if (temp_data == START_BYTE2 && is_start_byte1_received == 1) {
           is_start_byte1_received2=1;
        } else if (temp_data == START_BYTE3 && is_start_byte1_received == 1&&is_start_byte1_received2==1 ) {
            // 接收到第三个起始字节，可以处理数据
            is_receiving = 1;
					data_index=0;
        } else if (temp_data == END_BYTE1) {
            over_receiving = 1;
        } else if (temp_data == END_BYTE2 && over_receiving == 1) {
            // 接收到了完整的数据帧，处理数据
          over_receiving2=1;
        } else if (temp_data == END_BYTE3 && over_receiving == 1&&over_receiving2==1) {
            // 接收到了完整的数据帧，处理数据
            process_data();
            over_receiving2=0;
            is_receiving = 0;
            is_start_byte1_received = 0;
            over_receiving = 0;
					  is_start_byte1_received2=0;
        }
    }
}

