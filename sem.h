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
}

void P(semaphore *sem) {
	struct TCB_t *t; 
	sem->value--;
	if (sem->value < 0) {
		printf("\nStall\n");
		t = delQueue(runQ);
		addQueue(sem->sleepQ, t);
		swapcontext(&(t->context), &(runQ->header->context));
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

