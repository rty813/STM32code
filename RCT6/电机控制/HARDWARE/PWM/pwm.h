#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
 
void TIM_PWM_Init(u16 arr,u16 psc);
void TIM1_Mode_Config(u16 arr,u16 psc);
void TIM8_Mode_Config(u16 arr,u16 psc);
void Speed_con_GPIO_Config(void);


//CH1
#define CH1_A PBout(14)
#define CH1_B PBout(12)
//CH2
#define CH2_A PBout(15)
#define CH2_B PBout(13)
//CH3
#define CH3_A PAout(8)
#define CH3_B PAout(10)
//CH4
#define CH4_A PAout(9)
#define CH4_B PAout(11)





#endif
