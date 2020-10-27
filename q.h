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
		if (head->headPointer != NULL) {
			// Queue is not empty, break chain and insert new item to end
			item->prev = head->headPointer->prev; // Add new link at end of chain
			item->next = head->headPointer; // Attach new link to beginning of chain
			head->headPointer->prev->next = item; // Make link from last element
			head->headPointer->prev = item; // Make link to end from head
		} else {
			// Queue has 1 element so create new chain
			head->headPointer->next = item; // Add new link to new item
			head->headPointer->prev = item; // Create chain linking to last element
			item->next = head->headPointer; // Create chain linking to first element
			item->prev = head->headPointer; // Add new link to old item
		}
	} else {
		// Queue is empty
		head->headPointer = item; // Make header point to new item
		item->prev = NULL; // Make pointer to NULL
		item->next = NULL; // Make pointer to NULL
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
		item->prev = item;
		item->next = item;
	}
	return item;
}