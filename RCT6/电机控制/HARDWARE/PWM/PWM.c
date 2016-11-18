#include "pwm.h"
#include "include.h"


/***********PWM占空比*************/
double  pwmA[4]={0,0,0,0};//PWMA值
double  pwmB[4]={0,0,0,0};//PWMB值

/************************************************************************
TIM  8  初始化
						 | CH-1  | CH-2  | CH-3  | CH-4
			TIM8	 | PC6   | PC7   | PC8   | PC9

*************************************************************************/

static void TIM_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	/* TIM clock enable */
	//PCLK1经过2倍频后作为TIM3的时钟源等于72MHz
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);	   //很重要的一条必须加上复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */

// TIM8	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   	 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}



void TIM8_Mode_Config(u16 arr,u16 psc)
{ 
         
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure; 
 
	TIM_TimeBaseStructure.TIM_Period = arr;       
	TIM_TimeBaseStructure.TIM_Prescaler = psc ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	
	TIM_OCInitStructure.TIM_Pulse = 0 ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;	
	
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);																 
	
	TIM_OCInitStructure.TIM_Pulse = 0 ;
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);	
	
	TIM_OCInitStructure.TIM_Pulse =0 ;
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);	
	
	TIM_OCInitStructure.TIM_Pulse = 0 ;
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);	
	
	TIM_Cmd(TIM8, ENABLE);	
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
		
}


void Speed_con_GPIO_Config(void)
{
		 GPIO_InitTypeDef  GPIO_InitStructure;	
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		 GPIO_Init(GPIOB, &GPIO_InitStructure);					
		 GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);		

	
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;	    	
		 GPIO_Init(GPIOA, &GPIO_InitStructure);	  			
		 GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);							 

}

/************************************************************

			注意时钟开启逻辑

************************************************************/
void TIM_PWM_Init(u16 arr,u16 psc)
{
	TIM_GPIO_Config();
	TIM8_Mode_Config(arr,psc);
	Speed_con_GPIO_Config();
}

