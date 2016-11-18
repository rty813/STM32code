#ifndef __QUEUE_H
#define __QUEUE_H
#include "queue.h"
#include "stm32f10x.h"

#define QUEUE_SIZE  64    				//�����С


#define Empty_Queue(Queue_Check)	((Queue_Check).Q_Mum == 0)
#define Full_Queue(Queue_Check)		((Queue_Check).Q_Mum == QUEUE_SIZE)

typedef struct{
	uint8_t Q_data[QUEUE_SIZE];
	uint8_t Q_Head, Q_Tail, Q_Mum;
}Queue;															//���ܶ��нṹ��

uint8_t Top_Queue(Queue * pQueue);
void Push_Queue(Queue *pQueue, uint8_t ch);
void Prin_Queue(Queue *pQueue);
void Init_Queue(Queue *pQueue);

#endif /*__QUEUE_H*/
