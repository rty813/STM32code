#ifndef __SUANFA_H
#define __SUANFA_H
#include "mpu6050.h"
#include "sys.h"

// #define Kp 2.0f     // proportional gain   governs rate of convergence to accelerometer/magnetometer
// #define Ki 0.005f   // integral gain governs rate of convergence of gyroscope biases
// #define halfT 0.025f  // half the sample period
// #define Simple_Size 20

struct K_Filter
{
	double Pitch_Avg,Yaw_Avg,Roll_Avg;
	double Pitch_Avg2,Yaw_Avg2,Roll_Avg2;
	double Pitch_Con,Yaw_Con,Roll_Con;

};

//********************************************************************************
extern struct Acce acc;
extern struct Gyro gyro;
extern struct EularAngle EA;

void MPUpDate(struct Acce acc,struct Gyro gyro);
void EularAngle_calculate(void);
void suanfa(void);

#endif

