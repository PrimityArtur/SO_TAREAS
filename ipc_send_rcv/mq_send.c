#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h> 

struct mensaje {
    long tipo;
    int signal;
    int pid_p;
};

int main() {
    struct mensaje msg;
    key_t key = 1234;
    int msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Escriba pip de p: "); scanf("%d", &msg.pid_p);
    
    int opcion;
    while(1) {
        printf("Seleccione la señal a enviar:\n");
        printf("1. SIGINT 2\n");
        printf("2. SIGUSR1 10\n");
        printf("3. SIGUSR2 12\n");
        printf("4. SIGCONT 18\n");
        printf("5. SIGSTOP 19\n");
        printf("6. Salir\n");
        scanf("%d", &opcion);
        
        if (opcion == 6) break;
        switch(opcion) {
            case 1:
                msg.tipo = 1; msg.signal = SIGINT; break;
            case 2:
                msg.tipo = 1; msg.signal = SIGUSR1; break;
            case 3:
                msg.tipo = 1; msg.signal = SIGUSR2; break;
            case 4:
                msg.tipo = 2; msg.signal = SIGCONT; break;
            case 5:
                msg.tipo = 2; msg.signal = SIGTSTP; break;
            default:
                printf("Opción no válida\n"); continue;
        }

        msgsnd(msgid, &msg, sizeof(msg.signal) + sizeof(msg.pid_p), IPC_NOWAIT);
        printf("\nEnviado\n\n");
    }

    return 0;
}

