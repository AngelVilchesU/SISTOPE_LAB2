#include "fworker.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char bff[300];
    char gigante[5000];
    int number = 0;
    int contador = 0;

    // no pescar este caso por el momento

    while (1)
    {
        read(STDIN_FILENO, &bff, sizeof(char) * 300);
        // read(STDIN_FILENO, &number, sizeof(int));
        if (strcmp(bff, "FIN") == 0)
        {

            // en este write ira todo lo procesado
            write(STDOUT_FILENO, &gigante, sizeof(char) * 5000);
            return 0;
        }
        else
        {
            sprintf(gigante, "Linea: %s\n", bff);
            contador++;
        }
    }

    return 0;
}