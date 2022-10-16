#include "fbroker.h"

int main(int argc, char *argv[])
{
    printf("--------------\n");
    printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    printf("--------------\n");
    int arrPidsHijo[atoi(argv[4])];
    inicializarArrEstatico(arrPidsHijo, atoi(argv[4]));
    int worker = 0;
    char linea[largoChar];
    pid_t pidP;
    int status;
    int fd1[2]; // Primer pipe (0 refiere a lectura y 1 a escritura)
    int fd2[2]; // Segundo pipe
    pipe(fd1);
    pipe(fd2);

    

    for (int i = 0; i < (atoi(argv[4]) + 1); i++)
    {
        if (i < (atoi(argv[4])))
        {
            pidP = fork();
        }
        if (pidP > 0) // Es padre
        {
            wait(&status);

            if (i < atoi(argv[4]))
            {
                if (!estaPid(arrPidsHijo, atoi(argv[4]), (getpid() + i + 1)))
                {
                    agregarPid(arrPidsHijo, atoi(argv[4]), (getpid() + i + 1));
                }
            }
            else if (i == atoi(argv[4]))
            {
                FILE *dctoEntrada = fopen(argv[0], "r");
                if (dctoEntrada == NULL)
                {
                    printf("%s: error in input file named\n", argv[0]);
                    exit(-1);
                }
                srand(time(NULL));
                while (fgets(linea, largoChar, dctoEntrada))
                {
                    worker = randomizer(atoi(argv[4]));
                    printf("NUMERO RANDOM: %d\n", worker);

                    
                    //////////////////
                    // Pasar linea al hijo
                    /////////////////
                }

                fclose(dctoEntrada);
            }

            close(fd1[0]); // Se cierra el canal de lectura del primer pipe
            close(fd1[1]); // Se cierra el canal de escritura del primer pipe
            close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
            close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
        }
        else if (pidP == 0)
        {
            wait(&status);

            printf("GETPID DEL HIJO: %d\n", getpid());            // Indica el hijo
            printf("GETPPIND (PADRE) DEL HIJO: %d\n", getppid()); // Indica el padre

            close(fd1[1]); // Se cierra el canal de escritura del primer pipe
            close(fd1[0]); // Se cierra el canal de lectura del primer pipe
            close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
            close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
            execl("./worker", "./worker", NULL);

            exit(0);
        }
    }

    for (int i = 0; i < atoi(argv[4]); i++)
    {
        printf("%d -", arrPidsHijo[i]);
    }
    printf("\n");
    return 0;
}