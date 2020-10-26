#include <stdlib.h>
#include <unistd.h>
#include "tcb.h"

void initQueue(struct TCB_t*);	
void addQueue(struct TCB_t*, struct TCB_t*);	
void rotateQ(struct TCB_t*);	
struct TCB_t* delQueue(struct TCB_t*);	
struct TCB_t* newItem();	

void initQueue(struct TCB_t *head) {
	head = NULL;
	return;
}

void addQueue(struct TCB_t *head, struct TCB_t *item) {
	// if(item == NULL) return; 

	if (head != NULL) {
		if (head->next != NULL) {
			item->prev = head->prev; 
			item->next = head; 
			head->prev->next = item; 
			head->prev = item; 
		} else {
			head->next = item; 
			head->prev = item; 
			item->next = head; 
			item->prev = head; 
		}
	} else {
		head= item; 
		item->prev = NULL; 
		item->next = NULL; 
	}
	return;
}

void rotQueue(struct TCB_t *head) {
	addQueue(head, delQueue(head));
	return;
}

struct TCB_t* delQueue(struct TCB_t *head) {
	struct TCB_t *item = head;
	if (head != NULL) {
		if (head->next != NULL) {
			head->prev->next = head->next;
			head->next->prev = head->prev;
			head = head->next;
		} else {
			head = NULL;
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


