#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DWORD WINAPI funcion_hilo(LPVOID lpParameter) {
    int valor = *((int *)lpParameter);

    printf("Hola mundo desde el hilo: %d\n", valor);

    Sleep(valor * 1000);

    return (DWORD)((valor + 1) * 100);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s nHilos\n", argv[0]);
        return EXIT_FAILURE;
    }

    int nHilos = atoi(argv[1]);

    if (nHilos <= 0) {
        fprintf(stderr, "El numero de hilos debe ser positivo.\n");
        return EXIT_FAILURE;
    }

    HANDLE *tablaHilos = calloc(nHilos, sizeof(HANDLE));
    int *valores = malloc(nHilos * sizeof(int));

    if (tablaHilos == NULL || valores == NULL) {
        fprintf(stderr, "Error reservando memoria.\n");
        free(tablaHilos);
        free(valores);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < nHilos; i++) {
        valores[i] = i;

        tablaHilos[i] = CreateThread(
            NULL,
            0,
            funcion_hilo,
            &valores[i],
            0,
            NULL
        );

        if (tablaHilos[i] == NULL) {
            fprintf(stderr, "Error creando hilo: %lu\n",
                    (unsigned long)GetLastError());

            for (int j = 0; j < i; j++) {
                WaitForSingleObject(tablaHilos[j], INFINITE);
                CloseHandle(tablaHilos[j]);
            }

            free(tablaHilos);
            free(valores);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < nHilos; i++) {
        WaitForSingleObject(tablaHilos[i], INFINITE);

        DWORD resultado;

        if (GetExitCodeThread(tablaHilos[i], &resultado)) {
            printf("El hilo %d termino con resultado: %lu\n",
                   i, (unsigned long)resultado);
        }

        CloseHandle(tablaHilos[i]);
    }

    free(tablaHilos);
    free(valores);

    return EXIT_SUCCESS;
}
