#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

#define SHMSZ 100

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Supply s for server, c for client as argument!");
        return 1;
    }

    int shm_id;
    key_t key = 123;

    if (shm_id = shmget(key, SHMSZ, 0666 | IPC_CREAT) < 0)
    {
        perror("Error on msgget!\n");
        return 1;
    }

    char *shm;

    if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1)
    {
        perror("Error on shmat");
        return 1;
    }

    if (argv[1][0] == 's')
    {
        printf("Enter message to send:");
        scanf("%[^$]", shm);
    }
    else
    {
        printf("Message received: %s", shm);
    }

    return 0;
}