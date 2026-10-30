#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Uso: %s <nombre-fichero> <cadena-traduccion> <linea-modulo-a-eliminar>\n", argv[0]);
        return 1;
    }

    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    pid_t cat_pid = fork();

    if (cat_pid == 0) {
        dup2(pipe1[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("cat", "cat", argv[1], NULL);
        perror("cat");
        exit(1);
    }

    pid_t tr_pid = fork();

    if (tr_pid == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("tr", "tr", "-d", argv[2], NULL);
        perror("tr");
        exit(1);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);

    FILE *entrada = fdopen(pipe2[0], "r");

    char linea[1024];
    int numeroLinea = 1;
    int eliminar = atoi(argv[3]);

    while (fgets(linea, sizeof(linea), entrada)) {
        if (numeroLinea % eliminar != 0) {
            printf("%s", linea);
        }
        numeroLinea++;
    }

    fclose(entrada);

    waitpid(cat_pid, NULL, 0);
    waitpid(tr_pid, NULL, 0);

    return 0;
}
