#include <stdio.h>

int main(void)
{
    int n;
    printf("Enter number of request tracks:");
    scanf("%d", &n);

    int max = -1;
    printf("Enter the sequence of tracks:");

    for (int i = 0; i < n; i++)
    {
        int j;
        scanf("%d", &j);

        if (j > max)
            max = j;
    }

    int head;
    printf("Enter current header position:");
    scanf("%d", &head);

    printf("Total seek time: %d", max + head);
}