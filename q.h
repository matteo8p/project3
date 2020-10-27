#include <stdlib.h>
#include <unistd.h>
#include "tcb.h"

typedef struct queue {
	struct TCB_t *headPointer; // Pointer to 1st Element in Queue
} queue;

void initQueue(struct queue*);	
void addQueue(struct queue*, struct TCB_t*);	
void rotateQ(struct queue*);	
struct TCB_t* delQueue(struct queue*);	
struct TCB_t* newItem();	

void initQueue(struct queue *head) {
	head->headPointer = NULL;
	return;
}

void addQueue(struct queue *head, struct TCB_t *item) {
	if(head->headPointer == NULL)
	{
		head->headPointer = item; 
		head->headPointer->next = head->headPointer; 
		head->headPointer->prev = head->headPointer;
	}else
	{
		struct TCB_t *last = head->headPointer->prev; 
		last->next = item; 
		item->prev = last; 
		item->next = head->headPointer; 
		head->headPointer->prev = item; 
	}
	return;
}

void rotQueue(struct queue *head) {
	addQueue(head, delQueue(head));
	return;
}

struct TCB_t* delQueue(struct queue *head) {
	if(head->headPointer == NULL) return NULL; 
	struct TCB_t *deletedItem = head->headPointer; 

	if(deletedItem->next == deletedItem)
	{
		head->headPointer = NULL; 
	}else
	{
		struct TCB_t *last = head->headPointer->prev; 
		struct TCB_t *second = head->headPointer->next; 
		second->prev = last; 
		last->next = second; 
	}
	return deletedItem;
}

struct TCB_t* newItem() {
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
	return item;
}

