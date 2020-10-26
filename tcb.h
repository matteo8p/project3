#include <ucontext.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct TCB_t {
     struct TCB_t *next;
     struct TCB_t *prev;
     ucontext_t context;
};

void startThread(TCB_t *tcb, void *function, void *stack, int stack_size, int id) {
	memset(tcb, '\0', sizeof(TCB_t));      
	getcontext(&tcb->context);              
	tcb->context.uc_stack.ss_sp = stack;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 2, id);
}