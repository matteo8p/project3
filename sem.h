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
		//rotateQueue(&runQ);
		struct TCB_t *p = DelQueue(&runQ);
		AddQueue(&(semaphore->q), p);
        yield(); 
	}else
    {
        semaphore->val--;
    }
}

void V(struct sem *semaphore)
{
	semaphore->val++;
	if (semaphore->val <= 0) {
        struct TCB_t *v = DelQueue(&(semaphore->q)); 
		AddQueue(&runQ, v);
	}
	yield();
}
