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
	semaphore->val--;
	if (semaphore->val <= 0) {
		//rotateQueue(&runQ);
		struct TCB_t *currThread = DelQueue(&runQ);
		AddQueue(&(semaphore->q), currThread);
		while (runQ == NULL) ;
		swapcontext(&(currThread->context), &(runQ->context));
	}
}

void V(struct sem *semaphore)
{
	semaphore->val++;
	if (semaphore->val <= 0 && semaphore->q != NULL) {
		AddQueue(&runQ, DelQueue(&(semaphore->q)));
	}
	yield();
}
