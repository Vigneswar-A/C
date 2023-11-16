#include <stdio.h>
#include <stdlib.h>

void multiprocessor_schedule(int *burst, int nprocesses, int nprocessors)
{
    int *processors = malloc(sizeof(int) * nprocessors);
    int remaining = nprocesses;
    int *start = malloc(sizeof(int) * nprocesses);
    int *finish = malloc(sizeof(int) * nprocesses);
    int time = 0;

    for (int i = 0; i < nprocesses; i++)
    {
        start[i] = -1;
        finish[i] = -1;
    }

    for (int i = 0; i < nprocessors; i++)
    {
        processors[i] = -1;
    }
    while (remaining)
    {
        for (int i = 0; i < nprocesses; i++)
        {
            if (start[i] != -1)
            {
                continue;
            }
            for (int j = 0; j < nprocessors; j++)
            {
                if (processors[j] == -1)
                {
                    processors[j] = i;
                    break;
                }
            }
        }

        for (int i = 0; i < nprocessors; i++)
        {
            if (processors[i] == -1)
            {
                continue;
            }
            if (start[processors[i]] == -1)
            {
                start[processors[i]] = time;
            }
            burst[processors[i]]--;
            if (burst[processors[i]] == 0)
            {
                finish[processors[i]] = time + 1;
                processors[i] = -1;
                remaining--;
            }
        }

        time++;
    }

    printf("Turn Around Time\n");
    for (int i = 0; i < nprocesses; i++)
    {
        printf("%d\n", finish[i]);
    }

    free(processors);
    free(start);
    free(finish);
}

int main(void)
{
    int nprocesses;
    int nprocessors;

    printf("Enter number of processors:");
    scanf("%d", &nprocessors);

    printf("Enter number of processes:");
    scanf("%d", &nprocesses);

    int *burst = malloc(sizeof(int) * nprocesses);
    printf("Enter the burst times:");

    for (int i = 0; i < nprocesses; i++)
    {
        scanf("%d", &burst[i]);
    }

    multiprocessor_schedule(burst, nprocesses, nprocessors);

    free(burst);
    return 0;
}