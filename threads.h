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
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->headPointer->context));
	return;
}

void yield() {
	ucontext_t from, to;
	getcontext(&from);
	runQ->headPointer->context = from;
	rotQueue(runQ);
	to = runQ->headPointer->context;
	swapcontext(&from, &to);
}

