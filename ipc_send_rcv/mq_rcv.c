#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXSIZE 128

struct mensaje {
    long tipo;
    int signal;
    int pid_p;
};

int msgid;

void *thread_tipo1() {
    struct mensaje msg;
    while (1) {
        msgrcv(msgid, &msg, MAXSIZE, 1, 0);
        kill(msg.pid_p, msg.signal);
        printf("Mensaje tipo 1: %d\n", msg.signal);
    }
}

void *thread_tipo2() {
    struct mensaje msg;
    while (1) {
        msgrcv(msgid, &msg, MAXSIZE, 2, 0);
        kill(msg.pid_p, msg.signal);
        printf("Mensaje tipo 2: %d\n", msg.signal);
    }
}

int main() {
    pthread_t tid1, tid2;
    
    key_t key = 1234;
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    pthread_create(&tid1, NULL, thread_tipo1, NULL);
    pthread_create(&tid2, NULL, thread_tipo2, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    return 0;
}

