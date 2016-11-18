#include "led.h"
   
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			// LED1
 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			//超声波
 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
 GPIO_Init(GPIOB, &GPIO_InitStructure);	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
 GPIO_ResetBits(GPIOB,GPIO_Pin_13);
 GPIO_ResetBits(GPIOC,GPIO_Pin_6);
 GPIO_ResetBits(GPIOB,GPIO_Pin_4);
 GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
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
 
