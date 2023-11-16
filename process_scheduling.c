#include <stdio.h>
#include <stdlib.h>

void schedule(int *arrival, int *burst, int P, int Q)
{
    /* create required data structures */
    int time = 0;
    int *start = malloc(sizeof(int) * P);
    int *finish = malloc(sizeof(int) * P);
    int *remain = malloc(sizeof(int) * P);
    int pfinished = 0;

    /* initialise the arrays */
    for (int i = 0; i < P; i++)
    {
        start[i] = finish[i] = -1;
        remain[i] = burst[i];
    }

    /* simulate the cpu scheduling */
    while (pfinished < P)
    {
        /* level 1 - RR */

        /* find earliest process in ready queue and not yet given a chance */
        int current_process = -1;
        for (int i = 0; i < P; i++)
            if (start[i] == -1 && time >= arrival[i] && (current_process == -1 || arrival[i] < arrival[current_process]))
            {
                current_process = i;
                start[i] = time;
            }

        /* execute current process */
        if (current_process != -1)
        {

            /* execute for quantum or full burst which ever is lower */
            int cputime = (Q <= remain[current_process] ? Q : remain[current_process]);
            remain[current_process] -= cputime;
            time += cputime;

            /* process is finished */
            if (remain[current_process] == 0)
            {
                finish[current_process] = time;
                pfinished += 1;
            }
        }

        else
        {
            /* level 2 - FCFS */
            time += 1;

            /* find earliest arrived process that is in ready queue */
            int current_process = -1;
            for (int i = 0; i < P; i++)
                if (start[i] != -1 && time >= arrival[i] && remain[i] != 0)
                    current_process = ((current_process == -1 || start[i] < start[current_process]) ? i : current_process);

            /* execute the process for 1 clock cycle */
            if (current_process != -1)
            {
                remain[current_process] -= 1;

                /* process if finished */
                if (remain[current_process] == 0)
                {
                    finish[current_process] = time;
                    pfinished += 1;
                }
            }
        }
    }

    /* display the table */
    printf("Arrival    Burst    Start    Finish    Response    Waiting    TurnAround\n");
    for (int i = 0; i < P; i++)
    {
        printf("%-7d    %-5d    %-5d    %-6d    %-8d    %-7d    %-10d\n", arrival[i], burst[i], start[i], finish[i], start[i] - arrival[i], finish[i] - arrival[i] - burst[i], finish[i] - arrival[i]);
    }

    free(start);
    free(finish);
    free(remain);
}

int main(void)
{
    int Q;
    printf("Enter value of quanta for round robin:");
    scanf("%d", &Q);

    int P;
    printf("Enter the number of process:");
    scanf("%d", &P);

    int *arrival = malloc(sizeof(int) * P);

    printf("Enter Arrival Times:");
    for (int i = 0; i < P; i++)
        scanf("%d", &arrival[i]);

    int *burst = malloc(sizeof(int) * P);
    printf("Enter Burst Times:");
    for (int i = 0; i < P; i++)
        scanf("%d", &burst[i]);

    schedule(arrival, burst, P, Q);

    free(arrival);
    free(burst);

    return 0;
}