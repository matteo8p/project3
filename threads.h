#include "q.h"

struct TCB_t *runQ;

void startThread(void (*function)(void), int id);
void run();
void yield();

void startThread(void (*function)(void), int id) {
	TCB_t *temp = newItem();	
	void *stack = (void *) malloc(8192);	
	init_TCB(temp, function, stack, 8192, id);	
	addQueue(runQ, temp);	
}

void run() {
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->context));
}

void yield() {
	ucontext_t from, to;
	getcontext(&from);
	runQ->context = from;
	rotQueue(runQ);
	to = runQ->context;
	swapcontext(&from, &to);
}

