#include "timer.h"
#include "led.h"
#include "usart.h"
#include "pid.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!


void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	    
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设

}

int TIM4CH1_ENCODER_Up =0;
int TIM4CH1_ENCODER_Down =0;
int TIM4CH1_ENCODER=0;
u16 Present_Num;
int Pluse_Num;
u16 Previous_Num;

extern double Speed_Target;
double Speed;
extern double pwm2;
void TIM2_IRQHandler(void)   //TIM2中断
{
	static int deal;
	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		LED1 = !LED1;
		Present_Num=TIM_GetCounter(TIM4);
		Pluse_Num=Present_Num+10000*TIM4CH1_ENCODER_Up-Previous_Num;
		Speed = Pluse_Num/1024.0 *1000;
		Previous_Num=Present_Num;  
					
		if( Speed_Target > 0 )
			{
				pwm2 = pwm2+ IncPIDCalc (Speed);
				if(pwm2>995)pwm2=995;
				if(pwm2<0)pwm2=0;
				deal = pwm2;
				TIM_SetCompare2(TIM3,deal);
				TIM_SetCompare1(TIM3,0);
			}
			
			if(Speed_Target == 0)
			{
				TIM_SetCompare2(TIM3,0);
				TIM_SetCompare1(TIM3,0);
			}
			
		  if( Speed_Target < 0)
			{
				pwm2=pwm2+ IncPIDCalc (Speed* (-1));	//此时的PrevError是LastError E(k-1)
				if(fabs(pwm2)>995)pwm2=995;
				if(pwm2<0)pwm2=0;
				deal = pwm2;
				TIM_SetCompare2(TIM3,0);
				TIM_SetCompare1(TIM3,deal);
			}
		TIM4CH1_ENCODER_Up = 0 ;
		TIM_ClearITPendingBit(TIM2 , TIM_IT_Update);

		
	}
}




void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM4_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM4时钟
	TIM_DeInit(TIM4);	//设为缺省值？？？
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟
  
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;   // 	清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //P  输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	 
	
	//初始化定时器4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	
	//ENCODER 初始化
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//编码器接口初始化

	//初始化TIM4输入捕获参数
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 3;//IC1F=0000 配置输入滤波器 
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	 
	//中断分组初始化
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级2级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	//TIM_ITConfig(TIM4, TIM_IT_CC1|TIM_IT_Update,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);//溢出中断
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		TIM_SetCounter(TIM4,0);  
   	TIM_Cmd(TIM4,ENABLE ); 	//使能定时器4
		printf("READY\r\n");


}

     			
void TIM4_IRQHandler(void)
{
 
	if(TIM_GetITStatus(TIM4, TIM_IT_Update))  //如果产生中断
	{  
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);			//清除中断标志位
		if((TIM4->CR1 & 0x0010)==0)			  //如果向上溢出，手册中CR1寄存器第4位代表计数方向，0代表上溢
		{
			//printf("I'M INCREASING\n");
			
			TIM4CH1_ENCODER_Up++;
			
		}
		else
		{
//			TIM4CH1_ENCODER_Down++;
 			TIM4CH1_ENCODER_Up--;
		}

	} 
}





 