#include <windows.h>
#include <stdio.h>

#define SIZE_BUFFER 1024

int main(int argc, char *argv[]) {
    HANDLE archivo;
    HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
    char buffer[SIZE_BUFFER];
    DWORD leidos, escritos;

    if (argc < 2) {
        printf("Uso: mostrar archivo1.txt archivo2.txt ...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        archivo = CreateFileA(argv[i], GENERIC_READ, FILE_SHARE_READ,
                              NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (archivo == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Error abriendo %s: %lu\n",
                    argv[i], GetLastError());
            continue;
        }

        while (ReadFile(archivo, buffer, SIZE_BUFFER, &leidos, NULL)
               && leidos > 0) {
            if (!WriteFile(salida, buffer, leidos, &escritos, NULL)) {
                fprintf(stderr, "Error mostrando %s\n", argv[i]);
                break;
            }
        }

        CloseHandle(archivo);
    }

    return 0;
}
