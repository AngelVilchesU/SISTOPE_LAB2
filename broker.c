#include "fbroker.h"
#define llamado 0

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
        if (pidP > 0) // Es padre
            continue;
        else if (pidP == 0)
        {
            break;
        }
        else
        {
            exit(-1);
        }
    }

    if (pidP > 0) // Es padre
    {
        printf("SOY EL PADRE DE PID %d\n", getpid());

        int worker = 0;
        char linea[largoChar];
        char ordenFin[4] = "FIN";
        FILE *dctoEntrada = fopen(argv[0], "r");
        if (dctoEntrada == NULL)
        {
            printf("%s: error in input file named\n", argv[0]);
            exit(-1);
        }
        srand(time(NULL));



        close(fd1[0]); // Se cierra el canal de lectura del primer pipe
        while (fgets(linea, largoChar, dctoEntrada))
        {
            worker = randomizer(atoi(argv[4]));

            printf("ASINAR VIA PIPE INFO AL WORKER %d\n", worker);
            printf("Linea enviada al hijo: %s\n", linea);

            
            write(fd1[1], linea, strlen(linea) + 1);
            

            char lineaH[largoChar];
            read(fd2[0], lineaH, 300);
            printf("Linea recibida por el PADRE: %s\n", lineaH);
        }
        

        write(fd1[1], ordenFin, strlen(ordenFin) + 1);
        close(fd1[1]);
        close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
        close(fd2[0]); // Se cierra el canal de lectura del segundo pipe

        fclose(dctoEntrada);
    }
    else if (pidP == 0)
    {
        printf("SOY EL HIJO DE PID %d\n", getpid());
        close(fd1[1]); // Se cierra el canal de escritura del primer pipe
        while (1)
        {
            
            
            char lineaH[largoChar];
            char lineaHAux[largoChar];
            read(fd1[0], lineaH, 300);
            
            if (strcmp(lineaH, "FIN") == 0)
            {
                printf("HE RECIBIDO LA ORDEN DE FIN: %s\n", lineaH);
                break;
            }
            else if ((strcmp(lineaH, "") > 0) && (strcmp(lineaH, lineaHAux) != 0)) // LineaH no es vacio
            {   
                strcpy(lineaHAux, lineaH);
                strcat(lineaH, "---------------------------------------------->Modificacion por el hijo\n");
                printf("Linea modificada por el hijo: %s\n", lineaH);
                write(fd2[1], lineaH, strlen(lineaH) + 1);
            }
            
        }
        close(fd1[0]); // Se cierra el canal de lectura del primer pipe
        close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
        close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
        // execl("./worker", "./worker", NULL);
        exit(0);
    }

    return 0;
}