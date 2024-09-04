#include <stdio.h>
#include <stdlib.h>   // Para atoi
#include <signal.h>   // Para señales
#include <unistd.h>   // Para kill

void receive(int);

int main() {
    int sig[] = {SIGINT, SIGUSR1, SIGUSR2, SIGTSTP, SIGCONT};
    for (int i = 0; i < sizeof(sig) / sizeof(sig[0]); i++) {
        if (signal(sig[i], receive) == SIG_ERR) {
            perror("Error al recibir señal");
        }
    }

    printf("PID %d Ejecutando...\n", getpid());
    while(1){
      pause();
    }

    return 0;
}

void receive(int signum) {
    switch (signum) {
        case SIGINT:
            printf("SIGINT (2) recibida.\n");
            break;
        case SIGUSR1:
            printf("SIGUSR1 (10) recibida.\n");
            break;
        case SIGUSR2:
            printf("SIGUSR2 (12) recibida.\n");
            break;
        case SIGCONT:
            printf("SIGCONT (18) recibida.\n");
            break;
        case SIGSTOP:
            printf("SIGSTOP (19) recibida.\n");
            break;
        case SIGTSTP:
            printf("SIGTSTP (20) recibida.\n");
            break;
        default:
            printf("Señal %d recibida.\n", signum);
    }
}
