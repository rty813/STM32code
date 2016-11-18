/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 

uint32_t timeflag;
extern double speed_target[4];

 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/






#include "include.h"


#define count_per 5000	//溢出门限

int update_count[4] = {0,0,0,0};//记录溢出次数
int firstcount[4] = {0,0,0,0};//第一次在中断中读取的编码器计数器的值
int secondcount[4]= {0,0,0,0};//第二次在中断中读取的编码器计数器的值
int speed_pulse[4];					//1ms的脉冲数

double  speed[4]={0,0,0,0};

void TIM2_IRQHandler(void)
{
// 	OSIntEnter();
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))  //如果产生中断
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);			//清除中断标志位
		if((TIM2->CR1 & 0x0010)==0)			  //如果向上溢出，手册中CR1寄存器第4位代表计数方向，0代表上溢
		{
			update_count[0]++;
			
		}
		else
		{
			update_count[0]--;
			
		}
	}
// 	OSIntExit();
}
void TIM3_IRQHandler(void)
{
// 	OSIntEnter();
	if(TIM_GetITStatus(TIM3, TIM_IT_Update))  //如果产生中断
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);			//清除中断标志位
		if((TIM3->CR1 & 0x0010)==0)			  //如果向上溢出，手册中CR1寄存器第4位代表计数方向，0代表上溢
		{
			update_count[1]++;
			
		}
		else
		{
			update_count[1]--;
			
		}
	}
// 	OSIntExit();
}
void TIM4_IRQHandler(void)
{
// 	OSIntEnter();
	if(TIM_GetITStatus(TIM4, TIM_IT_Update))  //如果产生中断
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);			//清除中断标志位
		if((TIM4->CR1 & 0x0010)==0)			  //如果向上溢出，手册中CR1寄存器第4位代表计数方向，0代表上溢
		{
			update_count[2]++;
			
		}
		else
		{
			update_count[2]--;
			
		}
	}
// 	OSIntExit();
}
void TIM5_IRQHandler(void)
{
// 	OSIntEnter();
	if(TIM_GetITStatus(TIM5, TIM_IT_Update))  //如果产生中断
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);			//清除中断标志位
		if((TIM5->CR1 & 0x0010)==0)			  //如果向上溢出，手册中CR1寄存器第4位代表计数方向，0代表上溢
		{
			update_count[3]++;
			
		}
		else
		{
			update_count[3]--;
			
		}
	}
// 	OSIntExit();
}

extern u8 Speed_Flag ;
void TIM7_IRQHandler(void)
{ 
	uint8_t i=0;
// 	OSIntEnter();
	if(TIM_GetITStatus(TIM7, TIM_IT_Update))
	{
		
// 		printf(" ------------------ \r\n" );
			firstcount[0] = TIM_GetCounter(TIM2);//读取第一次计数值
			firstcount[1] = TIM_GetCounter(TIM3);//读取第一次计数值
			firstcount[2] = TIM_GetCounter(TIM4);//读取第一次计数值
			firstcount[3] = TIM_GetCounter(TIM5);//读取第一次计数值
		for(i=0;i<4;i++)
		{
			speed_pulse[i] = (firstcount[i] + count_per * update_count[i] - secondcount[i]);
																					//第一次计数值-第二次计数值+溢出次数*溢出值	  //1ms
      		  //	  转速
			speed[i]=speed_pulse[i]/4.0/500.0*Tined;

			update_count[i] = 0;//溢出次数清零//重要
			
			secondcount[i] = firstcount[i];//保存前一次读数
			
// 			printf("speed----------------%f \r\n",speed[2]);
		}
		Speed_Flag = 1;
		
// 		timeflag++;
// 		if(timeflag>400)
// 		{
// 			timeflag=0;
// 			speed_target[0] = 0;
// 			speed_target[1] = 0;
// 		}

 		TIM_ClearITPendingBit(TIM7 , TIM_IT_Update);
	
}
// 	
// 	OSIntExit();

}




