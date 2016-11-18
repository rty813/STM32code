#ifndef __HMC_H
#define __HMC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//****************************************
// 定义HMC5883L内部地址
//**************************************** 	
#define CONFIG_A 		0X00    //配置寄存器A  读/写
#define CONFIG_B 		0X01	//配置寄存器B  读/写
#define RES_MODE 		0X02	//模式寄存器   读/写
#define RES_X_MSB		0X03	//X MSB寄存器  读
#define RES_X_LSB		0X04	//X LSB寄存器  读
#define RES_Z_MSB		0X05	//Z MSB寄存器  读
#define RES_Z_LSB		0X06	//Z LSB寄存器  读
#define RES_Y_MSB		0X07	//Y MSB寄存器  读
#define RES_Y_LSB		0X08	//Y LSB寄存器  读
#define STATE			0X09	//状态寄存器   读
#define REC_A			0X0A	//识别寄存器A  读
#define REC_B			0X0B	//识别寄存器B  读
#define REC_C			0X0C	//识别寄存器C  读

#define HMC_SlaveAddress	0x3C	//IIC写入时的地址字节数据，+1为读取  


/////////////////////////////////////////////////////////////////////////////////////   		   
void Init_HMC5883(void);
void Multiple_read_HMC5883(u8*BUF);
void Multiple_read_HMC5883_2(void);
void HMC5883ReadID(void);
void Correct_yaw(void);
#endif
















