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

void addQueue(struct queue* head, TCB_t* item) {
	TCB_t* temp = head;
	if (temp == NULL) {
		head = item;	
		head->headPointer->next = head->headPointer;
		head->headPointer->prev = head->headPointer;
	} else if (temp->next == temp) {		
		temp->next = item;
		temp->prev = item;
		item->next = temp;
		item->prev = temp;
	} else {
		while (temp->next != head)
			temp = temp->next;
		item->next = temp->next;
		item->prev = temp;
		temp->next = item;
		head->headPointer->prev = item;
	}
}

void rotQueue(struct queue *head) {
	addQueue(head, delQueue(head));
	return;
}

TCB_t* delQueue(struct queue* head) {
	TCB_t* del = head;
	if (del->next == del) {
		head->headPointer = NULL;
	} else {
		while (del->next != head) {
			del = del->next;
		}
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}
	return del;
}

struct TCB_t* newItem() {
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
	
	if (!item) {
		item->prev = NULL;
		item->next = NULL;
	}

	return item;
}

