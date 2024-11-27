#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define DEVICE "/dev/UCSP"
#define SEM_KEY 0x1111
#define BUF_LEN 80
#define LMIT_PRCESS 3
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <id> <nombre>\n", argv[0]);
        return 1;
    }

    int idP = atoi(argv[1]);
    char *name = argv[2];
    
    int fd = open(DEVICE, O_RDWR);
    
    int sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    union semun u;
    if(semctl(sem_id, 0, GETPID, u) == 0){
        u.val = 1;
        semctl(sem_id, 0, SETVAL, u);
    }

    char buffer[BUF_LEN] = {0};
    char d[4] = {0};
    while (atoi(d) < 1000) {
        semop(sem_id, &p, 1); // Adquiere el semáforo

        lseek(fd, 0, SEEK_SET);
        read(fd, buffer, BUF_LEN);
        
        strncpy(d, buffer, 3);
        d[3]='\0';
        if (atoi(d) == idP) {
            snprintf(buffer, BUF_LEN, "%03d%s", idP + 1, name);            
            write(fd, buffer, strlen(buffer));
            idP += LMIT_PRCESS;
        }

        usleep(700000); // Espera breve antes de continuar
        semop(sem_id, &v, 1); // Libera el semáforo
    }

    close(fd);
    return 0;
}

