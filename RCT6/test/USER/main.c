#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"

int main(void)
{	
	extern u8 OverFlowFlag;
	u32 temp=0; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIMER_INIT(0xffff,71); 
	uart_init(115200);	 //串口初始化为115200;
	printf("欢迎使用超声波测距\r\n");
	
	while(1)
	{
		printf("当前距离：");
		TX3 = 1;
		delay_us(20);
		TX3 = 0;
		
		while (!RX3);
		TIM_Cmd(TIM3,ENABLE);
		while (RX3);
		TIM_Cmd(TIM3,DISABLE);
		
		temp = TIM_GetCounter(TIM3);
		if (OverFlowFlag)
			printf("-----\n");
		else
			printf("%f\n",(float)temp/58.);
		OverFlowFlag = 0;
		TIM_SetCounter(TIM3,0);
		delay_ms(100);
	}
}
