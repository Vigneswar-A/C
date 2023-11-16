#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

sem_t seats;
sem_t barb;
sem_t mutex;
int NSEATS;
int currseats = 0;
int currcustomer;
int remaining = -1;

void *barber(void *arg)
{
    int sleeping = 0;
    while (remaining)
    {
        if (currseats == 0) // If seats are empty, then sleep
        {
            printf("Barber is sleeping... zZzZ\n");
            sleeping = 1;
        }
        sleep(2);

        /* wait until customer arrives at a seat */
        sem_wait(&seats);

        /*Critical Section*/
        sem_wait(&mutex);
        if (sleeping)
        {
            printf("Barber woke up after seeing %d\n", currcustomer);
            sleeping = 0;
        }
        sleep(2);
        printf("Barber is now cutting for customer %d\n", currcustomer);
        sleep(3);
        printf("Barber has finished cutting for customer %d\n", currcustomer);
        remaining--;
        sleep(2);
        sem_post(&barb);
        /*End of Critical Section*/

        sem_post(&mutex);
    }
}

void *customer(void *arg)
{
    int cid = *(int *)(arg);

    /* if seats are full just leave */
    if (currseats == NSEATS)
    {
        printf("Customer %d left as there is no empty seat!\n", cid);
        remaining--;
        return NULL;
    }

    /*wait until barber finishes cutting for current customer */
    currseats++;
    printf("Customer %d is now waiting in the waiting seat...\n", cid);
    sleep(2);
    sem_wait(&barb);

    sem_wait(&mutex);
    /*Critical Section*/
    printf("Customer %d is now in the cutting seat!\n", cid);
    sleep(2);
    currcustomer = cid;
    sem_post(&seats);
    /*End of Critical Section*/

    currseats--;
    sem_post(&mutex);
}

int main(void)
{
    int NCUSTOMERS;
    printf("Enter number of seats:");
    scanf("%d", &NSEATS);

    printf("Enter number of customers:");
    scanf("%d", &NCUSTOMERS);
    remaining = NCUSTOMERS;

    sem_init(&seats, 0, 0);
    sem_init(&barb, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_t pbarber;
    pthread_create(&pbarber, NULL, barber, NULL);

    pthread_t *pcustomers = malloc(sizeof(pthread_t) * NCUSTOMERS);
    for (int i = 0; i < NCUSTOMERS; i++)
    {
        sleep(rand() % 30);
        int j = i + 1;
        pthread_create(&pcustomers[i], NULL, customer, (void *)&j);
    }

    for (int i = 0; i < NCUSTOMERS; i++)
        pthread_join(pcustomers[i], NULL);

    pthread_join(pbarber, NULL);
    return 0;
}