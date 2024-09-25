#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    if (pid == 0) {// Proceso hijo
        int fd_input = open("output.txt", O_RDONLY);
        int fd_output = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        
        if (dup2(fd_input,0) < 0) {
            perror("Error en dup2"); close(fd_input); return 0;
        } close(fd_input);
        
        if (dup2(fd_output,1) < 0) {
            perror("Error en dup2"); close(fd_output); return 0;
        } close(fd_output);



        char *args[] = {"./pp.exe", NULL};
        execv(args[0], args);
        
        
             
        
        
    } else {
        waitpid(pid, &status, 0);
    }

    return 0;
}

