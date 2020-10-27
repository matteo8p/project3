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
}

void run() {
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->headPointer->context));
}

void yield() {
	// ucontext_t context_a; 
	// ucontext_t context_b; 
	// getcontext(&context_a);
	// context_a = runQ->headPointer->context = context_a;
	// rotQueue(runQ);
	// context_b = runQ->headPointer->context;
	// swapcontext(&context_a, &context_b);

	TCB_t *temp = runQ->headPointer; 
	rotateQ(runQ);
	swapcontext(&(temp->context), &(runQ->headPointer->context));
}

