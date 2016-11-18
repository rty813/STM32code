#include "myiic.h"
#include "delay.h"


//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;	//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(5);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;
	delay_us(2);	   
	IIC_SCL=1;
	delay_us(5);	 
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
	delay_us(3);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
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
				IIC_SDA=(txd&0x80)>>7;
				delay_us(2);   //��TEA5767��������ʱ���Ǳ����
				IIC_SCL=1;
				delay_us(4); 
				IIC_SCL=0;	
				txd<<=1; 
				delay_us(2);
    }	 
} 	    
   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA in
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//No Send nACK
    else
        IIC_Ack(); // Send ACK   
    return receive;
}

//addr������slave_address
//reg ����������Ҫд�����ݵ��׵�ַ
//len ��д�����ݵĳ���
//data����Ҫд���һ������	  
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8 * data)
{
    int i;
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);//7λ�����ӵ�ַ+��дλ
    if (IIC_Wait_Ack()) 
	{
        IIC_Stop();
        return false;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    for (i = 0; i < len; i++) 
	{
        IIC_Send_Byte(*data);
        if (IIC_Wait_Ack()) 
		{
            IIC_Stop();
            return false;
        }
		data++;
    }
    IIC_Stop();
    return true;
}

//����ֵ 0��д�ɹ�
//		-1��дʧ��
int IIC_Write(u8 addr, u8 reg, u8 len, u8* data)
{
	if(IIC_Write_Buffer(addr,reg,len,data))
		return TRUE;
	else
		return FALSE;
}

//addr������slave_address
//reg ����������Ҫ�������ݵ��׵�ַ
//len ���������ݵĳ���
//buf ����Ҫ���������ݴ洢λ��
u8 IIC_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf)
{
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
    if (IIC_Wait_Ack())
	{
        IIC_Stop();
        return false;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();

    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Receiver);
    IIC_Wait_Ack();
    while (len)
	{
        *buf = IIC_Read_Byte(1);
        if (len == 1)
            IIC_NAck();
        else
            IIC_Ack();
        buf++;
        len--;
    }
    IIC_Stop();
    return true;
}

//����ֵ 0�����ɹ�
//		-1����ʧ��
int IIC_Read(u8 addr, u8 reg, u8 len, u8 *buf)
{
	if(IIC_Read_Buffer(addr,reg,len,buf))
		return TRUE;
	else
		return FALSE;
}


//addr������slave_address
//reg ����������Ҫ�������ݵ��׵�ַ
//len ���������ݵĳ���
//buf ����Ҫ���������ݴ洢λ��
u8 IIC_Read_Single(u8 addr, u8 reg )
{
		u8 buf;
    IIC_Start();
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
	
    IIC_Start();
		IIC_Send_Byte(addr+1);   
		IIC_Wait_Ack();
    buf = IIC_Read_Byte(0);
    IIC_Stop();
    return buf;
}
//addr������slave_address
//reg ����������Ҫд�����ݵĵ�ַ
//data����Ҫд���һ������
u8 IIC_WriteOneByte(u8 addr, u8 reg, u8 data)
{
    IIC_Start();
    IIC_Send_Byte(addr  );
    if (IIC_Wait_Ack()) 
	{
        IIC_Stop();
        return false;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
    return true;
}

 //��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_11);
	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
	IIC_Stop();
}
