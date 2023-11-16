#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

sem_t chopsticks[5];
sem_t mutex;

void takechopsticks(int i)
{
    /* we need mutex to prevent taking only one chopstick */
    sem_wait(&mutex);

    /* take both left and right chopsicks */
    sem_wait(&chopsticks[i]);
    sem_wait(&chopsticks[(i + 1) % 5]);
    printf("Philosopher %d took the chopsticks 🍴 \n", i);

    /* unlock mutex so other philosophers can take chopsticks */
    sem_post(&mutex);
}

void putchopsticks(int i)
{
    /* NOTE: dont use mutex here, it will cause deadlock when one philosopher entered take chopsticks, but the chopsticks is not available */

    /*release the chopsticks*/
    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i + 1) % 5]);
    printf("Philosopher %d put the chopsticks 🍽️\n", i);
}

void *philosopher(void *arg)
{
    /*Get philosopher id from argument*/
    int i = *(int *)(arg);

    /*You can replace this forloop with infinite while loop if you want*/
    for (int j = 0; j < 3; j++)
    {
        printf("Philosopher %d is Hungry 😣 \n", i);
        takechopsticks(i);
        printf("Philosopher %d is eating 🍕 \n", i);
        sleep(1);
        printf("Philosopher %d has finished eating 😖\n", i);
        putchopsticks(i);
    }
}

int main()
{
    pthread_t philosophers[5];

    /* initialise all the semaphores */
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < 5; i++)
        sem_init(&chopsticks[i], 0, 1);

    for (int i = 0; i < 5; i++)
    {
        /* we need to dynamially allocate because the scope of static variable is within the for loop */
        int *j = malloc(sizeof(int));
        *j = i;

        pthread_create(&philosophers[i], NULL, philosopher, j);
    }
    for (int i = 0; i < 5; i++)
    {
        /* we need join so that program (main) dont exist before our threads are finished */
        pthread_join(philosophers[i], NULL);
    }
};
