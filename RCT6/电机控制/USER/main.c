#include "include.h"
double  speed_target[4]    ={0,0,0,0};
double  speed_target_Prv[4]={0,0,0,0};
double  speed_target_1,speed_target_2,speed_target_3,speed_target_4;

PID pid;
extern PID vPID[4]; 

u8 tmp_buf[30]={0},t;

u8 Speed_Flag =0;
double pwm2=100;

extern int update_count[4];//记录溢出次数
extern int firstcount[4];//第一次在中断中读取的编码器计数器的值
extern int secondcount[4];//第二次在中断中读取的编码器计数器的值
extern int speed_pulse[4];
extern double  speed[4];
extern  double  pwmA[4];//PWMA值		 PWM占空比
extern  double  pwmB[4];//PWMB值

void msg_check_2()
{
	char a[7][40]={0};
	int i=0,t=0,u=0,num=0;
	while(USART_RX_BUF[t] != NULL)
			{		
					if(USART_RX_BUF[t] != 32)
					{
						a[u][num]=USART_RX_BUF[t];
						num++;
						t++;
					}
					while(USART_RX_BUF[t] == 32)
					{
						t++;
						if(USART_RX_BUF[t] != 32)
						{
							a[u][num]='\0';
							u++;
							num=0;
							break;
						}

					}
					
			}
	speed_target_1 = atof(a[0]);
	speed_target_2 = atof(a[1]);	
	speed_target_3 = atof(a[2]);
	speed_target_4 = atof(a[3]);
			
//   speed_target_3 = atof(a[0]);			
// 	pid.Proportion = atof(a[1]);
// 	pid.Integral   = atof(a[2]);
// 	pid.Derivative = atof(a[3]);
//   speed_target_4 = atof(a[4]);
			
	for(i=0;i<u+1;i++)
		{
			for(num = 0;num< 20;num++)a[i][num] = NULL;
		}		
	for(i=0;i<20;i++)
		{
			USART_RX_BUF[i] = NULL;
		}	
	i=0;
	t=0;
	u=0;
	num=0;
}


 int main(void) 
 {		
	u8 UART_Speed = 0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	LED_Init();	 

	TIM_PWM_Init(999,3); 		//PWM
	Encoder_Init();	 		//捕获脉冲
	CAN_Config();

 while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   

			USART_RX_STA=0;
			UART_Speed = 1;
			
		}
		if(UART_Speed )
		{
			Speed_Flag = 0;
				msg_check_2();
// 				printf("Speed_Target======*  %f\r\n",speed_target_1);
// 				printf("pid.Proportion====*  %f\r\n",pid.Proportion);
// 				printf("pid.Integral======*  %f\r\n",pid.Integral);
// 				printf("pid.Derivative====*  %f\r\n",pid.Derivative);

							speed_target[0]  = speed_target_1;
							speed_target[1]  = speed_target_2;
							speed_target[2]  = speed_target_3;
							speed_target[3]  = speed_target_4;
			
// 			for(i=0;i<4;i++)
// 					{		

// 							vPID[2].Proportion = pid.Proportion;
// 							vPID[2].Integral  = pid.Integral;
// 							vPID[2].Derivative  = pid.Derivative;
// 					}
				UART_Speed = 0;
		}
		
		
			if(Speed_Flag)
			{
			LED1 =! LED1;
 			TaskMotorSpeedAdj();
			Speed_Flag = 0;
			}
			
			
// 			TaskCanCommadDeal();
			
			
// 			printf("%.1lf %.1lf %.1lf %.1lf \r\n ",speed[0],vPID[0].SetPoint,speed[1],vPID[1].SetPoint);
// 			printf("%.1lf %.1lf %.1lf %.1lf\r\n ",vPID[0].SetPoint,vPID[1].SetPoint,vPID[2].SetPoint,vPID[3].SetPoint);

// 		printf(" 0--> %lf %lf %lf %lf\r\n ",speed[0],vPID[0].SetPoint,pwmA[0],pwmB[0]);
// // 		printf(" 1--> %lf %lf %lf %lf",speed[1],vPID[1].SetPoint,pwmA[1],pwmB[1]);
	
// 		printf("%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf %.1lf \r\n",speed[0],speed[1],speed[2],speed[3],vPID[0].SetPoint,vPID[1].SetPoint,vPID[2].SetPoint,vPID[3].SetPoint);
// 		printf("%.1lf %.1lf %.1lf %.1lf\r\n",speed[0],speed[1],speed[2],speed[3]);
// 	printf("%.1lf \r\n",speed[2]);
		
	}
	
}
