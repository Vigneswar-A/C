#include <stdio.h>
#include <stdlib.h>

void first_come_first_serve(int nrequests, int *request_sequence, int initial_head)
{
    int seek_time = 0;
    int current_head = initial_head;
    for (int i = 0; i < nrequests; i++)
    {
        seek_time += abs(request_sequence[i] - current_head);
        current_head = request_sequence[i];
    }
    printf("Seek Time: %d\n", seek_time);
}

void shortest_seek_time_first(int nrequests, int *request_sequence, int initial_head)
{
    int *finished = malloc(sizeof(int) * nrequests);
    int current_head = initial_head;
    int seek_time = 0;
    while (1)
    {
        int j = -1;
        for (int i = 0; i < nrequests; i++)
        {
            if (!finished[i] && (j == -1 || abs(current_head - request_sequence[i]) < abs(current_head - request_sequence[j])))
            {
                j = i;
            }
        }
        if (j != -1)
        {
            seek_time += abs(current_head - request_sequence[j]);
            current_head = request_sequence[j];
            finished[j] = 1;
        }
        else
        {
            break;
        }
    }

    free(finished);
}

int main(void)
{
    return 0;
}