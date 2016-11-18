#include "queue.h"
#include "usart.h"	


/**
  * @brief  队列操作函数
  * @param  None
  * @retval None
  */
uint8_t Top_Queue(Queue *pQueue)
{
	uint8_t data;
	data = pQueue->Q_data[pQueue->Q_Head];
	pQueue->Q_Head = (pQueue->Q_Head + 1) % QUEUE_SIZE;
	pQueue->Q_Mum --;
	return data;
}

void Push_Queue(Queue *pQueue, uint8_t ch)
{
	pQueue->Q_data[pQueue->Q_Tail] = ch;
	pQueue->Q_Tail = (pQueue->Q_Tail + 1) % QUEUE_SIZE;
	pQueue->Q_Mum ++;
}

void Init_Queue(Queue *pQueue)
{
	pQueue->Q_Head = 0;
	pQueue->Q_Tail = 0;
	pQueue->Q_Mum = 0;
}

void Prin_Queue(Queue *pQueue)
{
	while(!Empty_Queue(*pQueue))
	{
		USART_SendData(USE_USART , Top_Queue(pQueue));
		while(USART_GetFlagStatus(USE_USART , USART_FLAG_TXE) == RESET);
	}
}

