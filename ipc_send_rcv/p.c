#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int signo) {
    switch(signo) {
        case SIGINT:
            printf("Recibida señal SIGINT\n");
            break;
        case SIGUSR1:
            printf("Recibida señal SIGUSR1\n");
            break;
        case SIGUSR2:
            printf("Recibida señal SIGUSR2\n");
            break;
        case SIGCONT:
            printf("Recibida señal SIGCONT\n");
            break;
        case SIGTSTP:
            printf("Recibida señal SIGSTOP\n");
            kill(getpid(), SIGSTOP);
            break;
        default:
            printf("Señal desconocida\n");
    }
}

int main() {
    // Registrar manejadores de señal
    printf("PID = %d\n", getpid());
    
    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGCONT, signal_handler);
    signal(SIGTSTP, signal_handler);
    
    // Busy wait (espera activa)
    while(1) {
        pause(); // Esperar activamente las señales
    }
    
    return 0;
}

