#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct TCB_t *runQ = NULL; 
struct sem *full; 
struct sem *empty; 

int buffer[10000];
int in = 0; int out = 0; 

void producer(); 
void consumer(); 

int main()
{   
    full = (struct sem *)malloc(sizeof(struct sem)); 
    empty = (struct sem *)malloc(sizeof(struct sem)); 

    InitSem(full, 0); 
    InitSem(empty, B_num); 

    InitQueue(&runQ); 

   	scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    struct TCB_t *threads[P_num + C_num];

    //printf("\n Buffer Size: %d # Producers: %d # Consumers: %d N: %d \n", B_num, P_num, C_num, N_num);   
    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            start_thread(producer, threads[k], id);
        }else                   //ID < 0, create consumer 
        {   
            id = -id;                                   
            start_thread(consumer, threads[k], id); 
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
        P(empty);
        int itemNumber = i + 1;
        printf("\n Producer %d is producing item number %d\n", id, itemNumber); 
        in = (in + 1) % B_num; 
        V(full); 
    }
}

void consumer(int id)
{
    for(int i = 0; i < N_num; i++)
    {
        P(full); 
        out = (out + 1) % B_num; 
        printf("\n Consumer %d is consuming item generated by Producer %d\n", id, out); 
        V(empty); 
        // yield(); 
    }
}



