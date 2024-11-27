#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE "/dev/UCSP"
#define BUF_LEN 80

int main() {
    int fd = open(DEVICE, O_RDONLY);

    char buffer[BUF_LEN] = {0};
    char prev_buffer[BUF_LEN] = {0};

    while (1) {
        memset(buffer,0,BUF_LEN);
        read(fd, buffer, BUF_LEN);
        
        if (strcmp(buffer, prev_buffer) != 0) {
            printf("Dispositivo: %s\n", buffer);
            strcpy(prev_buffer, buffer);
        }
        usleep(5000); // Espera breve antes de la proxima lectura
    }

    close(fd);
    return 0;
}

