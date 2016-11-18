#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"

int main(void)
{	
	extern u8 OverFlowFlag;
	u32 temp=0;
float dis;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIMER_INIT(0xffff,71); 
	uart_init(115200);	 //串口初始化为115200;
	printf("欢迎使用超声波测距\r\n");

	while(1)
	{
		if (RX == 0)
			printf("有障碍\r\n");
		delay_ms(500);
	}
}
