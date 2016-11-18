#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "myiic.h"
u16 makeuint16(int lsb, int msb);
int main(void)
{	 
	//³õÊ¼»¯
	u8 DeviceRangeStatusInternal;
	u8 val1,val;
	int cnt;
	u16 acnt,scnt,dist;
	int buff[15];
	uart_init(115200);
	delay_init();
	LED_Init();
	LED0 = 0;
	IIC_Init();
	
	//×Ô¼ì
	val1 = IIC_Single_Read(VL53L0X_REG_IDENTIFICATION_REVISION_ID);
	printf("Revision ID: %d\r\n",val1);
	val1 = IIC_Single_Read(VL53L0X_REG_IDENTIFICATION_MODEL_ID);
	printf("Device ID: %d\r\n",val1);
	val1 = IIC_Single_Read(VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD);
	printf("PRE_RANGE_CONFIG_VCSEL_PERIOD = %d\r\n",val1);
	IIC_Single_Write(VL53L0X_REG_SYSRANGE_START,0x01);
	
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

	//²â¾à
	
	while(1)
	{	
		LED0 = !LED0;
		buff[0] = IIC_Single_Read(0x14);
		buff[1] = IIC_Single_Read(0x15);
		buff[2] = IIC_Single_Read(0x16);
		buff[3] = IIC_Single_Read(0x17);
		buff[4] = IIC_Single_Read(0x18);
		buff[5] = IIC_Single_Read(0x19);
		buff[6] = IIC_Single_Read(0x20);
		buff[7] = IIC_Single_Read(0x21);
		buff[8] = IIC_Single_Read(0x22);
		buff[9] = IIC_Single_Read(0x23);
		buff[10] = IIC_Single_Read(0x24);
		buff[11] = IIC_Single_Read(0x25);
		acnt = makeuint16(buff[7],buff[6]);
		scnt = makeuint16(buff[9], buff[8]);
		dist = makeuint16(buff[11], buff[10]);
		DeviceRangeStatusInternal = ((buff[0] & 0x78) >> 3);
		printf("ambient count: %d\r\n",acnt);
		printf("signal count: %d\r\n",scnt);
		printf("distance: %d\r\n",dist);
		printf("status: %d\r\n\r\n",DeviceRangeStatusInternal);
		delay_ms(500);
	}
}

u16 makeuint16(int lsb, int msb) {
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}
