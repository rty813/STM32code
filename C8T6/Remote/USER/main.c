#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "remote.h"
#include <math.h>
#include <string.h>
#include "joypad.h"

int main(void)
{	
	u8 cmd,key,cmd_prv,key1,i;
	u8 *str=0;
	extern u8 OverFlowFlag;
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	Remote_Init();
	JOYPAD_Init();
	TIM_Int_Init(0xFFFF,72-1);
	printf("at+cona0x00158300A579\r\n");
	delay_ms(1000);
	cmd_prv = '0';

	while(1)	
	{
		key = Remote_Scan();
		key1 = JOYPAD_Read();
		if (key)
		{
			switch(key)
			{			      
				case 98:str="UP";cmd='1' ;break;	    	   
				case 194:str="RIGHT"; cmd='2';break;	   
				case 34:str="LEFT"; cmd='3'; break;		  
				case 224:str="VOL-";cmd='5'; break;		  
				case 168:str="DOWN";cmd='4'; break;		   
				case 144:str="VOL+";cmd='6'; break;		
			}
			LED = 0;
		}
		else 
		if (key1)
		{
			for(i=0;i<8;i++)
				if(key1&(0X80>>i))
					switch (i)
					{
						case 0:str="RIGHT";cmd='2'; break;
						case 1:str="LEFT"; cmd='3'; break;
						case 2:str="DOWN"; cmd='4'; break;	
						case 3:str="UP";   cmd='1'; break;
						case 6:str="VOL-"; cmd='5'; break;	
						case 7:str="VOL+"; cmd='6'; break;	
					}
			LED = 0;
		}
		else			
		{
			LED = 1;
			cmd = '0';
		}		
		if (cmd != cmd_prv)
		{
			printf("%c\r\n",cmd);
			cmd_prv = cmd;
		}

	}

	
}
