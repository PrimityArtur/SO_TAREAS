#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 0x1111

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

int main()
{
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    union semun u;
    if(semctl(id, 0, GETPID, u) == 0){
        u.val = 1;
        semctl(id, 0, SETVAL, u);
    }
    
    for (int i = 0; i < 10; ++i)
    {
        semop(id, &p, 1);
            for (int e = 0; e < 8000; ++e)
            {
                printf("line %d: %d\n",i,e);
                usleep(0.999);
            }
        semop(id, &v, 1);
    }
    
    semctl(id, 0, IPC_RMID, u);
    return 0;
}
