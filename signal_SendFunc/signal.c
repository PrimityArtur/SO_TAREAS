#include <stdio.h>
#include <stdlib.h>   // Para atoi
#include <signal.h>   // Para señales
#include <unistd.h>   // Para kill

void killC(int,int);

//atoi = alfabetic 
int main(int argc, char *argv[]){
  int mi_sig = atoi(argv[1]);
  pid_t mi_pid = (pid_t)atoi(argv[2]);  
  killC(mi_pid, mi_sig);
  return 0;
}

void killC(pid_t pid, int signum){
    switch (signum) {
        case 2:
            if (kill(pid, SIGINT) == -1) { //interrupt
                perror("Error al enviar SIGINT");
                exit(1);
            }
            printf("SIGINT enviado al proceso %d\n", pid);
            break;
        case 10:
            if (kill(pid, SIGUSR1) == -1) {
                perror("Error al enviar SIGUSR1");
                exit(1);
            }
            printf("SIGUSR1 enviado al proceso %d\n", pid);
            break;
        case 12:
            if (kill(pid, SIGUSR2) == -1) {
                perror("Error al enviar SIGUSR2");
                exit(1);
            }
            printf("SIGUSR2 enviado al proceso %d\n", pid);
            break;
        case 18:
            if (kill(pid, SIGCONT) == -1) { //continue
                perror("Error al enviar SIGCONT");
                exit(1);
            }
            printf("SIGCONT enviado al proceso %d\n", pid);
            break;
        case 19:
            if (kill(pid, SIGSTOP) == -1) { //stop
                perror("Error al enviar SIGSTOP");
                exit(1);
            }
            printf("SIGSTOP enviado al proceso %d\n", pid);
            break;
        default:
            if (kill(pid, signum) == -1) { 
                printf("Error al enviar señal %d, al proceso %d\n",signum, pid);
                exit(1);
            }
            printf("Señal %d recibida, al proceso %d\n",signum, pid); 
            exit(1);
            break;
    } 
}
