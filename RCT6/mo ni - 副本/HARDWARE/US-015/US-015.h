#ifndef US_015_H
#define US_015_H
#include "delay.h"
#include "sys.h"
#include "timer.h"

#define RX2 PBin(15)		//Ç°
#define TX2 PCout(6)
#define RX1 PBin(12)		//¡ú
#define TX1 PBout(13)
#define RX3 PBin(3)			//¡û
#define TX3 PBout(4)

extern u8 OverFlowFlag;
void US015Init(void);
float GetDis1(void);
float GetDis2(void);
float GetDis3(void);

#endif
