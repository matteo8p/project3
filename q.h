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
	// if(item == NULL) return; 

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
	if (item->next == item) {
		head = NULL;
	} else {
		item = item->prev; 
		item->prev->next = item->next;
		item->next->prev = item->prev;
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

void printQueue(struct TCB_t *head)
{
	if (head == NULL) {
		puts("queue head is null");
		return;
	}

	if (head->next == head) {
		printf("\t%p\n", head);
	} else {
		struct TCB_t *current = head;
		do {
			printf("\t%p\n", current);
			current = current->next;
		} while (current != head);
	}
}

