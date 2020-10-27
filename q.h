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
	TCB_t* temp = head->headPointer;
	if (temp == NULL) {
		head->headPointer = item;	
		head->headPointer->next = head->headPointer;
		head->headPointer->prev = head->headPointer;
	} else if (temp->next == temp) {		
		temp->next = item;
		temp->prev = item;
		item->next = temp;
		item->prev = temp;
	} else {
		while (temp->next != head->headPointer)
			temp = temp->next;
		item->next = head->headPointer;
		item->prev = temp;
		temp->next = item;
		head->headPointer->prev = item;
	}
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
	return (struct TCB_t*) malloc(sizeof(struct TCB_t));
}

