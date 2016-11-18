void TIM3_ETR_GetDropCounts_Configuration(void) 
{   
   GPIO_InitTypeDef GPIO_InitStructure; 
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;    //test PA0 TIM8_ETR
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;;    
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
   GPIO_Init(GPIOD, &GPIO_InitStructure);     

   TIM_TimeBaseStructure.TIM_Prescaler = 0x00;    
   TIM_TimeBaseStructure.TIM_Period = 0xFFFF;    
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
   TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  // Time base configuration
   
   TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
   
   TIM_SetCounter(TIM3, 0);
   
   TIM_Cmd(TIM3, ENABLE); 
}
