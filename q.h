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
	struct queue *temp = head;
	if (temp->headPointer == NULL) {
		head->headPointer = item;
		(head)->headPointer->next = head->headPointer;
		(head)->headPointer->prev = head->headPointer;
	} else if (temp->headPointer->next == temp) {
		temp->headPointer->next = item;
		temp->headPointer->prev = item;
		item->next = temp;
		item->prev = temp;
	} else {
		while (temp->headPointer->next != head->headPointer)
			temp->headPointer = temp->headPointer->next;
		item->next = temp->headPointer->next;
		item->prev = temp->headPointer;
		temp->headPointer->next = item;
		(head)->headPointer->prev = item;
	}
	return;
}

void rotQueue(struct queue *head) {
	addQueue(head, delQueue(head));
	return;
}

struct TCB_t* delQueue(struct queue *head) {
	if(head->headPointer == NULL) return NULL; 

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

