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
    if(semaphore->val > 0)                              //If semaphore value is greater than 0, decrement 
    {
        semaphore->val = semaphore->val - 1;            
    }

    if(semaphore->val <= 0)                             //Block if val is <= 0. Let go when val > 0
    {        
		struct TCB_t *currThread = DelQueue(&runQ);
		addQueue(&(semaphore->queue), currThread);
		while (runQ == NULL) ;
		swapcontext(&(currThread->context), &(runQ->context));
    }
}

void V(struct sem *semaphore)
{
    semaphore->val = semaphore->val + 1;                //Increment semaphore val

    if(semaphore->val <= 0)                             
    {
        AddQueue(&runQ, DelQueue(&(semaphore->q)));                      //Place it into runQ 
    }
    yield(); 
}
