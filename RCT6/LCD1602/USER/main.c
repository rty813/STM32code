#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h" 
#include "myiic.h"
#include "math.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��23
 IIC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
extern void Delay5ms();
 				 	
//Ҫд�뵽24c02���ַ�������
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
	printf("��ӭʹ��HMC5883�������ָ����\r\n");
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
		
