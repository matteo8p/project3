#include <stdio.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct sem *fullSem;
struct sem *emptySem; 

void newProducer(int id)
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(fullSem); 
        printf("\n Consumer %d is consuming item generated by Producer.", id); 
        P(emptySem); 
        i++; 
    }
}

void newConsumer(int id)
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(emptySem); 
        printf("\n Producer %d is consuming item generated by Consumer.", id); 
        i++; 
    }
}

int main()
{
    struct TCB_t *threads[P_num + C_num]; 

    fullSem = (struct sem*) malloc(sizeof(struct sem)); 
    emptySem = (struct sem*) malloc(sizeof(struct sem)); 

    InitSem(emptySem, 0); 
    InitSem(fullSem, B_num);
    InitQueue(&runQ); 


   	scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    for(int i = 0; i < P_num + C_num; i++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            start_thread(&newProducer, threads[i], id);
        }else if(id < 0)        //ID < 0, create consumer 
        {
            id = -id;           
            start_thread(&newConsumer, threads[i], id); 
        }
    }
}



