#include "timer.h"
#include "led.h"
#include "usart.h"
#include "pid.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!


void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	    
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

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
void TIM2_IRQHandler(void)   //TIM2�ж�
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
				pwm2=pwm2+ IncPIDCalc (Speed* (-1));	//��ʱ��PrevError��LastError E(k-1)
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
	TIM_DeInit(TIM4);	//��Ϊȱʡֵ������
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��
  
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;   // 	���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //P  ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	 
	
	//��ʼ����ʱ��4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	
	//ENCODER ��ʼ��
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//�������ӿڳ�ʼ��

	//��ʼ��TIM4���벶�����
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 3;//IC1F=0000 ���������˲��� 
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	 
	//�жϷ����ʼ��
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�2��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	//TIM_ITConfig(TIM4, TIM_IT_CC1|TIM_IT_Update,ENABLE);//��������ж� ,����CC1IE�����ж�	
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);//����ж�
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		TIM_SetCounter(TIM4,0);  
   	TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��4
		printf("READY\r\n");


}

     			
void TIM4_IRQHandler(void)
{
 
	if(TIM_GetITStatus(TIM4, TIM_IT_Update))  //��������ж�
	{  
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);			//����жϱ�־λ
		if((TIM4->CR1 & 0x0010)==0)			  //�������������ֲ���CR1�Ĵ�����4λ�����������0��������
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





 