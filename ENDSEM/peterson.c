#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int flag[2];
int turn;

void *peterson(void *arg)
{
    int i = *(int *)(arg);
    int j = (!i);
    while (1)
    {
        flag[i] = 1;
        turn = j;
        while (flag[j] && turn == j)
            ;
        printf("Thread %d is now entering critical section!\n", i);
        printf("Thread %d is now executing critical section!\n", i);
        sleep(1);
        printf("Thread %d is now exiting critical section!\n", i);
        flag[i] = 0;
        sleep(rand() % 5);
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));
    flag[0] = 0;
    flag[1] = 0;

    pthread_t process_i, process_j;

    int i = 0;
    int j = 1;
    pthread_create(&process_i, NULL, peterson, &i);
    pthread_create(&process_j, NULL, peterson, &j);

    sleep(60);
    return 0;
}