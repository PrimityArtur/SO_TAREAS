#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 128
#define SHM_KEY 5678
main()
{
    int shmid;
    key_t key;
    char *shm;

    if ((shmid = shmget(SHM_KEY, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    char preShm[SHMSZ] = "";
    while (1) {
        if (strcmp(shm, preShm) != 0) {
            printf("%s\n", shm);
            strcpy(preShm, shm);
        }
        usleep(5000);
    }
    
    exit(0);
}
