#include "fbroker.h"

int main(int argc, char *argv[])
{
    printf("--------------\n");
    printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    printf("--------------\n");
    pid_t pidP;
    int status;
    int fd1[2]; // Primer pipe (0 refiere a lectura y 1 a escritura)
    int fd2[2]; // Segundo pipe
    pipe(fd1);
    pipe(fd2);
    for (int i = 0; i < atoi(argv[4]); i++)
    {
        pidP = fork();
        if (pidP > 0)
        {
            wait(&status);
            close(fd1[0]); // Se cierra el canal de lectura del primer pipe
            close(fd1[1]); // Se cierra el canal de escritura del primer pipe
            close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
            close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
        }
        else if (pidP == 0)
        {
            wait(&status);
            randomizerWorker(argv[0]);
            close(fd1[1]); // Se cierra el canal de escritura del primer pipe
            close(fd1[0]); // Se cierra el canal de lectura del primer pipe
            close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
            close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
            execl("./worker", "./worker", NULL);
            exit(0);
        }
        else
        {
            printf("Err\n");
            exit(1);
        }
    }

    return 0;
}