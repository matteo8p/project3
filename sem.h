#include "threads.h"

typedef struct semaphore {
	int value;	
	struct queue *semQ;	
} semaphore;

void initSem(semaphore*, int);
void P(semaphore*, int id);
void V(semaphore*);

void initSem(semaphore *sem, int value) {
	sem->semQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(sem->semQ);
	sem->value = value;
}

void P(semaphore *sem, int id) 
{
	sem->value--; 
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
			addQueue(sem->semQ, tcb);
			swapcontext(&(tcb->context), &(runQ->headPointer->context));
		}
	
}

void V(semaphore *sem) 
{
	sem->value++;
	if(sem->value <= 0 && sem->semQ != NULL)
	{
		struct TCB_t *tcb = delQueue(sem->semQ);
		addQueue(runQ, tcb);
	}

	yield(); 
}
