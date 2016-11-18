#include "myiic.h"
#include "delay.h"


//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;	//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(5);							   	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 

//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
				IIC_SDA=(txd&0x80)>>7;
				delay_us(2);   //对TEA5767这三个延时都是必须的
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

//addr：器件slave_address
//reg ：从器件将要写入数据的首地址
//len ：写入数据的长度
//data：将要写入的一串数据	  
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8 * data)
{
    int i;
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);//7位器件从地址+读写位
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

//返回值 0：写成功
//		-1：写失败
int IIC_Write(u8 addr, u8 reg, u8 len, u8* data)
{
	if(IIC_Write_Buffer(addr,reg,len,data))
		return TRUE;
	else
		return FALSE;
}

//addr：器件slave_address
//reg ：从器件将要读的数据的首地址
//len ：读出数据的长度
//buf ：将要读出的数据存储位置
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

//返回值 0：读成功
//		-1：读失败
int IIC_Read(u8 addr, u8 reg, u8 len, u8 *buf)
{
	if(IIC_Read_Buffer(addr,reg,len,buf))
		return TRUE;
	else
		return FALSE;
}


//addr：器件slave_address
//reg ：从器件将要读的数据的首地址
//len ：读出数据的长度
//buf ：将要读出的数据存储位置
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
//addr：器件slave_address
//reg ：从器件将要写入数据的地址
//data：将要写入的一个数据
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

 //初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_11);
	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
	IIC_Stop();
}
