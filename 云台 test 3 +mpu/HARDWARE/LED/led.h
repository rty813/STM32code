#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

#define PB12 PBout(12)// PB5
#define PB13 PEout(13)// PE5	
#define  AX_TXD  GPIO_SetBits(GPIOB,GPIO_Pin_12); GPIO_ResetBits(GPIOB,GPIO_Pin_13);
#define  AX_RXD  GPIO_SetBits(GPIOB,GPIO_Pin_13); GPIO_ResetBits(GPIOB,GPIO_Pin_12);
void LED_Init(void);//��ʼ��
void IO_Init(void);
		 				    
#endif
