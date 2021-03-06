#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct semaphore *full; 
struct semaphore *empty; 

int in = 0; int out = 0; 

int* Buffer; 

void producer(); 
void consumer(); 

int main()
{   
    scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);

    full = (struct semaphore *)malloc(sizeof(struct semaphore)); 
    empty = (struct semaphore *)malloc(sizeof(struct semaphore)); 
    runQ = (struct queue*)malloc(sizeof(struct queue)); 

    initQueue(runQ); 
    initSem(full, 0); 
    initSem(empty, B_num); 

    Buffer = (int*)malloc(B_num * sizeof(int));

    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            startThread(producer, id);
        }else                   //ID < 0, create consumer 
        {                          
            startThread(consumer, id); 
        }
    }

    run(); 
    return 0; 
}

void producer(int id)
{
    int i = 0; 
    while(i < N_num) 
    {
        P(empty, id);

        printf("\n Producer %d is producing item number %d \n", id, i + 1); 
        Buffer[in] = id; 
        in = (in + 1) % B_num;

        V(full);
        i++; 
    }
    TCB_t *tcb = delQueue(runQ); 
    if(runQ->headPointer == NULL) exit(0); 
    swapcontext(&(tcb->context), &(runQ->headPointer->context)); 
}

void consumer(int id)
{
    int i = 0;
    while(i < N_num)
    {
        P(full, id); 
        printf("\n Consumer %d is consuming item generated by Producer %d \n", -id, Buffer[out]); 

        Buffer[out] = 0; 
        out = (out + 1) % B_num; 

        V(empty); 
        i++; 
    }
    TCB_t *tcb = delQueue(runQ); 
    if(runQ->headPointer == NULL) exit(0); 
    swapcontext(&(tcb->context), &(runQ->headPointer->context)); 
}




