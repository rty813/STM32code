/**
  ******************************************************************************
  * @date   	2014-11-16
  * @brief  	canģ������
  ******************************************************************************
  * @attention
	*						PB8-CAN-RX
  *						PB9-CAN-TX
  * 
  ******************************************************************************
	*/

#include "include.h"

extern double speed_target[4];
extern double  speed_target_1,speed_target_2;
u8 CAN_EN = 0;
CanTxMsg TxMessage;
CanRxMsg RxMessage;
CAN_TX sta=CAN_TX_READY;

extern uint32_t timeflag;
/**
  * @brief  ����CAN
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
	CAN_InitTypeDef		CAN_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	
	//CAN_GPIO_Config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 , ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE );
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	
	
	//CAN_NVIC_Config
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	//CAN_Mode_Config
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
  CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = ENABLE;
//  CAN_InitStructure.CAN_SJW = CAN_SJW_4tq;
//  CAN_InitStructure.CAN_BS1 = CAN_BS1_15tq;
//  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
//  CAN_InitStructure.CAN_Prescaler =6;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
  CAN_InitStructure.CAN_Prescaler =4;
	CAN_Init(CAN1 , &CAN_InitStructure);
	
	
	//CAN_Filter_Config

	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	
	
/****************ID����*******************/
					//��չID���	//	CAN_FilterInitStructure.CAN_FilterIdHigh = Set_ID >>13 & 0xffff;
												//	CAN_FilterInitStructure.CAN_FilterIdLow = (uint16_t)(Set_ID << 3) | CAN_RTR_DATA | CAN_ID_STD;
	CAN_FilterInitStructure.CAN_FilterIdHigh = Set_ID << 5 & 0xffff;
	CAN_FilterInitStructure.CAN_FilterIdLow = CAN_RTR_DATA | CAN_ID_STD;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0;//0xffc0;//���̶ܹ���׼ID���������һλ�в�ͬ
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0;//0x0005;	//��׼����/Զ��֡
	
	
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	
	CAN_ITConfig(CAN1 , CAN_IT_FMP0 , ENABLE);
}

void TaskCanCommadDeal(void)
{
	float x;
// 	if(	CAN_EN == 1)	
// 	{
	//CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);
	
	//CAN_Transmit(CAN1,(CanTxMsg *)&RxMessage);
	//printf("%x,%x,%x,%x,%d...\n",RxMessage.StdId,RxMessage.ExtId,RxMessage.IDE,RxMessage.RTR,RxMessage.DLC);
	//printf("RE%x,%x,%x,%x,%x,%x,%x,%x,%x...\n",RxMessage.StdId,RxMessage.Data[0],RxMessage.Data[1],RxMessage.Data[2],RxMessage.Data[3],RxMessage.Data[4],RxMessage.Data[5],RxMessage.Data[6],RxMessage.Data[7]);
	if(RxMessage.RTR == CAN_RTR_DATA)	//�����ٶ�ָ��
	{
		switch(RxMessage.StdId)
		{
			case (0x01e0>>5):
				x = *((float*)(&RxMessage.Data[0]));  //��1
			//printf("1 %.1f\r\n",x);
			speed_target[0] = 80*x  ;
				x = *((float*)(&RxMessage.Data[4]));  //��2
			//printf("1 %.1f\r\n",x);
			speed_target[1] = -80*x ;
			timeflag = 0;
			break;
			case (0x02e0>>5):
			x = *((float*)(&RxMessage.Data[0]));   //��1
			speed_target[3] = x * 750;

			//printf("1\r\n");
				break;
			case (0x03e0>>5):
				x = *((float*)(&RxMessage.Data[0]));  //��2
				speed_target[2] = x * 750;
 				//printf("3\r\n");
			//	break;
			case (0x04e0>>5):
// 				speed_target[0] = *(float*)&RxMessage.Data[0];
// 				speed_target[1] = *(float*)&RxMessage.Data[4];
 				//printf("4\r\n");
			//	break;
			default: break;
		}
	}
	
// 		}	
// 	CAN_EN = 0;
//	else if(RxMessage.RTR == CAN_RTR_Remote)//�ش���Ϣ
//	{
//		switch(RxMessage.StdId)
//		{
//			case Main_Track:
//			
//				break;
//			case Side_Track:
//				
//				break;
//			default: break;
//		}
//	}


}

/**
  * @brief  This function handles CAN RX interrupt request.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0))
	{
		CAN_Receive(CAN1 , CAN_FIFO0 , &RxMessage);
// 		CAN_EN = 1;
			
		TaskCanCommadDeal();
		CAN_GetITStatus(CAN1,CAN_IT_FMP0);	
	}
}
