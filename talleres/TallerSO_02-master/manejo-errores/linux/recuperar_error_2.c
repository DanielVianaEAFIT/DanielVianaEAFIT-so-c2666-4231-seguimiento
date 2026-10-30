#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void abrir_archivo(const char *nombre) {
    int estado = open(nombre, O_RDONLY);

    if (estado < 0) {
        fprintf(stderr, "Error abriendo %s debido a %d: %s\n",
                nombre, errno, strerror(errno));
        return;
    }

    printf("Archivo %s abierto correctamente\n", nombre);
    close(estado);
}

int main(void) {
    abrir_archivo("no-existe.txt");
    abrir_archivo("existe.txt");

    return 0;
}
