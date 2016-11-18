#ifndef US_015_H
#define US_015_H
#include "delay.h"
#include "sys.h"
#include "timer.h"

#define RX1 PCin(6)	
#define TX1 PCout(7)

extern u8 OverFlowFlag;
void US015Init(void);
float GetDis(void);

#endif
