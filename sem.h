#include "threads.h"

struct sem
{
   int val;                 //Value field 
   struct TCB_t *q;         //queue of TCBs 
};

void InitSem(struct sem *semaphore, int thisValue)      //Initialize value field with specified value 
{
	semaphore = malloc(sizeof(struct sem)); 
    semaphore->val = thisValue; 
	InitQueue(semaphore->q); 
}

void P(struct sem *semaphore)
{
	semaphore->val--;
	if (semaphore->val <= 0) {
		struct TCB_t *t = DelQueue(runQ); 
		AddQueue(&(semaphore->q), t);
		swapcontext(&(t->context), &(runQ->context)); 
	}
}

void V(struct sem *semaphore)
{
	semaphore->val++; 
	if(semaphore->val <= 0)
	{
		AddQueue(&runQ, DelQueue(semaphore->q));
	}
	yield(); 
}
