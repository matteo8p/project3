#include <stdio.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct TCB_t *runQ; 
struct sem *fullSem;
struct sem *emptySem; 

void producer(); 
void consumer(); 

void producer()
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        printf("\n Consumer is consuming item generated by Producer.\n"); 
        i++; 
    }
}

void consumer()
{
    int j = 0; 
    while(j < N_num)            //Loop N times 
    {
        printf("\n Producer is consuming item generated by Consumer.\n"); 
        j++; 
    }
}

int main()
{
    struct TCB_t *threads[P_num + C_num]; 

    fullSem = (struct sem*) malloc(sizeof(struct sem)); 
    emptySem = (struct sem*) malloc(sizeof(struct sem)); 

    InitQueue(&runQ); 
    InitSem(emptySem, 0); 
    InitSem(fullSem, B_num);


    printf("Insert 4 numbers: \n");
   	scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    printf("\n Buffer Size: %d # Producers: %d # Consumers: %d N: %d \n", B_num, P_num, C_num, N_num);   
    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            printf("Added Producer"); 
            start_thread(producer, threads[k], id);
        }else if(id < 0)        //ID < 0, create consumer 
        {  
            printf("Added Consumer"); 
            start_thread(consumer, threads[k], id); 
        }
    }
    printf("\nInitiate RUN \n");
    run(); 
    return 0; 
}



