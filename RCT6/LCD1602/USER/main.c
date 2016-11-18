#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h" 
#include "myiic.h"
#include "math.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验23
 IIC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
extern void Delay5ms();
 				 	
//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"WarShipSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
extern unsigned char BUF[8];
int main(void)
{	 
	int x,y,z,i;
	double angle;
	i=0;
	while (i++<500)
		Delay5ms();
	uart_init(115200);
	printf("欢迎使用HMC5883三轴电子指南针\r\n");
	IIC_Init();
	INIT_HMC5883();
	//LED_Init();
	
	while(1)
	{
		Multiple_read();
		x=BUF[0] << 8 | BUF[1];
	    z=BUF[2] << 8 | BUF[3];
		y=BUF[4] << 8 | BUF[5];
		angle = atan2((double)y,(double)x) * (180/3.1415926) + 180;
		printf("%.1lf  %d  %d  %d\r\n",angle,x,y,z);
		i = 0;
		while (i++<300)
			Delay5ms();
	}
}
		
