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
	u8 fg3 = 0;
	u8 fg4 = 0;
	u8 fg5 = 0;
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
	TIM_Int_Init(0xFFFF,72-1);
	
	LED1 = 1;
	printf("1");		//1：前进	2：右转	  3：左转   4：右偏    5：左偏    6：stop
	while(1)
	{
		OverFlowFlag = 0;	//Init
		fg3 = 0;
		fg4 = 0;
		fg5 = 0;
		dis1 = 0;		//right
		dis2 = 0;		//front
		dis3 = 0;		//left
		
		TX1 = 1;		//发送高电平
		TX2 = 1;
		TX3 = 1;
		delay_us(20);
		TX1 = 0;
		TX2 = 0;
		TX3 = 0;				

		while (1)
		{
			if ((RX1) && (!fg3))		//捕获上升沿
			{
				TIM_Cmd(TIM3, ENABLE);
				fg3 = 1;
			}
			if ((RX2) && (!fg4))
			{
				TIM_Cmd(TIM4, ENABLE);
				fg4 = 1;
			}
			if ((RX3) && (!fg5))
			{
				fg5 = 1;
				TIM_Cmd(TIM5, ENABLE);
			}
			
			if ((fg3) && (!RX1))		//捕获下降沿
			{
				fg3 = 0;
				dis1 = TIM_GetCounter(TIM3)/58.;
				TIM_SetCounter(TIM3,0);
				TIM_Cmd(TIM3, DISABLE);
			}
			if ((fg4) && (!RX2))
			{
				fg4 = 0;
				dis2 = TIM_GetCounter(TIM4)/58.;
				TIM_SetCounter(TIM4,0);
				TIM_Cmd(TIM4, DISABLE);
			}
			if ((fg5) && (!RX3))
			{
				fg5 = 0;
				dis3 = TIM_GetCounter(TIM5)/58.;
				TIM_SetCounter(TIM5,0);
				TIM_Cmd(TIM5, DISABLE);
			}
			
			if ((dis1!=0) && (dis2!=0) && (dis3!=0))	//捕获成功
				break;
			
			if (OverFlowFlag)			//定时器溢出，捕获未完成
			{
				TIM_SetCounter(TIM5,0);
				TIM_Cmd(TIM5, DISABLE);
				TIM_SetCounter(TIM4,0);
				TIM_Cmd(TIM4, DISABLE);
				TIM_SetCounter(TIM3,0);
				TIM_Cmd(TIM3, DISABLE);
				break;
			}
		}
		if (OverFlowFlag)
			continue;
		//成功捕获
		
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
		
		if (fabs(diff1)>5)	continue;	//滤波
		if (fabs(diff2)>5)	continue;
		if (fabs(diff3)>5)	continue;
		if (fabs(diff4)>5)	continue;
		if (fabs(diff5)>5)	continue;
		if (fabs(diff6)>5)	continue;
		
		if ((dis1<10)||(dis2<10)||(dis3<10))	//碰撞保护
			printf("6");
		
		if (dis1>200)		
		{
			printf("2");	 //Turn Right
			delay_ms(2000);
			printf("1");
			delay_ms(2000);
		}
		else
		if (dis2<100)
		{
			if (dis3>200)
			{
				printf("3");	//Turn Left
				delay_ms(2000);
				printf("1");
				delay_ms(2000);
			}
			else
			{
				printf("2");	 //Turn Back
				delay_ms(4000);
				printf("1");
			}
		}
		//车身偏，调整
		if ((diff1>2)&&(diff2>2))	//往右偏
		{
			printf("5");	//左偏
			delay_ms(200);
			printf("1");
		}
		if ((diff1<-2)&&(diff2<-2))	//往左偏
		{
			printf("4");	//右偏
			delay_ms(200);
			printf("1");
		}

		delay_ms(100);
	}
}
