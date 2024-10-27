#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#define SHMSZ 128
#define SHM_KEY 5678

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm;

    shmid = shmget(SHM_KEY, SHMSZ, IPC_CREAT | 0666);
    shm = shmat(shmid, NULL, 0);
    
    strcpy(shm,"003");
    exit(0);
}
