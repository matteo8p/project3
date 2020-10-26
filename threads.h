#include "q.h"

#ifndef THREADS_H
#define THREADS_H

#include "q.h"

extern struct TCB_t *runQ;

void startThread(void (*function)(void), int id)
{
	TCB_t *temp = newItem();	
	void *stack = (void *) malloc(8192);	
	init_TCB(temp, function, stack, 8192, id);	
	addQueue(runQ, temp);	
}

void run()
{
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->context));
}

void yield()
{
	struct TCB_t *temp = runQ;
	rotateQueue(&runQ);
	swapcontext(&(temp->context), &(runQ->context));
}

#endif

