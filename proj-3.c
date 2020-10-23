#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct sem *full; 
struct sem *empty; 
struct TCB_t *runQ = NULL; 

int in = 0; int out = 0; 

int* Buffer; 

void producer(); 
void consumer(); 

int main()
{   
    scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    full = (struct semaphore *)malloc(sizeof(struct semaphore)); 
    empty = (struct semaphore *)malloc(sizeof(struct semaphore)); 

    InitSem(full, 0); 
    InitSem(empty, B_num); 
    InitQueue(runQ); 

    Buffer = (int*)malloc(B_num * sizeof(int));

    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            TCB_t *newThread = NewItem(); 
            start_thread(producer, id);
        }else                   //ID < 0, create consumer 
        {   
            TCB_t *newThread = NewItem();   
            id = -id;                       
            start_thread(consumer, id); 
        }
    }
    printf("Running threads"); 
    run(); 
    return 0; 
}

void producer()
{
    int i = 0; 
    while(i < B_num) 
    {
        P(empty);
        int itemNumber = i + 1;
        printf("\n Producer %d is producing item number %d\n", id, itemNumber); 
        V(full);
        i++; 
    }
    //yield(); 
}

void consumer()
{
    int i = 0;
    while(i < B_num)
    {
        P(full); 
        printf("\n Consumer %d is consuming item generated by Producer %d\n", id, 0); 
        V(empty); 
        i++;
    }
    //yield(); 
}



