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
#define LED PCout(13)// PE5	
#define RX PBin(15)		//ǰ
#define RM1 PBout(12)		//�ұߵ��
#define RM2 PBout(13)
#define LM1 PBout(3)			//��ߵ��
#define LM2 PBout(4)
#define PWM1 PCout(7)
#define PWM2 PBout(14)


void LED_Init(void);//��ʼ��

		 				    
#endif
