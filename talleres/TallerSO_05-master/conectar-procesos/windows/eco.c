#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr,
                "Uso: %s <nombre-fichero> <cadena-traduccion> <linea-modulo-a-eliminar>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES saAttr;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        fprintf(stderr, "Error creando tuberia: %ld\n", GetLastError());
        return EXIT_FAILURE;
    }

    SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hWritePipe;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags = STARTF_USESTDHANDLES;

    ZeroMemory(&pi, sizeof(pi));

    char comando[2048];

    snprintf(comando, sizeof(comando),
             "C:\\msys64\\usr\\bin\\bash.exe -lc \"cat '%s' | tr -d '%s'\"",
             argv[1], argv[2]);

    if (!CreateProcess(NULL,
                       comando,
                       NULL,
                       NULL,
                       TRUE,
                       0,
                       NULL,
                       NULL,
                       &si,
                       &pi)) {

        fprintf(stderr,
                "Error creando proceso: %ld\n",
                GetLastError());

        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        return EXIT_FAILURE;
    }

    CloseHandle(hWritePipe);

    char buffer[4096];
    char linea[4096];

    DWORD bytesRead;

    int posicion = 0;
    int numeroLinea = 1;
    int modulo = atoi(argv[3]);

    if (modulo <= 0) {
        fprintf(stderr, "El modulo debe ser mayor que 0\n");
        CloseHandle(hReadPipe);
        return EXIT_FAILURE;
    }

    while (ReadFile(hReadPipe,
                    buffer,
                    sizeof(buffer),
                    &bytesRead,
                    NULL) &&
           bytesRead > 0) {

        for (DWORD i = 0; i < bytesRead; i++) {

            linea[posicion++] = buffer[i];

            if (buffer[i] == '\n' ||
                posicion >= (int)sizeof(linea) - 1) {

                linea[posicion] = '\0';

                if (numeroLinea % modulo != 0) {
                    printf("%s", linea);
                }

                numeroLinea++;
                posicion = 0;
            }
        }
    }

    if (posicion > 0) {

        linea[posicion] = '\0';

        if (numeroLinea % modulo != 0) {
            printf("%s", linea);
        }
    }

    CloseHandle(hReadPipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return EXIT_SUCCESS;
}
