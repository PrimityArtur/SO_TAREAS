#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define DEVICE "/dev/UCSP"

int main() {
    int fd = open(DEVICE, O_WRONLY);

    // Inicializa el contenido del dispositivo con "003"
    write(fd, "003", 3);

    printf("Dispositivo inicializado con '003'.\n");
    close(fd);
    return 0;
}

