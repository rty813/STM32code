#include "US-015.h"
void US015Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);	
}

float GetDis1()
{
	float dis=0;
	TX1 = 1;	
	delay_us(20);
	TX1 = 0;
	while (!RX1);
	TIM_Cmd(TIM3,ENABLE);
	while (RX1);
	TIM_Cmd(TIM3,DISABLE);
	if (OverFlowFlag)
		dis = 400;
	else
		dis = TIM_GetCounter(TIM3)/58.;
	TIM_SetCounter(TIM3,0);
	OverFlowFlag = 0;
	return dis;
}

float GetDis2()
{
	float dis=0;
			TX2 = 1;	
		delay_us(20);
		TX2 = 0;
		while (!RX2);
		TIM_Cmd(TIM3,ENABLE);
		while (RX2);
		TIM_Cmd(TIM3,DISABLE);
		if (OverFlowFlag)
			dis = 400;
		else
			dis = TIM_GetCounter(TIM3)/58.;
		TIM_SetCounter(TIM3,0);
		OverFlowFlag = 0;
		return dis;
}

float GetDis3()
{
	float dis=0;
			TX3 = 1;	
		delay_us(20);
		TX3 = 0;
		while (!RX3);
		TIM_Cmd(TIM3,ENABLE);
		while (RX3);
		TIM_Cmd(TIM3,DISABLE);
		if (OverFlowFlag)
			dis = 400;
		else
			dis = TIM_GetCounter(TIM3)/58.;
		TIM_SetCounter(TIM3,0);
		OverFlowFlag = 0;
		return dis;
}

