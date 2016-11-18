#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 unsigned char BUF[8];
 
 
 void Delay5ms()
{
    unsigned int n = 560;

    while (n--);
}

void Delay5us()
{
    __nop();
	__nop();__nop();__nop();
             __nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();
              __nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();
             __nop();__nop();__nop();__nop();

}
 
//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13); 	//PB6,PB7 �����
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay5us();
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay5us();
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	Delay5us();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;Delay5us;	   
	IIC_SCL=1;Delay5us;	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	Delay5us();
	IIC_SCL=1;
	Delay5us();
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	Delay5us();
	IIC_SCL=1;
	Delay5us();
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		Delay5us();  //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		Delay5us();
		IIC_SCL=0;	
		Delay5us();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        Delay5us();
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay5us();
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

void IIC_Single_Write(unsigned char Address, unsigned char data)
{
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	IIC_Wait_Ack();
	IIC_Send_Byte(Address);
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	IIC_Wait_Ack();
	IIC_Stop();
}

unsigned char IIC_Single_Read(unsigned char Address)
{
	unsigned char data;
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	IIC_Wait_Ack();
	IIC_Send_Byte(Address);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(SlaveAddress+1);
	IIC_Wait_Ack();
	data = IIC_Read_Byte(0);
	IIC_Stop();
	return data;
}

void Multiple_read(void)
{
	unsigned char i;
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x03);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(SlaveAddress+1);
	IIC_Wait_Ack();
	for (i=0; i<5; i++)
		BUF[i] = IIC_Read_Byte(0);
	BUF[i] = IIC_Read_Byte(1);
	IIC_Stop();
	Delay5ms();
}

void INIT_HMC5883()
{
	IIC_Single_Write(0x02,0x00);
}





















