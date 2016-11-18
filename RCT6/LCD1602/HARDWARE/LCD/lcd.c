#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	
#include "myiic.h"


void lcd_init()
{
	IIC_Send_Byte(0x38);
	delay(1);
	IIC_Send_Byte(0x0c);
	delay(1);
	IIC_Send_Byte(0x06);
	delay(1);
	IIC_Send_Byte(0x01);
	delay(1);
}

void lcd_pos(BYTE pos)
{							//设定显示位置
	IIC_Send_Byte(pos | 0x80);
}
	