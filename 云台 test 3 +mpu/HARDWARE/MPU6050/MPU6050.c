#include "myiic.h"
#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "math.h"
#include "suanfa.h"
short  Acceleration[3];
u8 a[6];
short AX,AY,AZ;
short Temperature;

/***************************************************************************
			误差校准
*****************************************************************************/
short Acc_correct[3]={0,0,0};
double Gyro_correct[3];
 
Acce acc;
Gyro gyro;
EularAngle EA;
 
void InitMPU6050()
{
	
  int i=0,j=0;
  //在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      ;
    }
  }
	IIC_WriteOneByte(SlaveAddress, PWR_MGMT_1, 0x00);		//解除休眠状态
	IIC_WriteOneByte(SlaveAddress,SMPLRT_DIV, 0x07);		//陀螺仪采样率，典型值：0x07(125Hz)
	IIC_WriteOneByte(SlaveAddress,CONFIG, 0x06);				//低通滤波频率，典型值：0x06(5Hz)
	IIC_WriteOneByte(SlaveAddress,GYRO_CONFIG, 0x18);		//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	IIC_WriteOneByte(SlaveAddress,ACCEL_CONFIG, 0x00);	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
}


void MPU6050ReadID(void)
{
	u8 Re = 0;
   Re=IIC_Read_Single(SlaveAddress ,WHO_AM_I );    //读器件地址
//    printf("%d\r\n",Re);
// 	printf("%KO\r\n");
}

//**************************************
//合成数据
//**************************************
//short 2字节8位
int CombineData(u8 REG_Address)
{
	short H=0,L=0;
	short ComNum;
	H=IIC_Read_Single(SlaveAddress, REG_Address );
	L=IIC_Read_Single(SlaveAddress, REG_Address+1 );
	ComNum = (H<<8) | L;
	return  ComNum; //合成数据
}

void GetData()
{
	short temp3;
	 Acceleration[0]=CombineData(ACCEL_XOUT_H)-Acc_correct[0];
	 Acceleration[1]=CombineData(ACCEL_YOUT_H)-Acc_correct[1];	
	 Acceleration[2]=CombineData(ACCEL_ZOUT_H)-Acc_correct[2];	
	
	AX = CombineData(GYRO_XOUT_H);
	AY = CombineData(GYRO_YOUT_H);
	AZ = CombineData(GYRO_ZOUT_H);
	
// 	temp3=CombineData(TEMP_OUT_H);
// 	Temperature=(((double) (temp3 + 13200)) / 280)-13.0;
	
}

void Data_Trans()
{
// 	acc.x=(double)(Acceleration[0]*9.8/16384);
// 	acc.y=(double)(Acceleration[1]*9.8/16384);	
// 	acc.z=(double)(Acceleration[2]*9.8/16384);	
	acc.x=(double)(Acceleration[0]);
	acc.y=(double)(Acceleration[1]);	
	acc.z=(double)(Acceleration[2]);	
	gyro.x=(double)(AX/16.4)-Gyro_correct[0];
	gyro.y=(double)(AY/16.4)-Gyro_correct[1];
	gyro.z=(double)(AZ/16.4)-Gyro_correct[2];
}



void Data_Pare()
{
	GetData();
	Data_Trans();
}

// uint32_t GET_NOWTIME(uint32_t * lasttime)//????systick????,32?

// {
// 		uint32_t temp,temp1,temp2;
// 		temp1 = SysTick->VAL;
// 		temp = SysTick->CTRL;
// 		if(temp&(1<<16)) 
// 		temp2 = *lasttime + 0xffffff - temp1;//????
// 		else
// 		temp2 = *lasttime - temp1;
// 		*lasttime = temp1;
// 		if(temp2>100000)return 0;
// 		return temp2;

// }




  
