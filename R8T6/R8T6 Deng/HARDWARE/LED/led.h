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
#define RX PAin(4)
#define TX PAout(3)
#define Light PAout(8)
#define Led PBout(11)

#define PB5 PBout(5)
#define PB6 PBout(6)
#define PB3 PBout(3)
#define PB4 PBout(4)
#define PC12 PCout(12)

void LED_Init(void);//��ʼ��

		 				    
#endif
