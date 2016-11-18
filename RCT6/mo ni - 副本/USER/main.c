#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include <math.h>
#include <string.h>
#include "GY953.h"
#include "US-015.h"

int main(void)
{	
	float dis1;
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	TIM_Int_Init(0xFFFF,72-1);
	US015Init();
	LED_Init();

	printf("hello");
	
	while(1)
	{
		if (RX1==0)
			printf("6\r\n");
		delay_ms(100);
		
	}
}


