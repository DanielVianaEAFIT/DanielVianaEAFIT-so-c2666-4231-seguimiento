#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Uso: ./saludo -h\n");
        printf("     ./saludo [-s|-d] <nombre>\n");
    }
    else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        printf("Hola %s\n", argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
        printf("Adios %s\n", argv[2]);
    }
    else {
        printf("Uso: ./saludo [-s|-d] <nombre>\n");
        return 1;
    }

    return 0;
}
