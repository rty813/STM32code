#include "timer.h"
#include "led.h"

void TIMER_INIT(u16 ARR, u16 PSC)
{
	NVIC_InitTypeDef NVIC_Str;	
	TIM_TimeBaseInitTypeDef TimerInitStr;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	

	
	TimerInitStr.TIM_CounterMode = TIM_CounterMode_Up;
	TimerInitStr.TIM_Prescaler = PSC;
	TimerInitStr.TIM_Period = ARR;	
	TIM_TimeBaseInit(TIM3,&TimerInitStr);

	NVIC_Str.NVIC_IRQChannel =   TIM3_IRQn;
	NVIC_Str.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Str.NVIC_IRQChannelSubPriority = 2;
	NVIC_Str.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_Str);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,DISABLE);
	
}

u8 OverFlowFlag = 0;

void TIM3_IRQHandler(void)
{

 	OverFlowFlag = 1;
 
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位

}

