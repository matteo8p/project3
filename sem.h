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
	semaphore->value--;
	if (semaphore->value < 0) {
		//rotateQueue(&runQ);
		struct TCB_t *currThread = delQueue(&runQ);
		addQueue(&(semaphore->queue), currThread);
		while (runQ == NULL) ;
		swapcontext(&(currThread->context), &(runQ->context));
	}
}

void V(struct sem *semaphore)
{
	semaphore->value++;
	if (semaphore->value <= 0 && semaphore->queue != NULL) {
		//rotateQueue(&runQ);
		addQueue(&runQ, delQueue(&(semaphore->queue)));
	}
	yield();
}
