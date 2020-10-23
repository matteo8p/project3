#include "q.h" 

struct TCB_t *runQ; //Global header pointer

void start_thread(void (*function)(void), int id)
{ 
	void *stack;
	TCB_t *item;
	stack = malloc(8192);
	item = (TCB_t *)malloc(sizeof(TCB_t));
	init_TCB(item, function, stack, 8192, id);
	AddQueue(runQ,item);
}

void run()                                                      //Given code 
{	
    ucontext_t parent;	// get a place to store the main context, for
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(runQ->context));	// start the first thread
}

void yield() // similar to run
{
    TCB_t *prerotate = runQ; 
    RotateQ(&runQ);                                 //rotate the runq
    swapcontext(&(prerotate->context), &(runQ->context));  //swap context of old runq and current runq 
}


