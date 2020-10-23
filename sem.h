#include "threads.h"

struct sem
{
   int val;                 //Value field 
   struct TCB_t *q;         //queue of TCBs 
};

void InitSem(struct sem *semaphore, int thisValue)      //Initialize value field with specified value 
{
    semaphore->val = thisValue; 
	InitQueue(&(semaphore->q)); 
}

void P(struct sem *semaphore, int id)
{
	semaphore->val--;
	if (semaphore->val <= 0) {
		printf("Producer/Consumer %d blocked", id); 
		struct TCB_t *t = DelQueue(runQ); 
		AddQueue(&(semaphore->q), t);
		while(runQ == NULL) ;
		swapcontext(&(t->context), &(runQ->context));
	}
}

void V(struct sem *semaphore, int id)
{
	semaphore->val++;
	if(semaphore->val <= 0 && semaphore->q != NULL)
	{
		AddQueue(&runQ, DelQueue(semaphore->q));
	}
	yield(); 
}
