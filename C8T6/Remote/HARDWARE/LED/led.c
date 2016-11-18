#include "led.h"
   
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			// LED1
 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_Init(GPIOC, &GPIO_InitStructure);	 
}
