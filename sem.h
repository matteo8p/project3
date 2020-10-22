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
	while(semaphore->val <- 0) ;
    semaphore->val--;
}

void V(struct sem *semaphore)
{
	// semaphore->val++;
	// if(semaphore->val <= 0)
	// {
	// 	AddQueue(&runQ, DelQueue(semaphore->q));
	// }
	semaphore->val++; 
	yield(); 
}
