#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

sem_t rw_lock;
sem_t mutex;
int readers = 0;

void *writer()
{
    while (1)
    {
        sem_wait(&rw_lock);

        printf("writer is now writing!\n");
        sleep(1);

        sem_post(&rw_lock);
    }
}

void *reader(void *args)
{
    int i = *(int *)args;
    while (1)
    {
        sem_wait(&mutex);
        if (++readers == 1)
            sem_wait(&rw_lock);
        sem_post(&mutex);

        printf("reader %d is now reading!\n", i);

        sem_wait(&mutex);
        if (--readers == 0)
            sem_post(&rw_lock);
        sem_post(&mutex);
        sleep(1);
    }
}

int main(void)
{
    int n;
    printf("Enter number of readers:");
    scanf("%d", &n);

    sem_init(&rw_lock, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_t pwriter;
    pthread_t *readers = malloc(sizeof(pthread_t) * n);

    pthread_create(&pwriter, NULL, writer, NULL);

    for (int i = 0; i < n; i++)
    {
        int j = i;
        pthread_create(&readers[i], NULL, reader, &j);
    }

    pthread_join(pwriter, NULL);
    free(readers);

    return 0;
}