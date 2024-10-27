#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

#define SEM_KEY 0x1111
#define SHM_KEY 5678
#define SHMSZ 128
#define LMIT_PRCESS 3

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

int main(int argc, char *argv[])
{
    int shmid = shmget(SHM_KEY, SHMSZ, 0666);
    char *shm = (char *)shmat(shmid, NULL, 0);
    
    int id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    union semun u;
    if(semctl(id, 0, GETPID, u) == 0){
        u.val = 1;
        semctl(id, 0, SETVAL, u);
    }
    
    int idP = atoi(argv[1]);
    char name[SHMSZ]; strcpy(name, argv[2]);
    char d[3] = {};
    while (atoi(d) < 1000) {
        semop(id, &p, 1);
        strncpy(d, shm, 3); 
        if (atoi(d) == idP) {
            snprintf(shm, SHMSZ, "%03d%s", idP + 1, name);
            idP += LMIT_PRCESS;
        }
        usleep(700000);
        semop(id, &v, 1);
    }
    
    semctl(id, 0, IPC_RMID, u);
    shmdt(shm);
    return 0;
}
