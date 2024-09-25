#include <stdio.h>

int main() {
    char buffer[256];
    for (int i = 0; i < 10; i++) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("%i: %s", i, buffer);
        } else {
            printf("No hay más entrada\n");
            break;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%i\n", i);
    }

    return 0;
}

