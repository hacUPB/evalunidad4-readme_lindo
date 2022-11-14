#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#define Hilos 5


//Variable global, que representa el numero de tacos iniciales
int tacos = 100;

/*Estructura Mutex que mas adelante utilizaremos para utiizar Loc y Unlock de la variable local*/
pthread_mutex_t mxShared;


/*EL metodo Make Tacos sirve para aumentar el numero de tacos, o sea el productor*/
void* make_Tacos(void* args)
{
    //Un al que se entra si o si
    while(1)
    {
        //Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
        //Lo que permite usar el Lock para la variable Tacos
        pthread_mutex_lock(&mxShared);
        //Aumentamos la vairable tacos en 5
        tacos = tacos + 5;
        //Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
        //Lo que permite usar el unlock de la variable tacos
        pthread_mutex_unlock(&mxShared);
        //Luego imprimimos el numero de tacos que se hicieron
        printf("\n5 Tacos listos\n");
        //Sleep para parar el hilo 2 seg
        sleep(2);
        //Un condicional, en el que si hay mas de 300 tacos, termine el hilo
        if (tacos > 300)
        {
            //Retornar nulo, nos ayuda a salir del ciclo
            return NULL;
        }
    }
}

void* consume_Tacos(void* args)
{
    //Un ciclo al que siempre vamos a entrar
    while(1)
    {
        //Un condicional para solo disminuir los tacos si 
        if (tacos > 0)
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


        //Sleep para parar el hilo 2 seg
        sleep(2);

        if (tacos > 300)
        {
            //Retornar nulo, nos ayuda a salir del ciclo
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
