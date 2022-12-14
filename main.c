#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

/*

INTEGRANTES DEL EQUIPO README_LINDO:

-MATEO ARANGO
-JULIANA OLARTE
-FELIPE BARON

*/

// Definimos el numero de hilos que vamos a ejecutar
#define NumeroHilos 5

// Variable global, que representa el numero de tacos iniciales
int tacos = 100;

/*Estructura Mutex que mas adelante utilizaremos para utiizar Loc y Unlock de la variable local*/
pthread_mutex_t mxShared;

/*EL metodo Make Tacos sirve para aumentar el numero de tacos, o sea el productor*/
void *make_Tacos(void *args)
{

    // Un al que se entra si o si
    while (1)
    {

        // Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
        // Lo que permite usar el Lock para la variable Tacos
        pthread_mutex_lock(&mxShared);

        // Aumentamos la vairable tacos en 5
        tacos = tacos + 7;

        // Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
        // Lo que permite usar el unlock de la variable tacos
        pthread_mutex_unlock(&mxShared);

        // Luego imprimimos el numero de tacos que se hicieron
        printf("\nAcaban de salir 7 Tacos del Horno :D\n");

        // Sleep para parar el hilo 2 seg
        sleep(2);

        // Un condicional, en el que si hay mas de 160 tacos, termine el hilo
        if (tacos > 130)
        {

            // Retornar nulo, nos ayuda a salir del ciclo
            return NULL;
        }
    }
}

void *consume_Tacos(void *args)
{
    // Un ciclo al que siempre vamos a entrar
    while (1)
    {

        // Un condicional para solo disminuir los tacos si
        if (tacos > 0)
        {

            // Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
            // Lo que permite usar el Lock para la variable Tacos
            pthread_mutex_lock(&mxShared);

            // Disminuimos la variable Tacos en 1
            tacos = tacos - 1;

            // Un mutex al que se le manda la direccion de memoria de la estructura pthread_mutex_t
            // Lo que permite usar el unlock de la variable tacos
            pthread_mutex_unlock(&mxShared);

            // Imprimimos el numero de tacos que se vendieron
            printf("\nSe vendio 1 taco\n");

            // Sleep para parar el hilo 2 seg
            sleep(2);
        }
        else
        {
            // Si los tacos son 0 o menor que 0 se imprimir:
            printf("\nEspere por favor, estamos preparando los tacos\n");
        }

        if (tacos > 130)
        {
            // Retornar nulo, nos ayuda a salir del ciclo
            return NULL;
        }
    }
}

// un metodo que nos dir?? cuando hay de inventario de tacos
void *inventario_Tacos(void *args)
{

    // Un ciclo al que vamos a entrar
    while (1)
    {

        // Vamos a imprimir cuantos tacos hay
        printf("\nEn este momento hay: %i tacos en el inventario\n", tacos);
        // Luego vamos a dormir el ciclo 5 seg
        sleep(5);

        // Cuando los tacos sean mayores a 160
        if (tacos > 130)
        {
            // vamos a salir del inventario de tacos
            return NULL;
        }
    }
}

int main(int argc, char const *argv[])
{
    char a;
    printf("\n\n\n\n--Bienvenido a la taqueria ReadMe Lindo --\n\n");
    printf("Para ingresar 'y' || De lo contrario 'n'\n");
    scanf("%c", &a);

    if (a == 'y')
    {

        // Creamos los hilos, utilizando un Vector de Numero de hilos definido arriba
        pthread_t hilo[NumeroHilos];

        // Creamos cada hilo por aparte para que funcione:

        /*El primer Hilo va a ser el Hilo productor*/
        pthread_create(&hilo[0], NULL, &make_Tacos, NULL);

        /*este Hilo sera un consumidor*/
        pthread_create(&hilo[1], NULL, &consume_Tacos, NULL);

        /*este Hilo sera un consumidor*/
        pthread_create(&hilo[2], NULL, &consume_Tacos, NULL);

        /*este Hilo sera un consumidor*/
        pthread_create(&hilo[3], NULL, &consume_Tacos, NULL);

        // El 4to hilo nos dira cuantos tacos hay
        pthread_create(&hilo[4], NULL, &inventario_Tacos, NULL);

        /*Creamos un ciclo para hacer el Join de los hilos*/
        for (int i = 0; i < NumeroHilos; i++)
        {

            // Si el Hilo que estamos mirando, es != 0
            if (pthread_join(hilo[i], NULL) != 0)
            {
                // Se dara un error al hacer el join del hilo que estemos mirando
                perror("Failed to join (hilo %i) ");
            }
        }

        // Liberamos la memoria de &mxShared
        pthread_mutex_destroy(&mxShared);

        /*Lo siguiente es una forma de calificar*/
        printf("\n\n\n\n\nDesea Calificar su experiencia? (y/n) \n");
        char r;
        scanf("%c", &r);
        fflush(stdin);

        if (r == 'y')
        {
            printf("Por favor califique la experiencia del 1 al 5\n");

            int cal;
            scanf("%i", &cal);

            if (cal >= 3)
            {
                if (cal == 5)
                {
                    printf("Gracias por su visita, vuelva pronto\n");
                }
                else
                {
                    printf("Tomaremos en consideracion la calificacion para seguir mejorando nuesro servicio!\nVuelva pronto!");
                }
            }
            if (cal < 3)
            {
                printf("Sentimos que su experiencia no haya sido la ideal\nEstaremos mejorando nuestro servicio, gracias por su visita\n");
            }
        }
        else
        {
            printf("Gracias por su visita, vuelva pronto\n");
        }

        /*SI TODO SALE BIEN, EL PROGRAMA RETORNARA 0*/
        return 0;
    }
}
