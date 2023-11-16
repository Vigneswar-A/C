#include <stdio.h>
#include <stdlib.h>

void display(int *arrival, int *burst, int *start, int *finish, int nprocesses)
{
    int total_wait = 0;
    printf("Start        Finish        Wait\n");
    for (int i = 0; i < nprocesses; i++)
    {
        int wait = finish[i] - arrival[i] - burst[i];
        total_wait += wait;
        printf("%-5d        %-6d        %-4d\n", start[i], finish[i], wait);
    }
    printf("Average waiting time: %.2f\n", (float)total_wait / nprocesses);
}

void first_come_first_serve(int *arrival, int *burst, int nprocesses)
{
    int *start = malloc(sizeof(int) * nprocesses);
    int *finish = malloc(sizeof(int) * nprocesses);

    for (int i = 0; i < nprocesses; i++)
    {
        start[i] = -1;
        finish[i] = -1;
    }

    int remaining = nprocesses;
    int time = 0;

    while (remaining)
    {
        int j = -1;
        for (int i = 0; i < nprocesses; i++)
        {
            if (start[i] == -1 && arrival[i] <= time && (j == -1 || arrival[i] < arrival[j]))
            {
                j = i;
            }
        }

        if (j != -1)
        {
            start[j] = time;
            time += burst[j];
            finish[j] = time;
            remaining--;
        }
        else
        {
            time++;
        }
    }
    display(arrival, burst, start, finish, nprocesses);

    free(start);
    free(finish);
}

void shortest_remaining_time_first(int *arrival, int *burst, int nprocesses)
{
    int *start = malloc(sizeof(int) * nprocesses);
    int *finish = malloc(sizeof(int) * nprocesses);
    int *remain = malloc(sizeof(int) * nprocesses);

    for (int i = 0; i < nprocesses; i++)
    {
        start[i] = -1;
        finish[i] = -1;
        remain[i] = burst[i];
    }

    int remaining = nprocesses;
    int time = 0;

    while (remaining)
    {
        int j = -1;
        for (int i = 0; i < nprocesses; i++)
        {
            if (finish[i] == -1 && arrival[i] <= time && (j == -1 || remain[i] < remain[j]))
            {
                j = i;
            }
        }

        if (j != -1)
        {
            if (start[j] == -1)
            {
                start[j] = time;
            }

            remain[j] -= 1;
            time++;

            if (remain[j] == 0)
            {
                finish[j] = time;
                remaining--;
            }
        }
        else
        {

            time++;
        }
    }

    display(arrival, burst, start, finish, nprocesses);

    free(start);
    free(finish);
    free(remain);
}

void shortest_job_first(int *arrival, int *burst, int nprocesses)
{
    int *start = malloc(sizeof(int) * nprocesses);
    int *finish = malloc(sizeof(int) * nprocesses);

    for (int i = 0; i < nprocesses; i++)
    {
        start[i] = -1;
        finish[i] = -1;
    }

    int remaining = nprocesses;
    int time = 0;

    while (remaining)
    {
        int j = -1;
        for (int i = 0; i < nprocesses; i++)
        {
            if (finish[i] == -1 && arrival[i] <= time && (j == -1 || burst[i] < burst[j]))
            {
                j = i;
            }
        }

        if (j != -1)
        {
            start[j] = time;
            time += burst[j];
            finish[j] = time;
            remaining--;
        }
        else
        {
            time++;
        }
    }

    display(arrival, burst, start, finish, nprocesses);

    free(start);
    free(finish);
}

void round_robin(int *arrival, int *burst, int nprocesses)
{
    int *start = malloc(sizeof(int) * nprocesses);
    int *finish = malloc(sizeof(int) * nprocesses);
    int *queue_arrival = malloc(sizeof(int) * nprocesses);
    int *remain = malloc(sizeof(int) * nprocesses);

    int q;
    int end_time = -1;

    printf("Enter value of quanta for round robin:");
    scanf("%d", &q);

    for (int i = 0; i < nprocesses; i++)
    {
        start[i] = -1;
        finish[i] = -1;
        queue_arrival[i] = arrival[i];
        remain[i] = burst[i];
    }

    int remaining = nprocesses;
    int time = 0;

    while (remaining)
    {
        int j = -1;
        for (int i = 0; i < nprocesses; i++)
        {
            if (finish[i] == -1 && queue_arrival[i] <= time)
            {
                end_time = end_time < queue_arrival[i] ? queue_arrival[i] : end_time;
                if (j == -1 || queue_arrival[i] < queue_arrival[j] || (queue_arrival[i] == queue_arrival[j] && start[i] == -1))
                {
                    j = i;
                }
            }
        }

        if (j != -1)
        {
            if (start[j] == -1)
            {
                start[j] = time;
            }

            int cycles = q < remain[j] ? q : remain[j];
            remain[j] -= cycles;
            time += cycles;
            queue_arrival[j] = end_time + cycles;
            end_time = queue_arrival[j];

            if (remain[j] == 0)
            {
                finish[j] = time;
                remaining--;
            }
        }
        else
        {
            time++;
        }
    }

    display(arrival, burst, start, finish, nprocesses);

    free(start);
    free(finish);
    free(queue_arrival);
}

int main(void)
{
    int nprocesses;
    printf("Enter number of processes:");
    scanf("%d", &nprocesses);

    int *arrival = malloc(sizeof(int) * nprocesses);
    printf("Enter arrival times:");
    for (int i = 0; i < nprocesses; i++)
    {
        scanf("%d", &arrival[i]);
    }

    int *burst = malloc(sizeof(int) * nprocesses);
    printf("Enter burst times:");
    for (int i = 0; i < nprocesses; i++)
    {
        scanf("%d", &burst[i]);
    }

    first_come_first_serve(arrival, burst, nprocesses);
    shortest_job_first(arrival, burst, nprocesses);
    round_robin(arrival, burst, nprocesses);
    shortest_remaining_time_first(arrival, burst, nprocesses);

    free(arrival);
    free(burst);

    return 0;
}