#ifndef THREADS_H
#define THREADS_H

#include "q.h"

struct queue *runQ;

void startThread(void (*function)(void), int id);
void run();
void yield();

void startThread(void (*function)(void), int id) {
	TCB_t *temp = newItem();	
	void *stack = (void *) malloc(8192);	
	init_TCB(temp, function, stack, 8192, id);	
	addQueue(runQ, temp);	

	return;
}

void run() {
	// Declare the context of the first TCB
	ucontext_t parent;
	
	// Grab the original conext
	getcontext(&parent);
	
	// Swap to the first TCB in Run Queue
	swapcontext(&parent, &(runQ->header->context));

	return;
}

void yield() {
	// Declare the context of the threaded TCBs
	ucontext_t from, to;
	
	// Grab the running processes context
	getcontext(&from);
	
	// Update the context of the current process
	runQ->header->context = from;
	
	// Move the process to the end of the Queue
	rotQueue(runQ);
	
	// Grab the next process in the Run Queue
	to = runQ->header->context;
	
	// Swap the currently running process to the next process in the Queue
	swapcontext(&from, &to);
	return;
}

#endif
