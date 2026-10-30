#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *env = getenv("LPRINTER");

    if (env == NULL) {
        printf("La variable LPRINTER no esta definida\n");
    } else {
        printf("LPRINTER=%s\n", env);
    }

    return 0;
}
