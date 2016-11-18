#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include <math.h>
#include <string.h>

int main(void)
{	
	extern u8 OverFlowFlag;
	float dis1;
	float dis2;
	float dis3;
	float cap1_1 = 0;
	float cap1_2 = 0;
	float cap1_3 = 0;
	float cap2_1 = 0;
	float cap2_2 = 0;
	float cap2_3 = 0;
	float cap3_1 = 0;
	float cap3_2 = 0;
	float cap3_3 = 0;
	float diff1;
	float diff2;
	float diff3;
	float diff4;
	float diff5;
	float diff6;	
	
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TX1 = 0;
	TX2 = 0;
	TX3 = 0;
	TIM_Int_Init(0xffff,72-1);
	
	printf("1\r\n");		//1：前进	2：右转	  3：左转   4：右偏    5：左偏    6：stop
	while(1)
	{
		OverFlowFlag = 0;	//Init
		dis1 = 0;		//right
		dis2 = 0;		//front
		dis3 = 0;		//left
		
		//右超声波捕获
		TX1 = 1;	
		delay_us(20);
		TX1 = 0;
		while (!RX1);
		TIM_Cmd(TIM3,ENABLE);
		while (RX1);
		TIM_Cmd(TIM3,DISABLE);
		if (OverFlowFlag)
			dis1 = 400;
		else
			dis1 = TIM_GetCounter(TIM3)/58.;		
		TIM_SetCounter(TIM3,0);
		OverFlowFlag = 0;
		
	/*	//前超声波捕获
		TX2 = 1;	
		delay_us(20);
		TX2 = 0;
		while (!RX2);
		TIM_Cmd(TIM3,ENABLE);
		while (RX2);
		TIM_Cmd(TIM3,DISABLE);
		if (OverFlowFlag)
			dis2 = 400;
		else
			dis2 = TIM_GetCounter(TIM3)/58.;
		TIM_SetCounter(TIM3,0);
		OverFlowFlag = 0;
		
		
		//左超声波捕获
		TX3 = 1;	
		delay_us(20);
		TX3 = 0;
		while (!RX3);
		TIM_Cmd(TIM3,ENABLE);
		while (RX3);
		TIM_Cmd(TIM3,DISABLE);
		if (OverFlowFlag)
			dis3 = 400;
		else
			dis3 = TIM_GetCounter(TIM3)/58.;
		TIM_SetCounter(TIM3,0);
		OverFlowFlag = 0;
		*/
		printf("R:%.1f  L:%.1f   F:%.1f\n",dis1,dis3,dis2);
		delay_ms(100);
		continue;
		cap1_1 = cap1_2;
		cap1_2 = cap1_3;
		cap1_3 = dis1;
		
		cap2_1 = cap2_2;
		cap2_2 = cap2_3;
		cap2_3 = dis2;
		
		cap3_1 = cap3_2;
		cap3_2 = cap3_3;
		cap3_3 = dis3;
		//记录三次捕获的差值
		diff1 = (cap1_1-cap1_2);
		diff2 = (cap1_2-cap1_3);
		diff3 = (cap2_1-cap2_2);
		diff4 = (cap2_2-cap2_3);
		diff5 = (cap3_1-cap3_2);
		diff6 = (cap3_2-cap3_3);
		

		if (dis1>100)		
		{
			printf("2\n");	 //Turn Right
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(500);
			printf("1\n");
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
		}
		else
		if (dis2<50)
		{
			if (dis3>100)
			{
				printf("3\n");	//Turn Left
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(500);
				printf("1\n");
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
			else
			{
				printf("2\n");	 //Turn Back
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				printf("1\n");
			}
		}
		
		//车身偏，调整
		if (((diff1>1)&&(diff2>1))||(dis3<15))	//往右偏
		{
			printf("5\r\n");	//左偏
			delay_ms(500);
			printf("1\n");
		}
		if (((diff1<-1)&&(diff2<-1))||(dis1<15))	//往左偏
		{
			printf("4\r\n");	//右偏
			delay_ms(500);
			printf("1\n");
		}
		
		
		if ((dis1<10)||(dis2<15)||(dis3<10))	//碰撞保护
		{
			
			printf("6\r\n");
			//printf("R:%.1f  L:%.1f   F:%.1f\n",dis1,dis3,dis2);
			delay_ms(1000);
			continue;
		}
		else
		{
			printf("1\r\n");
		}
		delay_ms(50);
	}
}
