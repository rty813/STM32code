#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include <math.h>
#include <string.h>
#include "myiic.h"
//#include "signal_5883.h"
//#include "IIC_5883.h"

int main(void)
{	
	int x,y,z;
	int minx=180,miny=180,maxx=0,maxy=0;
	unsigned char Mode;
	double angle;
	extern unsigned char BUF[8];
	uart_init(115200);
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM_Int_Init(0xFFFF,72-1);
	IIC_Init();
	
	
//	I2C_GPIO_Config();
	
	delay_ms(1000);
	
	printf("欢迎使用HMC5883三轴电子指南针\r\n");
	while (1)
	{
		INIT_HMC5883();
		//delay_ms(1000);
		BUF[0]=IIC_Single_Read(0x03);
		BUF[1]=IIC_Single_Read(0x04);
		BUF[2]=IIC_Single_Read(0x05);
		BUF[3]=IIC_Single_Read(0x06);
		BUF[4]=IIC_Single_Read(0x07);
		BUF[5]=IIC_Single_Read(0x08);
		
		//Multiple_read();
		x=BUF[0] << 8 | BUF[1]; 
		y=BUF[2] << 8 | BUF[3]; 
        z=BUF[4] << 8 | BUF[5];
      if(x>32768)
        x = -(0xFFFF - x + 1);
      if(z>32768)
        z = -(0xFFFF - z + 1);
      if(y>32768)
        y = -(0xFFFF - y + 1); 
		//printf("%d  %d  %d  %d  %d  %d\r\n",BUF[0],BUF[1],BUF[2],BUF[3],BUF[4],BUF[5]);
		
	  if (x>maxx) maxx = x;
	  if (x<minx) minx = x;
	  if (y>maxy) maxy = y;
	  if (y<miny) miny = y;
	  x = x-(double)(maxx+minx)/2.;
	  y = y-(double)(maxy+miny)/2.;	
	  
	  
	  angle= (atan2((double)y,(double)x) * (180 / 3.14159265) + 180);  // angle in degrees
	
	  printf("%4.1lf  %4d  %4d  %4d  %4d  %4d  %4d  %4d\r\n",angle,x,y,z,minx,maxx,miny,maxy); 
	 // read_hmc5883l();
	  
		delay_ms(20);
	}
}
