#include <stdio.h>
#include <stdbool.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct TCB_t *runQ; 
struct sem *S;

void producer(); 
void consumer(); 

int main()
{
    runQ = (struct TCB_t*) malloc(sizeof(struct TCB_t)); 
    InitQueue(&runQ); 

    printf("Insert 4 numbers: \n");
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
        }else       //ID < 0, create consumer 
        {  
            TCB_t newthread;
            id = -id;                                       
            start_thread(&consumer, &newthread, id); 
        }
    }
    
    printf("\nInitiate RUN \n");
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
        
        if(B_num > 0)
        {
            printf("\n Producer %d is producing item number %d\n", id, itemNumber); 
            B_num--;
        }else
        {
            printf("\n Producer %d is waiting", id); 
            i--; 
        }
        
        V(S); 
        //yield(); 
        i++; 
    }
}

void consumer(int id)
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(S); 
        printf("\n Consumer %d is consuming item generated by Producer.\n", id); 
        B_num++; 
        V(S); 
        //yield(); 
        i++; 
    }
}



