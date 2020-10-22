#include <stdio.h>
#include "sem.h"

int B_num;      //Buffer size 
int P_num;      //# of producers
int C_num;      //# of consumers 
int N_num;      //# times they run their loops

struct TCB_t *runQ; 
struct sem *commonSem;

void producer(); 
void consumer(); 

void producer()
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(commonSem);
        printf("\n Producer is consuming item generated by Consumer.\n"); 
        V(commonSem); 
        //yield(); 
        i++; 
    }
}

void consumer()
{
    int i = 0; 
    while(i < N_num)            //Loop N times 
    {
        P(commonSem); 
        printf("\n Consumer is consuming item generated by Producer.\n"); 
        V(commonSem); 
        //yield(); 
        i++; 
    }
}

int main()
{
    struct TCB_t *threads[P_num + C_num]; 
    commonSem = (struct sem*) malloc(sizeof(struct sem)); 

    InitSem(commonSem, 0);

    printf("Insert 4 numbers: \n");
   	scanf("%d,%d,%d,%d",&B_num,&P_num,&C_num,&N_num);
    //printf("\n Buffer Size: %d # Producers: %d # Consumers: %d N: %d \n", B_num, P_num, C_num, N_num);   
    for(int k = 0; k < P_num + C_num; k++)
    {
        int id; 
        scanf("%d", &id);

        if(id > 0)              //ID > 0, create producer 
        {
            //printf("Added Producer\n"); 
            start_thread(producer, threads[k], id);
        }else       //ID < 0, create consumer 
        {  
            //printf("Added Consumer\n"); 
            start_thread(consumer, threads[k], id); 
        }
    }
    printf("\nInitiate RUN \n");
    run(); 
    return 0; 
}



