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
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIMER_INIT(0xffff,71); 
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200;
	printf("��ӭʹ�ó��������\r\n");
	
	while(1)
	{
		printf("��ǰ���룺");
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
