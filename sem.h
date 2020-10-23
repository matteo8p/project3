#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct semaphore {
	int value;	
	struct queue *sleepQ;	
} semaphore;

void initSem(semaphore*, int);
void P(semaphore*, int id, bool producer);
void V(semaphore*);

void initSem(semaphore *sem, int value) {
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(sem->sleepQ);

	sem->value = value;

	return;
}

void P(semaphore *sem, int id, bool producer) {

	struct TCB_t *p; 
	sem->value--;
	if (sem->value < 0) {
		if(producer)
		{
			printf("\n Producer %d is blocked \n", id); 
		}else
		{
			printf("\n Consumer &d is blocked \n", id); 
		}
		p = delQueue(runQ);
		addQueue(sem->sleepQ, p);
		swapcontext(&(p->context), &(runQ->header->context));
	}
}

void V(semaphore *sem) {
	struct TCB_t *t; 
	sem->value++;

	if (sem->value <= 0) {
		t = delQueue(sem->sleepQ);
		addQueue(runQ, t);
	}
	yield();
}

#endif
