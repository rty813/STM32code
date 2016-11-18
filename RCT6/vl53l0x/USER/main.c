#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include <math.h>
#include <string.h>
#include "myiic.h"
u8 BUF[16];

u16 makeuint16(int lsb, int msb) 
{
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}

int main(void)
{	
	u8 val1,val;
	int cnt = 0;
	u16 acnt;
	u16 scnt;
	u32 dist;
	u8 DeviceRangeStatusInternal;
	
	uart_init(115200);
	delay_init();	    //延时函数初始化	  
	IIC_Init();
			printf("欢迎使用vl53l0x激光测距\r\n");
val1 = IIC_Single_Read(VL53L0X_REG_IDENTIFICATION_REVISION_ID);
	printf("Revision ID: %d\r\n",val1);
	val1 = IIC_Single_Read(VL53L0X_REG_IDENTIFICATION_MODEL_ID);
	printf("Device ID: %d\r\n",val1);
	val1 = IIC_Single_Read(VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD);
	printf("PRE_RANGE_CONFIG_VCSEL_PERIOD = %d\r\n",val1);
	IIC_Single_Write(VL53L0X_REG_SYSRANGE_START,0x01);
		delay_ms(500);
		
		cnt = 0;
  while (cnt < 100) { // 1 second waiting time max
    delay_ms(10);
    val = IIC_Single_Read(VL53L0X_REG_RESULT_RANGE_STATUS);
    if (val & 0x01) break;
    cnt++;
  }
  if (val & 0x01) 
		printf("ready\r\n"); 
	else 
	{
		printf("not ready");
		while(1);
	}

	while (1)
	{	
		IIC_Single_Write(VL53L0X_REG_SYSRANGE_START,0x01);
  	BUF[0]=IIC_Single_Read(0x14);
		BUF[1]=IIC_Single_Read(0x15);
		BUF[2]=IIC_Single_Read(0x16);
		BUF[3]=IIC_Single_Read(0x17);
		BUF[4]=IIC_Single_Read(0x18);
		BUF[5]=IIC_Single_Read(0x19);
		BUF[6]=IIC_Single_Read(0x1a);
		BUF[7]=IIC_Single_Read(0x1b);
		BUF[8]=IIC_Single_Read(0x1c);
		BUF[9]=IIC_Single_Read(0x1d);
		BUF[10]=IIC_Single_Read(0x1f);
		BUF[11]=IIC_Single_Read(0x20);
   
		acnt = makeuint16(BUF[7], BUF[6]);
		scnt = makeuint16(BUF[9], BUF[8]);
		dist = makeuint16(BUF[11], BUF[10]);
    DeviceRangeStatusInternal = ((BUF[0] & 0x78) >> 3);

		//printf("ambient count: "); printf("%d\r\n",acnt);
		//printf("signal count: ");  printf("%d\r\n",scnt);
		printf("distance ");       printf("%d\r\n",dist);
		//printf("status: ");        printf("%d\r\n",DeviceRangeStatusInternal);
		//printf("\n");
		delay_ms(50);
	}
	
}
