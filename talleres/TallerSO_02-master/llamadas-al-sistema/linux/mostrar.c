#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE_BUFFER 1024

void mostrar_archivo(const char *nombre) {
    int fd = open(nombre, O_RDONLY);

    if (fd == -1) {
        perror(nombre);
        return;
    }

    char buffer[SIZE_BUFFER];
    ssize_t tam;

    while ((tam = read(fd, buffer, SIZE_BUFFER)) > 0) {
        ssize_t escritos = 0;

        while (escritos < tam) {
            ssize_t n = write(STDOUT_FILENO,
                              buffer + escritos,
                              tam - escritos);

            if (n <= 0) {
                perror("Error escribiendo");
                close(fd);
                return;
            }

            escritos += n;
        }
    }

    if (tam == -1) {
        perror("Error leyendo archivo");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s archivo1 [archivo2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        mostrar_archivo(argv[i]);
    }

    return 0;
}
