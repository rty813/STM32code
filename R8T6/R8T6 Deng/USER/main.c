#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"

int main(void)
{	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	Led = 1;
	
	while(1)
	{
		Led = !RX;
		Light = RX;
		delay_ms(1);
	}
	
}
