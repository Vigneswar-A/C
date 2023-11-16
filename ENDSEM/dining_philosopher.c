#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 5
sem_t forks[N];
sem_t mutex;

void takefork(int i)
{
    sem_wait(&forks[i]);
    sem_wait(&forks[(i + 1) % N]);
}

void putfork(int i)
{
    sem_post(&forks[i]);
    sem_post(&forks[(i + 1) % N]);
}

void *philosopher(void *arg)
{
    int i = *(int *)(arg);
    while (1)
    {
        sem_wait(&mutex);
        takefork(i);
        sem_post(&mutex);

        printf("Philosopher %d has taken the forks\n", i);
        sleep(rand() % 5);
        printf("Philosopher %d is now eating!\n", i);
        sleep(rand() % 5);
        printf("Philosopher %d has finished eating!\n", i);

        putfork(i);
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);

    pthread_t philosophers[N];
    int philosopher_indices[N];
    for (int i = 0; i < N; i++)
    {
        philosopher_indices[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_indices[i]);
    }

    sleep(60);

    return 0;
}
