#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
sem_t empty;
sem_t full;
sem_t mutex;

void *producer()
{
    int i = 0;
    while (1)
    {

        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[i % BUFFER_SIZE] = i;
        printf("Produced produced %d\n", i);
        sem_post(&mutex);
        sem_post(&full);
        i++;
        sleep(rand() % 5);
    }
}

void *consumer()
{
    int i = 0;
    while (1)
    {

        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumer Consumed %d\n", buffer[i % BUFFER_SIZE]);
        sem_post(&mutex);
        sem_post(&empty);
        i++;
        sleep(rand() % 5);
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_t pproducer, pconsumer;

    pthread_create(&pproducer, NULL, producer, NULL);
    pthread_create(&pconsumer, NULL, consumer, NULL);

    sleep(60);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}
