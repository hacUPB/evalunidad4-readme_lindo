#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#define Hilos 4



// Variable en la que se almacenan los tacos
int tacos = 0;

// Metodo para hacer tacos
void *make_tacos(void *args)
{
    while (1)
    {
        tacos = tacos + 5;
        sleep(7);
    }
    return NULL;
}

void *consume_taco(void *args)
{
    if (tacos != 0)
    {
        tacos = tacos - 2;
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t hilo[Hilos];

    pthread_create(&hilo[1], NULL, &make_tacos, NULL);
    
    while (1)
    {
        printf("tacos: %i",tacos);
        sleep(5);    
    }
    
    

    return 0;
}

//gcc -c -g -Wall main.c -o main.o
//gcc -g -Wall main.o -o eje