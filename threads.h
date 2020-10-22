#include "q.h" 

struct TCB_t *runQ; //Global header pointer

void start_thread(void (*function)(void), int id)
{ 
    void *stack = (void *)malloc(8192);                                 //Allocate stack of size 8192 
    TCB_t *thread = NewItem();                //Allocate a tcb via malloc 
    init_TCB(thread, function, stack, 8192, id);                       //Call init_tcb with arguments 
    AddQueue(runQ, thread);                                       //Add this tcb to global runQ
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


