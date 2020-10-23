#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct semaphore {
	int value;	
	struct queue *sleepQ;	
} semaphore;

void initSem(semaphore*, int);
void P(semaphore*);
void V(semaphore*);

void initSem(semaphore *sem, int value) {
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(sem->sleepQ);

	sem->value = value;

	return;
}

void P(semaphore *sem) {

	struct TCB_t *p; 

	if (sem->value == 0) {
		printf("\n Blocked \n"); 
		p = delQueue(runQ);
		addQueue(sem->sleepQ, p);
		swapcontext(&(p->context), &(runQ->header->context));
	}else
	{
		sem->value--;
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
