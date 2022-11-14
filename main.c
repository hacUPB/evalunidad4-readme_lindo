#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#define Hilos 5



int tacos = 100;

pthread_mutex_t mxShared;

void* make_Tacos(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&mxShared);
        tacos = tacos + 5;
        pthread_mutex_unlock(&mxShared);
        printf("\n5 Tacos listos\n");
        sleep(2);
        if (tacos > 300)
        {
        return NULL;
        }
    }
}

void* consume_Tacos(void* args)
{
    while(1)
    {
        if (tacos != 0)
        {
            pthread_mutex_lock(&mxShared);
            tacos = tacos - 1;
            pthread_mutex_unlock(&mxShared);
            printf("\nSe vendio 1 taco\n");
        }
        else
        {
            printf("\nEspere por favor, estamos preparando los tacos\n");
        }
        sleep(2);

        if (tacos > 300)
        {
        return NULL;
        }   
    }
}

void* inventario_Tacos(void* args)
{
    while(1)
    {
        sleep(5);
        printf("\nEn este momento hay: %i tacos en el inventario\n", tacos);
        if (tacos > 300)
        {
        return NULL;
        }
    }
    
}


int main(int argc, char const *argv[])
{
    pthread_t hilo[Hilos];
    



    pthread_create(&hilo[0], NULL, &make_Tacos, NULL);
    
    pthread_create(&hilo[1], NULL, &consume_Tacos, NULL);
    
    pthread_create(&hilo[2], NULL, &consume_Tacos, NULL);

    pthread_create(&hilo[3], NULL, &consume_Tacos, NULL);
    
    pthread_create(&hilo[4], NULL, &inventario_Tacos, NULL);

    
    for (int i = 0; i < Hilos; i++)
    {
        if(pthread_join(hilo[i],NULL) != 0)
        {
            perror("Failed to join");
        }
    }
    

    pthread_mutex_destroy(&mxShared);
    return 0;
}
