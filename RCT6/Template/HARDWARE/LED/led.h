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
#define LED1 PAout(8)// PE5	
#define RX1 PBin(15)
#define TX1 PCout(6)
#define RX2 PBin(12)
#define TX2 PBout(13)
#define RX3 PBin(3)
#define TX3 PBout(4)


void LED_Init(void);//��ʼ��

		 				    
#endif
