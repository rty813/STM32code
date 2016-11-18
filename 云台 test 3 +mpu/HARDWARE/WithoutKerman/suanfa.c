#include "delay.h"
#include "mpu6050.h"
#include "usart.h"
#include "math.h"
#include "suanfa.h"
#include "timer.h"

extern Acce acc;
extern Gyro gyro;
extern short Hmc_X,Hmc_Y,Hmc_Z;
extern EularAngle EA;
 
struct K_Filter K_F;
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;   // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0;  // scaled integral error

// #define halfT   GET_NOWTIME() * 0.5f   //采样间隔的一半
#define Kp 2.0f // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.005f// integral gain governs rate of convergence of gyroscope biases

float halfT = 0.025f;;
float integralFBx,integralFBy,integralFBz;
float qa0, qa1, qa2, qa3;
float integralFBhand,handdiff;
float halftime ;
float  now; // TIM2 采样时间
float acc_vector = 0;//  加速度合力M/S^2

//Fast inverse square-root
/**************************????********************************************
函数原型：float invSqrt(float x) 
功能   ：快速算1/sqrt
*******************************************************************************/
float invSqrt(float x) 
{
		float halfx = 0.5f * x;
		float y = x;
		long i = *(long*)&y;
		i = 0x5f3759df - (i>>1);
		y = *(float*)&i;
		y = y * (1.5f - (halfx * y * y));
		return y;
}

/**************************????********************************************
函数原型：void IMU_init(void)
功能   ：初始化个参数
*******************************************************************************/
void IMU_init(void)
{
// initialize quaternion
			q0 = 1.0f;    //初始化四元数
			q1 = 0.0f;
			q2 = 0.0f;
			q3 = 0.0f;
	
			qa0 = 1.0f;
			qa1 = 0.0f;
			qa2 = 0.0f;
			qa3 = 0.0f;
	
			exInt = 0.0;
			eyInt = 0.0;
			ezInt = 0.0;
	
			integralFBx = 0.0;
			integralFBy = 0.0; 
			integralFBz= 0.0;
			now = 0;
}


/***************************实现函数*******************************************
函数原型： void IMU_getValues(float * values) \
功能    ：读取加速度计 陀螺仪 磁力计 当前值
*******************************************************************************/




/**************************实现函数********************************************
函数原型；IMU_AHRSupdate（）
功能   ：	更新AHRS四元数
*******************************************************************************/
extern u8 TIM2_OUT ;
//计算四元数
void MPUpDate(struct Acce acc,struct Gyro gyro)
{
        float norm;
        float vx, vy, vz;
        float ex, ey, ez; 
				float ax, ay, az;
				float gx, gy, gz;		
				ax=acc.x;
				ay=acc.y;
				az=acc.z;
	
				gx=gyro.x*3.14/180;
				gy=gyro.y*3.14/180;
				gz=gyro.z*3.14/180;

// normalise the measurements
        norm = invSqrt(ax*ax + ay*ay + az*az);
				if(norm == 0){ printf(" ERROR  ");}	
        ax = ax * norm;
        ay = ay * norm;
        az = az * norm;      
	
// estimated direction of gravity    q1=1
        vx = 2*(q1*q3 - q0*q2);
        vy = 2*(q0*q1 + q2*q3);
        vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
// error is sum of cross product between reference direction of field and direction measured by sensor
        ex = (ay*vz - az*vy);
        ey = (az*vx - ax*vz);
        ez = (ax*vy - ay*vx);
// integral error scaled integral gain
        exInt = exInt + ex*Ki;
        eyInt = eyInt + ey*Ki;
        ezInt = ezInt + ez*Ki;

// adjusted gyroscope measurements
        gx = gx + Kp*ex + exInt;
        gy = gy + Kp*ey + eyInt;
        gz = gz + Kp*ez + ezInt;

// integrate quaternion rate and normalise
		now = GET_NOWTIME();
		halfT = now * 0.5;
        q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
        q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
        q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
        q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  

// normalise quaternion
        norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
        q0 = q0 * norm;
        q1 = q1 * norm;
        q2 = q2 * norm;
        q3 = q3 * norm;
				
}

// 四元数-->欧拉角
void EularAngle_calculate()
{
		
		float t11,t12,t13;
		float	t21,t22,t23;
		float	t31,t32,t33;
	
// 		t11 = q0*q0+q1*q1-q2*q2-q3*q3;
// 		t12=2.0*(q1*q2+q0*q3);
		t13=2.0*(q1*q3-q0*q2);
// 		t21=2.0*(q1*q2-q0*q3);
// 		t22=q0*q0-q1*q1+q2*q2-q3*q3;
		t23=2.0*(q2*q3+q0*q1);
// 		t31=2.0*(q1*q3+q0*q2);
// 		t32=2.0*(q2*q3-q0*q1);
		t33=q0*q0-q1*q1-q2*q2+q3*q3;
 
		EA.Roll = atan2(t23,t33)*57.3;
		EA.Pitch = -asin(t13)*57.3;
// 		EA.Yaw = atan2(t12,t11)*57.3;
// 		if (EA.Yaw < 0)
// 			{
// 					EA.Yaw += (360);
// 		}
}
extern volatile u8 mpu_flag;
void suanfa( )
{
	Data_Pare();
	MPUpDate( acc, gyro);
	EularAngle_calculate();
}






