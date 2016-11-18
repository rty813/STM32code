#include "led.h"
   
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			// LED1
 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_Init(GPIOC, &GPIO_InitStructure);	 
}