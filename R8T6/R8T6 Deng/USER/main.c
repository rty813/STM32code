#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"

int main(void)
{	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	Led = 1;
	
	while(1)
	{
		Led = !RX;
		Light = RX;
		delay_ms(1);
	}
	
}
