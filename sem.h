#include "threads.h"

struct sem
{
   int val;                 //Value field 
   struct TCB_t *q;         //queue of TCBs 
};

void InitSem(sem *semaphore, int thisValue)      //Initialize value field with specified value 
{
    semaphore->val = thisValue; 
}

void P(sem *semaphore)
{
	semaphore->val--;
	if (semaphore->val < 0) {
		//rotateQueue(&runQ);
		struct TCB_t *currThread = DelQueue(runQ);
		AddQueue(&(semaphore->q), currThread);
		swapcontext(&(currThread->context), &(runQ->context));
	}
}

void V(sem *semaphore)
{
	semaphore->val++;
	if (semaphore->val <= 0) {
		AddQueue(runQ, DelQueue(&(semaphore->q)));
	}
	yield();
}
