void Encoder_Configration (void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
  TIM_ICInitTypeDef TIM_ICInitStructure;               //PC6 AÏà PC7 BÏà 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  
  /* Enable the TIM3 Update Interrupt */ 
  /*NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;   
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   NVIC_Init(&NVIC_InitStructure);*/  
  /* Timer configuration in Encoder mode */
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling    
  TIM_TimeBaseStructure.TIM_Period = 10000;   
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12,                               
  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);   
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = 6;//ICx_FILTER;   
  TIM_ICInit(TIM8, &TIM_ICInitStructure);
  
// Clear all pending interrupts 
  TIM_ClearFlag(TIM8, TIM_FLAG_Update);
  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);   //Reset counter
  
  TIM2->CNT = 0;     
  TIM_Cmd(TIM8, ENABLE);   
}  

	n_Counter = TIM_GetCounter(TIM8); 
	Diled_Disp_Num((float)n_Counter); 
