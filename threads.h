#include "q.h"

struct queue *runQ;

void startThread(void (*function)(void));
void run();
void yield();

void start_thread(void (*function)(void), int id) {
	TCB_t *temp = newItem();	
	void *stack = (void *) malloc(8192);	
	init_TCB(temp, function, stack, 8192, id);	
	addQueue(runQ, temp);	
}

void run() {
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->header->context));
}

void yield() {
	ucontext_t from, to;
	getcontext(&from);
	runQ->header->context = from;
	rotQueue(runQ);
	to = runQ->header->context;
	swapcontext(&from, &to);
}
