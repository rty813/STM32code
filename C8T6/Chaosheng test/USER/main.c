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
		if (RX == 0)
			printf("���ϰ�\r\n");
		delay_ms(500);
	}
}
