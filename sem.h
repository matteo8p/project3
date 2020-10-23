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

void P(struct sem *semaphore, int id)
{
	if (semaphore->val <= 0) {
		printf("Blocked"); 
		struct TCB_t *t = DelQueue(runQ); 
		AddQueue(&(semaphore->q), t);
		swapcontext(&(t->context), &(runQ->context)); 
	}else
	{
		semaphore->val--;
	}
}

void V(struct sem *semaphore, int id)
{
	semaphore->val++; 
	if(semaphore->val <= 0)
	{
		printf("Blocked"); 
		AddQueue(&runQ, DelQueue(semaphore->q));
	}
	yield(); 
}
