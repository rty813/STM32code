#ifndef __ENCOODER_H
#define __ENCOODER_H	 
#include "sys.h"


void GPIO_Encoder_Config(void);
void NVIC_Config(void);
void Encoder_Mode_Config(u16 arr,u16 psc) ;
void TIM7_Cal_speed_init(u16 arr,u16 psc) ;
void Encoder_Init(void);

#endif

