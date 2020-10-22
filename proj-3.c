#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

int objectsInBuffer; 

struct TCB_t *BufferQueue; 
struct TCB_t *runQ; 
struct sem *S;

int buffQ[10000];
int head; 
int tail; 

void producer(); 
void consumer(); 

int main()
{   
    int head = 0; 
    int tail = 0; 

    objectsInBuffer = 0; 
    BufferQueue = (struct TCB_t*) malloc(sizeof(struct TCB_t)); 
    InitQueue(&BufferQueue); 

    runQ = (struct TCB_t*) malloc(sizeof(struct TCB_t)); 
    InitQueue(&runQ); 

   	scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    S = (struct sem*) malloc(sizeof(struct sem)); 
    InitSem(S, B_num);

    //printf("\n Buffer Size: %d # Producers: %d # Consumers: %d N: %d \n", B_num, P_num, C_num, N_num);   
    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            TCB_t newthread; 
            start_thread(&producer, &newthread, id);
        }else                   //ID < 0, create consumer 
        {  
            TCB_t newthread;
            id = -id;                                       
            start_thread(&consumer, &newthread, id); 
        }
    }
    run(); 
    return 0; 
}

void producer(int id)
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(S);
        int itemNumber = i + 1;
        //printf("%d", objectsInBuffer); 
        if(objectsInBuffer < B_num)
        {
            printf("\n Producer %d is producing item number %d\n", id, itemNumber); 
            buffQ[tail] = id; 
            tail++; 
            objectsInBuffer++; 
        }else
        {
            printf("\n Producer %d is waiting \n", id); 
        }
        V(S); 
        i++; 
    }
}

void consumer(int id)
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(S); 
        //printf("%d", objectsInBuffer); 
        if(objectsInBuffer > 0)
        {
            printf("\n Consumer %d is consuming item generated by Producer %d\n", id, buffQ[head]); 
            head++; 
            objectsInBuffer--; 
        }else
        {
            printf("\n Consumer %d is waiting\n", id); 
        }
        V(S); 
        //yield(); 
        i++; 
    }
}



