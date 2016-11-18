#include "US-015.h"
void US015Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
		
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);	
}

float GetDis()
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
