#include "Encooder.h"
#include "include.h"


/************************************************************************
						 | CH-A  | CH-B
			TIM2	 | PA15  | PB3  ( 占用了 JTAG )
			TIM3	 | PA6   | PA7
			TIM4	 | PB6   | PB7		
			TIM5	 | PA0   | PA1
			
************************************************************************/
			
void GPIO_Encoder_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	   //很重要的一条必须加上复用功能

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		    //浮空输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		    //浮空输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

/*********************所有的中断向量表配置*****************************
	中断优先级 Group-2	
								PreemptionPriority    SubPriority
			TIM2	 |        0                   1
			TIM3	 |        0    								1
			TIM4	 |        0    								1 	
			TIM5	 |        0   							  1 
			
************************************************************************/

void NVIC_Config(void)
{	  
	  NVIC_InitTypeDef     NVIC_InitStructure;
// TIM2 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				   
  	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                  	 
  	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	  NVIC_Init(&NVIC_InitStructure);

// TIM3
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				   
  	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                  	 
  	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	  NVIC_Init(&NVIC_InitStructure);
	 
// TIM4
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				   
  	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                  	 
  	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	  NVIC_Init(&NVIC_InitStructure);

// TIM5
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				   
  	  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                  	 
  	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	  NVIC_Init(&NVIC_InitStructure);
			 
// TIM7	   中断计算速度 

	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;	 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);	  
	 
	  
}


/**************************************************************
			函数名：ENCODE_Config
			描述  ：配置TIM3编码器模式
			调用  ：内部调用
***************************************************************/
void Encoder_Mode_Config(u16 arr,u16 psc) 
{
  
	TIM_ICInitTypeDef         TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 |
												 RCC_APB1Periph_TIM3 | 
												 RCC_APB1Periph_TIM4 | 
												 RCC_APB1Periph_TIM5 , ENABLE);   
	
	TIM_DeInit(TIM2);
	TIM_DeInit(TIM3);
	TIM_DeInit(TIM4);
	TIM_DeInit(TIM5);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;				   //计数值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				   //预分频此值加1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			   //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;				   //计数值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				   //预分频此值加1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			   //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;				   //计数值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				   //预分频此值加1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			   //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;				   //计数值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				   //预分频此值加1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			   //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);	
	
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//编码器接口初始化
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//编码器接口初始化
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//编码器接口初始化
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//编码器接口初始化

	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 3;//滤波 			
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//溢出中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM2,0);   									
	TIM_Cmd(TIM2, ENABLE);
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 3;//滤波 			
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//溢出中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM3,0);   									
	TIM_Cmd(TIM3, ENABLE);
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 3;//滤波 			
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//溢出中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM4,0);   									
	TIM_Cmd(TIM4, ENABLE);
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 3;//滤波 			
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);//溢出中断
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM5,0);   									
	TIM_Cmd(TIM5, ENABLE);  
  
}

void TIM7_Cal_speed_init(u16 arr,u16 psc)
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 

	TIM_TimeBaseStructure.TIM_Prescaler = arr;
	TIM_TimeBaseStructure.TIM_Period = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
	TIM_Cmd(TIM7, ENABLE);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
}



void Encoder_Init(void)
{
	
	GPIO_Encoder_Config();
	NVIC_Config();
	Encoder_Mode_Config(5000-1,0);  // 编码器溢出值
	TIM7_Cal_speed_init(24,7199);			//400HZ
	
}

  
