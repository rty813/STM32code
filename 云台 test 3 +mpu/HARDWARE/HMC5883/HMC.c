// #include "myiic.h"
// #include "hmc.h"
// #include "usart.h"
// #include "delay.h"
// #include "math.h"
// #include "mpu6050.h"
// #include "math.h"
// short Hmc_X,Hmc_Y,Hmc_Z;
// double angle;

// void HMC5883ReadID(void)
// {
// 	u8 Re[5];
//   Re[0]=IIC_Read_Single(HMC_SlaveAddress ,REC_A );    //读器件地址
// 	Re[1]=IIC_Read_Single(HMC_SlaveAddress ,REC_B );    //读器件地址
// 	Re[2]=IIC_Read_Single(HMC_SlaveAddress ,REC_C );    //读器件地址
// 	Re[3]=IIC_Read_Single(HMC_SlaveAddress ,0x1E ); 
// //    printf("%d  %d  %d\r\n",Re[0],Re[1],Re[2]);
// 	 printf("%d \r\n",Re[3]);

// }

// void Init_HMC5883(void)
// {
// 	IIC_WriteOneByte(HMC_SlaveAddress,RES_MODE, 0x00);		//连续测量模式
// 	IIC_WriteOneByte(HMC_SlaveAddress,CONFIG_B,0XE0);		//230高斯增益
// }


// //这种读法有问题 ，IIC！！
// void Multiple_read_HMC5883(u8*BUF)
// {    
// 		u8 i;
// 		i=IIC_Read(HMC_SlaveAddress,RES_X_MSB,6,BUF);
// // 	printf("%d\r\n",i);
// 		Hmc_X = (BUF[0]<<8) | BUF[1];
// 		Hmc_Y = (BUF[2]<<8) | BUF[3];
// 		Hmc_Z = (BUF[4]<<8) | BUF[5];
// 	
// 	printf("----------------%d  %d  %d %d  %d  %d\r\n",BUF[0],BUF[1],BUF[2],BUF[3],BUF[4],BUF[5]);
// 		
//    
// }

// int CombineData_Hmc(u8 REG_Address)
// {
// 	short H=0,L=0;
// 	short ComNum;
// 	H=IIC_Read_Single(HMC_SlaveAddress, REG_Address );
// 	L=IIC_Read_Single(HMC_SlaveAddress, REG_Address+1 );
// 	ComNum = (H<<8) | L;
// 	return  ComNum; //合成数据
// }

// void Multiple_read_HMC5883_2(void)
// {
// 	
// 	 Hmc_X=CombineData_Hmc(RES_X_MSB);
// 	 Hmc_Y=CombineData_Hmc(RES_Y_MSB);	
// 	 Hmc_Z=CombineData_Hmc(RES_Z_MSB);	
// 		Hmc_X-= 22;
// 		Hmc_Y+= 34.5;
// 		Hmc_Z+= 8.5;
// 	
// // 	  printf("%lf  \r\n",angle);
// //   	printf("    %d  %d  %d \r\n",Hmc_X,Hmc_Y,Hmc_Z);

// }

// void Correct_yaw()
// {
// 	double cos_roll,sin_roll,sin_pitch,cos_pitch;
// 	double HMC_x,HMC_y;
// 	double angle_yaw,angle_yaw_2;
// 	
// // 	angle_yaw_2=atan2(Hmc_Y,Hmc_X)*57.3;
// // 	printf("  %f ",angle_yaw_2);
// 	cos_roll = cos(EA.Roll / 57.3);
// 	sin_roll = sin(EA.Roll / 57.3);
// 	
// 	cos_pitch= cos(EA.Pitch/ 57.3);
// 	sin_pitch= sin(EA.Pitch/ 57.3);
// 	HMC_x = Hmc_X * cos_pitch + Hmc_Y * sin_roll * sin_pitch + Hmc_Z * cos_roll * sin_pitch;
// 	HMC_y = Hmc_Y * cos_roll - Hmc_Z * sin_roll;
// 	angle_yaw = atan2(HMC_y,HMC_x)*57.3;
// // 	if(angle_yaw<0)angle_yaw=angle_yaw+180;
// 	printf("  %.2f \r\n",angle_yaw);	
// }


// /*This sketch does not utilize the magnetic component Z as tilt compensation can not be done without an Accelerometer
//  
//   ----------------->y
//   |
//   |
//   |
//   |
//   |
//   |
//   x 
//  
//  
//  
//      N 
//  NW  |  NE
//      |  
// W----------E
//      |
//  SW  |  SE
//      S
//  
//  
//  
//  */

