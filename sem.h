// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 3
// Description: Holds the functions to create and modify Semaphores. InitSem(semaphore, value) initializes
//		a new Semaphore with the value equal to the parameter. P(semaphore) will decrement the value
//		and block the process if the value is less than zero. V(semaphore) will increment the value
//		and call the aprocess in the PCB and puts in the RunQ if the value is 0 or negative.

#ifndef SEM_H
#define SEM_H

//---------------//
// Include Files //
//---------------//
#include "threads.h"

//----------------------------//
// Data Structure Declaration //
//----------------------------//
typedef struct semaphore {
	int value;	// Holds the Semaphore value that is incremented & decremented
	struct queue *sleepQ;	// Stores the Queue to hold the blocked processes
} semaphore;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void initSem(semaphore*, int);
void P(semaphore*);
void V(semaphore*);

//----------------//
// initSem Method //
//----------------//
void initSem(semaphore *sem, int value) {
	// Allocate memory for the Sleep Queue
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));
	
	// Initialize the Head of the Sleep Queue
	initQueue(sem->sleepQ);

	// Initialize the value of the Semaphore
	sem->value = value;

	return;
}

//----------//
// P Method //
//----------//
//----------//
// P Method //
//----------//
void P(semaphore *sem) {
	// Declare a temporary TCB to hold the popped process
	struct TCB_t *p; 

	if (sem->value == 0) {
		printf("\n Blocked \n"); 
		p = delQueue(runQ);
		addQueue(sem->sleepQ, p);
		swapcontext(&(p->context), &(runQ->header->context));
	}else
	{
		sem->value--;
	}
}

//----------//
// V Method //
//----------//
void V(semaphore *sem) {
	struct TCB_t *t; 
	sem->value++;

	if (sem->value <= 0) {
		t = delQueue(sem->sleepQ);
		addQueue(runQ, t);
	}

	yield();
}

#endif
