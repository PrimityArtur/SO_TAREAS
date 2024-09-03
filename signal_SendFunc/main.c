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
  if (kill(pid, signum) == -1){
    perror("Error al enviar la señal");
    return;
  }
  printf("Señal %d recibida, al proceso %d\n",signum, pid);  
}
