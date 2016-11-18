#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
#include"delay.h"

#define SDA_OUT() {GPIOB->CRH &= 0xffff0fff; GPIOB->CRH |= 0x00003000;}
#define SDA_IN() {GPIOB->CRH &= 0xffff0fff; GPIOB->CRH |= 0x00008000;}
#define IIC_SDA PBout(13)
#define IIC_SCL PBout(12)
#define READ_SDA	PBin(13)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8);
u8 IIC_Read_Byte(u8);	//读一个字节，ack = 1时， 发送ACK， ack = 0，发送nACK

#endif
