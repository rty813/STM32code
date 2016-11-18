#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h"

typedef unsigned char BYTE;
	
void delay(BYTE ms)
{
	BYTE i;
	while(ms--)
	{
		for (i=0; i<250; i++)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

void lcd_init();
void lcd_pos(BYTE pos);

#endif  
	 
	 



