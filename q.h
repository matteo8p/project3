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
	// Check for 0 elements in Queue
	if (head->headPointer != NULL) {
		if (head->headPointer->next != NULL) {

			item->prev = head->headPointer->prev;
			item->next = head->headPointer; 
			head->headPointer->prev->next = item; 
			head->headPointer->prev = item; 
		} else {
			head->headPointer->next = item; 
			head->headPointer->prev = item; 
			item->next = head->headPointer; 
			item->prev = head->headPointer; 
		}
	} else {
		head->headPointer = item; 
		item->prev = NULL; 
		item->next = NULL; 
	}
	
	return;
}

void rotQueue(struct queue *head) {
	addQueue(head, delQueue(head));
	return;
}

struct TCB_t* delQueue(struct queue *head) {
	struct TCB_t *item = head->headPointer;

	if (head->headPointer != NULL) {
		if (head->headPointer->next != NULL) {
			head->headPointer->prev->next = head->headPointer->next;
			head->headPointer->next->prev = head->headPointer->prev;
			head->headPointer = head->headPointer->next;
		} else {
			head->headPointer = NULL;
		}
	}
	
	return item;
}

struct TCB_t* newItem() {
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
	
	if (!item) {
		item->prev = NULL;
		item->next = NULL;
	}

	return item;
}

