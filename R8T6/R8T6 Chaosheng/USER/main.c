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
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIMER_INIT(0xffff,71); 
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200;
	printf("��ӭʹ�ó��������\r\n");
	
	while(1)
	{
		Led = !Led;
		printf("��ǰ���룺");
	TX = 1;	
	delay_us(20);
	TX = 0;
	while (!RX);
	TIM_Cmd(TIM3,ENABLE);
	while (RX);
	TIM_Cmd(TIM3,DISABLE);
	if (OverFlowFlag)
		dis = 400;
	else
		dis = TIM_GetCounter(TIM3)/58.;
	TIM_SetCounter(TIM3,0);
	OverFlowFlag = 0;
	printf("%.1f\r\n",dis);
		delay_ms(100);
	}
}
