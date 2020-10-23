#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct semaphore {
	int value;	
	struct queue *sleepQ;	
} semaphore;

void initSem(semaphore*, int);
void P(semaphore*, int id);
void V(semaphore*);

void initSem(semaphore *sem, int value) {
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(sem->sleepQ);

	sem->value = value;

	return;
}

void P(semaphore *sem, int id) 
{
	while(1) 
	{
		if(sem->value <= 0)
		{
			if(id > 0)
			{
				printf("\n Producer %d is waiting \n", id); 
			}else
			{
				printf("\n Consumer %d is waiting \n", id); 
			}
			struct TCB_t *tcb = delQueue(runQ);
			addQueue(sem->sleepQ, tcb);
			swapcontext(&(tcb->context), &(runQ->header->context));
		}else
		{
			sem->value--; 
		}
	}
}

void V(semaphore *sem) 
{
	if(sem->value <= 0 && sem->sleepQ != NULL)
	{
		struct TCB_t *tcb = delQueue(sem->sleepQ);
		addQueue(runQ, tcb);
	}
	sem->value++;
	yield(runQ);
}

#endif
