// ps -AF | egrep nombre_del_proceso.exe
#include <stdio.h> // fprintf()
#include <stdlib.h> // exit()
#include <string.h>
#include <unistd.h> // fork() pipe()
#include <sys/types.h>

#define MAX_LINE 256
void handle_error(const char*);

int main(void) {
    int fd1[2], fd2[2];
    pid_t childpid;

    // Crear dos pipes
    pipe(fd1); // Pipe para que el hijo envíe líneas al padre
    pipe(fd2); // Pipe para que el padre envíe la última enumeración al hijo

    if ((childpid = fork()) == -1) handle_error("fork");

    if (childpid == 0) { // Proceso hijo
        close(fd1[0]); // Cerrar el lado de lectura 
        close(fd2[1]); // Cerrar el lado de escritura

        FILE *inputFile = fopen("read.txt", "r");
        if (!inputFile) handle_error("Error al abrir read.txt");

        char line[MAX_LINE];
        while (fgets(line, sizeof(line), inputFile) != NULL) {
            write(fd1[1], line, strlen(line)); // Enviar la línea al padre
        }
        close(fd1[1]); // Cerrar escritura al terminar de enviar

        // Leer la última enumeración del padre
        char lastEnumeration[MAX_LINE];
        read(fd2[0], lastEnumeration, sizeof(lastEnumeration));

        FILE *outputFile = fopen("count.txt", "w");
        if (!outputFile) handle_error("Error al abrir el count.txt");
        
        fprintf(outputFile, "%s", lastEnumeration);
        fclose(outputFile);

        close(fd2[0]);
        fclose(inputFile);
        exit(0);
        
    } else { // Proceso padre
        close(fd1[1]); // Cerrar el lado de escritura 
        close(fd2[0]); // Cerrar el lado de lectura 

        FILE *outputFile = fopen("write.txt", "w");
        if (!outputFile) handle_error("Error al abrir write.txt");

        int lineCount = 1;
        char buffer[MAX_LINE];
        int bufferPos = 0;

        // Leer carácter por carácter para procesar líneas correctamente
        //lee un solo carácter desde el pipe (fd1[0]) y lo almacena en la posición buffer + bufferPos
        //El bucle continúa mientras read() devuelve un número positivo, indicando que se han leído caracteres correctamente.
        while (read(fd1[0], buffer + bufferPos, 1) > 0) {
            if (buffer[bufferPos] == '\n') {
                buffer[bufferPos + 1] = '\0';
                fprintf(outputFile, "%d: %s", lineCount++, buffer); // escritura
                bufferPos = 0; // Reiniciar buffer para la siguiente línea
            } else {
                bufferPos++;
            }
        }
        close(fd1[0]); // Cerrar el pipe de lectura después de recibir las líneas

        // Enviar la última enumeración al hijo
        char lastEnumeration[MAX_LINE];
        snprintf(lastEnumeration, sizeof(lastEnumeration), "%d\n", lineCount - 1);
        write(fd2[1], lastEnumeration, strlen(lastEnumeration)+1);
        
        close(fd2[1]); // Cerrar el pipe de escritura
        fclose(outputFile);
    }

    return 0;
}



void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
