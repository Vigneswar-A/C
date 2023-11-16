#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;
sem_t full;
sem_t empty;
int current_buffer = 0;

void *producer()
{
    while (1)
    {
        sleep(rand() % 2);
        sem_wait(&empty);
        sem_wait(&mutex);

        /* critical section start */
        printf("Producer produced an item, current buffer: %d\n", ++current_buffer);
        sem_post(&full);
        /* critical section end */

        sem_post(&mutex);
    }
}

void *consumer()
{
    while (1)
    {
        sleep(rand() % 2);
        sem_wait(&full);
        sem_wait(&mutex);

        /* critical section start */
        printf("Consumer consumed an item, current buffer: %d\n", --current_buffer);
        sem_post(&empty);
        /* critical section end */

        sem_post(&mutex);
    }
}

int main(void)
{
    int n;
    printf("Enter the buffer size:");
    scanf("%d", &n);

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);  // No. of buffer blocks full
    sem_init(&empty, 0, n); // No. of buffer blocks empty

    pthread_t pproducer, pconsumer;

    pthread_create(&pproducer, NULL, producer, NULL);
    pthread_create(&pconsumer, NULL, consumer, NULL);

    pthread_join(pconsumer, NULL);

    return 0;
}