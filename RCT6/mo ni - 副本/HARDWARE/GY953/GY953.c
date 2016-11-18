#include "GY953.h"
void GY953Init(void)
{
	u8 text1[USART_REC_LEN],len,t;
	text1[1] = 0xa5;
	text1[2] = 0x45;
	text1[3] = 0xea;
	len = 3;

	//USART_SendData(UART4, 0xa5);//向串口1发送数据
	//while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);
	//USART_SendData(UART4, 0xa5);//向串口1发送数据
	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);
	for(t=1;t<=len;t++)
		{
			USART_SendData(UART4, text1[t]);//向串口1发送数据
			while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
		}
}
int GetYaw()
{
	int Yaw;
	while(1)
	{
		if (USART_RX_STA&0x8000)
		{
			Yaw = (USART_RX_BUF[8]<<8) | USART_RX_BUF[9];
			Yaw/=100;
			if (Yaw > 180)
				Yaw -= 295;
			USART_RX_STA = 0;
			return Yaw;
		}
}	
}