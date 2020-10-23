#ifndef Q_H
#define Q_H

#include <stdlib.h>
#include <unistd.h>
#include "tcb.h"

typedef struct queue {
	struct TCB_t *header; // Pointer to 1st Element in Queue
} queue;

void initQueue(struct queue*);	
void addQueue(struct queue*, struct TCB_t*);	
void rotateQ(struct queue*);	
struct TCB_t* delQueue(struct queue*);	
struct TCB_t* newItem();	

void initQueue(struct queue *head) {
	head->header = NULL;
	return;
}

void addQueue(struct queue *head, struct TCB_t *item) {
	// Check for 0 elements in Queue
	if (head->header != NULL) {
		if (head->header->next != NULL) {

			item->prev = head->header->prev;
			item->next = head->header; 
			head->header->prev->next = item; 
			head->header->prev = item; 
		} else {
			head->header->next = item; 
			head->header->prev = item; 
			item->next = head->header; 
			item->prev = head->header; 
		}
	} else {
		head->header = item; 
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
	struct TCB_t *item = head->header;

	if (head->header != NULL) {
		if (head->header->next != NULL) {
			head->header->prev->next = head->header->next;
			head->header->next->prev = head->header->prev;
			head->header = head->header->next;
		} else {
			head->header = NULL;
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

#endif
