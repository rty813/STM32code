#include "stm32f10x.h"
#include  "math.h"    
#include "IIC_5883.h"
#include "delay_5883.h"
#include "signal_5883.h"
#include "usart.h"

#define	HMC5883L_Addr   0x3C	              //磁场传感器器件地址


u8 test=0; 

u16 angle;
  
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return 0;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return 0;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return 1;
}

unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!I2C_Start())return 0;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop();test=1; return 0;}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

	REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    //return 1;
	return REG_data;

}						      
void conversion(u16 temp_data)  
{   
    Delayms(20);		
}

void read_hmc5883l(void)
{
	
       unsigned char BUF[8];                         //接收数据缓存区
       int   x,y;

       Single_Write(HMC5883L_Addr,0x00,0x10); 
	   Single_Write(HMC5883L_Addr,0x01,0x00);   
       Single_Write(HMC5883L_Addr,0x02,0x00);   
  	   Delayms(10);

       BUF[0]=Single_Read(HMC5883L_Addr,0x03); 
       BUF[1]=Single_Read(HMC5883L_Addr,0x04); 

	   BUF[2]=Single_Read(HMC5883L_Addr,0x05); 
       BUF[3]=Single_Read(HMC5883L_Addr,0x06); 

		x=BUF[0] << 8 | BUF[1]; 
		y=BUF[2] << 8 | BUF[3]; 

      if(x>32768)
        x = -(0xFFFF - x + 1);
      if(y>32768)
        y = -(0xFFFF - y + 1);

	  
       angle= (atan2((double)y,(double)x) * (180 / 3.14159265) + 180); 
	   printf("现在的角度为:=%d°   %d  %d\n",angle,x,y);
	  // conversion(angle);
	
	    
  }

