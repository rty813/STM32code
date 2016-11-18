#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "remote.h"
#include "US-015.h"
#include <math.h>
#include <string.h>

int main(void)
{	
	u8 cmd,key;
	u16 speed=50;
	u16 dis;
	u8 *str=0;
	extern u8 OverFlowFlag;
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	US015Init();
	
	
	TIM_Int_Init(0xFFFF,72-1);
 	TIM2_PWM_Init(899,0);
	
	while(1)	
	{
		if (USART_RX_STA&0x8000)
		{
			USART_RX_STA = 0;
			cmd = USART_RX_BUF[0];
			//printf("%d\n",cmd);
		}
		
		if (RX == 0)
		{
			if (cmd == '1')
				cmd = '0';
		}
		

		
		switch (cmd)
		{
			case '1':
				RM1 = 0;
				RM2 = 1;
				LM1 = 0;
				LM2 = 1;
				break;
			case '2':
				RM1 = 1;
				RM2 = 0;
				LM1 = 0;
				LM2 = 1;
				break;
			case '3':
				RM1 = 0;
				RM2 = 1;
				LM1 = 1;
				LM2 = 0;
				break;
			case '4':
				RM1 = 1;
				RM2 = 0;
				LM1 = 1;
				LM2 = 0;
				break;		
			case '0':
				RM1 = 0;
				RM2 = 0;
				LM1 = 0;
				LM2 = 0;
				LED = 1;
				break;
			case '5':
				LED = 0;
				speed++;
				if (speed>890)
					speed = 890;
				delay_ms(30);
				break;
			case '6':
				LED = 0;
				if (speed==0)
					speed++;
				speed--;
				delay_ms(30);
				break;
		}
		TIM_SetCompare3(TIM2,speed+40);
		TIM_SetCompare4(TIM2,speed);
	}

	
}
