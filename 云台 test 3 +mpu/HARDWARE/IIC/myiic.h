#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"



 
//IO方向设置

#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}


//IO操作函数	 
#define IIC_SCL    PCout(12) //SCL
#define IIC_SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //输入SDA 

#define true 1
#define false 0 

#define TRUE  0
#define FALSE -1

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)	//写
#define  I2C_Direction_Receiver         ((uint8_t)0x01)	//读

//IIC所有操作函数
void IIC_Init(void);                					//初始化IIC的IO口				 
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8 * data);
int IIC_Write(u8 addr, u8 reg, u8 len, u8* data);
u8 IIC_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf);
u8 IIC_Read_Single(u8 addr, u8 reg );
int IIC_Read(u8 addr, u8 reg, u8 len, u8 *buf);
u8 IIC_WriteOneByte(u8 addr, u8 reg, u8 data);
u16 IIC_GetErrorCounter(void);
u8 IIC_Read_Byte(unsigned char ack);
  
#endif















