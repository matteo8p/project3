#include "threads.h"

struct sem
{
   int val;                 //Value field 
   struct TCB_t *q;         //queue of TCBs 
};

void InitSem(struct sem *semaphore, int thisValue)      //Initialize value field with specified value 
{
    semaphore->val = thisValue; 
}

void P(struct sem *semaphore)
{
	if (semaphore->val <= 0) {
		struct TCB_t *t = DelQueue(runQ); 
		AddQueue(&(semaphore->q), t);
		swapcontext(&(t->context), &(runQ->context)); 
	}else
	{
		semaphore->val--;
	}
}

void V(struct sem *semaphore)
{
	if(semaphore->val <= 0)
	{
		AddQueue(&runQ, DelQueue(semaphore->q));
	}else
	{
		semaphore->val++; 
	}
	yield(); 
}
