#ifndef __HMC_H
#define __HMC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//****************************************
// ����HMC5883L�ڲ���ַ
//**************************************** 	
#define CONFIG_A 		0X00    //���üĴ���A  ��/д
#define CONFIG_B 		0X01	//���üĴ���B  ��/д
#define RES_MODE 		0X02	//ģʽ�Ĵ���   ��/д
#define RES_X_MSB		0X03	//X MSB�Ĵ���  ��
#define RES_X_LSB		0X04	//X LSB�Ĵ���  ��
#define RES_Z_MSB		0X05	//Z MSB�Ĵ���  ��
#define RES_Z_LSB		0X06	//Z LSB�Ĵ���  ��
#define RES_Y_MSB		0X07	//Y MSB�Ĵ���  ��
#define RES_Y_LSB		0X08	//Y LSB�Ĵ���  ��
#define STATE			0X09	//״̬�Ĵ���   ��
#define REC_A			0X0A	//ʶ��Ĵ���A  ��
#define REC_B			0X0B	//ʶ��Ĵ���B  ��
#define REC_C			0X0C	//ʶ��Ĵ���C  ��

#define HMC_SlaveAddress	0x3C	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ  


/////////////////////////////////////////////////////////////////////////////////////   		   
void Init_HMC5883(void);
void Multiple_read_HMC5883(u8*BUF);
void Multiple_read_HMC5883_2(void);
void HMC5883ReadID(void);
void Correct_yaw(void);
#endif
















