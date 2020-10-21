#include "tcb.h"

TCB_t *NewItem()              //Returns a new TCB object newItem 
{
   TCB_t *q = (TCB_t*)malloc(sizeof(TCB_t)); 
   q->next = NULL; 
   q->prev = NULL; 
   return q;        //Create newq and return the q  
}

void InitQueue(struct TCB_t **head)                    //Point empty queue(NULL) to head 
{
   *head = NULL;                             
}

void AddQueue(struct TCB_t **head, struct TCB_t *item) //adds a queue item, pointed to by "item", to the queue pointed by head 
{
   TCB_t *pointer = *head; 

   if(pointer == NULL)                                //If head is empty (NULL)   
   {
      *head = item;                                   //set head to item. Point to itself. 
      (*head)->next = *head; 
      (*head)->prev = *head;                       
   }else                                              //If head node exists 
   {
      pointer = (*head)->prev;                        //Pointer is the last element in queue 
      item->next = *head;  
      item->prev = pointer; 
      pointer->next = item; 
      (*head)->prev = item;                     
   }
}

struct TCB_t *DelQueue(struct TCB_t *head)      
{
   TCB_t *delq = head; 
   if(head == NULL || head->next == head)
   {
      head = NULL; 
      return delq; 
   }else
   {
      TCB_t *lastNode = head->prev; 
      head = head->next; 
      lastNode->next = head; 
      head->prev = lastNode; 
   }
   return delq; 
}

void RotateQ(struct TCB_t **head) 
{
   if(head == NULL)
   {
   	return; 
   } else
   {
   	TCB_t *t = *head; 
   	*head = t->next; 
   }
}
