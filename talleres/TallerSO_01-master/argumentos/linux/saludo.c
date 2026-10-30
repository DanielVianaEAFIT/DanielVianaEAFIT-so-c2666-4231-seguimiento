#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opcion;

    while ((opcion = getopt(argc, argv, "hs:d:")) != -1) {
        switch (opcion) {
            case 'h':
                printf("Uso: ./saludo -h\n");
                printf("     ./saludo [-s|-d] <nombre>\n");
                return 0;
            case 's':
                printf("Hola %s\n", optarg);
                return 0;
            case 'd':
                printf("Adios %s\n", optarg);
                return 0;
            default:
                printf("Uso: ./saludo -h\n");
                printf("     ./saludo [-s|-d] <nombre>\n");
                return 1;
        }
    }

    if (argc == 2) {
        printf("Hola %s\n", argv[1]);
        return 0;
    }

    printf("Uso: ./saludo -h\n");
    printf("     ./saludo [-s|-d] <nombre>\n");
    return 1;
}

