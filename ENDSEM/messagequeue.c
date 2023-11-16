#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Supply s for server, c for client as argument!");
        return 1;
    }

    int msg_id;
    key_t key = 123;

    if (msg_id = msgget(key, 0666 | IPC_CREAT) == -1)
    {
        perror("Error on msgget!\n");
        return 1;
    }

    char buff[100];

    if (argv[1][0] == 's')
    {
        printf("Enter message to send:");
        scanf("%[^$]", buff);
        msgsnd(msg_id, &buff, 100, 0);
    }
    else
    {
        msgrcv(msg_id, &buff, 100, 0, 0);
        printf("Message received: %s", buff);
    }

    return 0;
}