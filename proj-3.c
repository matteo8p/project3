#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct TCB_t *runQ = NULL; 
struct sem *full = NULL; 
struct sem *empty = NULL; 

int in = 0; int out = 0; 

int* Buffer; 

void producer(); 
void consumer(); 

int main()
{   
    scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    full = (struct sem *)malloc(sizeof(struct sem)); 
    empty = (struct sem *)malloc(sizeof(struct sem)); 

    InitQueue(&runQ); 

    
    InitSem(full, 0); 
    InitSem(empty, B_num); 

    Buffer = (int*)malloc(B_num * sizeof(int));

    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            TCB_t *newThread = NewItem(); 
            start_thread(producer, newThread, id);
        }else                   //ID < 0, create consumer 
        {   
            TCB_t *newThread = NewItem();   
            id = -id;                       
            start_thread(consumer, newThread, id); 
        }
    }
    printf("Running threads"); 
    run(); 
    return 0; 
}

void producer(int id)
{
    int i = 0; 
    for(int i = 0; i < N_num; i++) 
    {
        P(empty, id);
        int itemNumber = i + 1;
        printf("\n Producer %d is producing item number %d\n", id, itemNumber); 
        V(full, id);
        yield(); 
    }
}

void consumer(int id)
{
    for(int i = 0; i < N_num; i++)
    {
        P(full, id); 
        printf("\n Consumer %d is consuming item generated by Producer %d\n", id, 0); 
        V(empty, id); 
        yield(); 
    }
}



