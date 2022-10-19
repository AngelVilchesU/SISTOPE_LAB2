#include "fbroker.h"
#define llamado 0

int main(int argc, char *argv[])
{
    // printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    pid_t pidP;
    int status;
    int fd1[2]; // Primer pipe (0 refiere a lectura y 1 a escritura)
    int fd2[2]; // Segundo pipe (0 refiere a lectura y 1 a escritura)
    pipe(fd1);
    pipe(fd2);
    for (int i = 0; i < atoi(argv[4]); i++) // Creación de los hijos dados el número de workers
    {
        pidP = fork();
        if (pidP > 0) // Es padre
            continue;
        else if (pidP == 0) // Es hijo
        {
            break;
        }
        else // En caso de algún error
        {
            exit(-1);
        }
    }
    if (pidP > 0) // Si es padre
    {
        int worker = 0;                          // Valor que alude al worker
        char linea[largoChar];                   // Variable que contendrá las líneas del archivo leído
        char ordenFin[4] = "FIN";                // Orden para finalizar la espera de líneas de los hijos
        FILE *dctoEntrada = fopen(argv[0], "r"); // Se abre el archivo de entrada en modo lectura
        if (dctoEntrada == NULL)                 // En caso de algún error asociado a la no existencia del documento
        {
            printf("%s: error in input file named\n", argv[0]);
            exit(-1);
        }
        srand(time(NULL));                           // Inicialización de la semilla random
        close(fd1[0]);                               // Se cierra el canal de lectura del primer pipe
        while (fgets(linea, largoChar, dctoEntrada)) // Mientras no se hayan leído todas y cada una de las líneas del archivo de entrada
        {
            worker = randomizer(atoi(argv[4])); // Se llama a la función randomizer obteniendo un número aleatorio entre 0 y el nro. de workers
            printf("ASINAR VIA PIPE INFO AL WORKER %d\n", worker);
            char separadorLPid[largoChar] = "---";           // String que señala la separación entre la línea propia del contenido del archivo y el worker asignado
            char workerStr[largoChar];                       // Variable que alude al nro de worker como string
            sprintf(workerStr, "%d", getpid() + worker + 1); // Conversión del entero pid del hijo que alude al worker asignado a string
            strcat(linea, strcat(separadorLPid, workerStr)); // Concatenación de la línea del archivo de entrada y el worker asignado dada la sepación entre estos
            printf("Linea enviada al hijo: %s\n", linea);
            write(fd1[1], linea, strlen(linea) + 1); // Se escribe la concatenación anterior en el pipe correspondiente
            char lineaH[largoChar];
            read(fd2[0], lineaH, 300);   // Se lee lo retornado por el hijo
            if (strcmp(lineaH, "") == 0) // Si lo leído es nulo (el hijo no retornó ya que no le correspondia retornar)
            {
                while (strcmp(lineaH, "") == 0) // Se repite el proceso de envío y recepción al siguiente hijo
                {
                    write(fd1[1], linea, strlen(linea) + 1);
                    read(fd2[0], lineaH, 300);
                }
            }
            //printf("Linea recibida por el PADRE: %s\n", lineaH);
        }
        for (int j = 0; j < atoi(argv[4]); j++) // Se envía a todos y cada uno de los hijos la orden 'FIN'
        {
            write(fd1[1], ordenFin, strlen(ordenFin) + 1);
            wait(&status);
            read(fd2[0], linea, 300);
            
        }
        close(fd1[1]);       // Se cierra el canal de escritura del primer pipe
        close(fd2[1]);       // Se cierra el canal de escritura del segundo pipe
        close(fd2[0]);       // Se cierra el canal de lectura del segundo pipe
        fclose(dctoEntrada); // Se cierra el documento de entrada
    }
    else if (pidP == 0) // Si es hijo
    {
        close(fd1[1]); // Se cierra el canal de escritura del primer pipe
        dup2(fd1[1], STDOUT_FILENO);
        char buffer[9999] = "";
        while (1) // Se ingresa a un loop infinito hasta recibir la señal de salir 'FIN'
        {
            char lineaH[largoChar];              // Variable contenedora de lo recibido vía pipe
            char lineaHAux[largoChar];           // Auxiliar de la variable anterior
            char tokenAux[largoChar];            // Auxiliar del token por concepto de strtok
            read(fd1[0], lineaH, 300);           // Se lee el pipe
            char lineaHAux2[largoChar];          // Auxiliar
            char *token = strtok(lineaH, "---"); // separación de la línea recibida y el worker asignado
            strcpy(lineaHAux2, token);           // Respaldo
            token = strtok(NULL, "---");
            if (strcmp(lineaH, "FIN") == 0) // Si lo recibido corresponde a la orden 'FIN'
            {
                printf("HE RECIBIDO LA ORDEN DE FIN: %s\n", lineaH);
                write(fd2[1], "", 1);
                break;
            }
            else if (getpid() == atoi(token)) // Si el pid del hijo equivale al asignado dado el worker
            {
                printf("SOY EL HIJO LLAMADO. %d vs %d\n", getpid(), atoi(token));
                strcpy(tokenAux, token);                                          // Respaldo del token
                if ((strcmp(lineaH, "") > 0) && (strcmp(lineaH, lineaHAux) != 0)) // LineaH no es vacio y no se ha evaluado anteriormente
                {
                    strcpy(lineaHAux, lineaH); // Respaldo
                    strcat(buffer, strcat(lineaH, "---"));

                    strcat(lineaH, "---------------------------------------------->Modificacion por el hijo\n"); // Modificación
                    // printf("Linea modificada por el hijo: %s\n", lineaH);
                    write(fd2[1], lineaH, strlen(lineaH) + 1); // Se escribe vía pipe al padre
                }
            }
            else // El pid del presente hijo no era el asignado dado el worker
            {
                printf("NOOO SOY EL HIJO LLAMADO. %d vs %d\n", getpid(), atoi(token));
                write(fd2[1], "", 1);
                sleep(1); // Duerme
            }
        }
        execl("./worker", buffer, NULL);
        printf("SOY EL HIJO DE PID SALIENDO DEL WHILE%d\n", getpid());
        // printf("MI BUFFER ES %s\n", buffer);
        
        close(fd1[0]); // Se cierra el canal de lectura del primer pipe
        close(fd2[0]); // Se cierra el canal de lectura del segundo pipe
        close(fd2[1]); // Se cierra el canal de escritura del segundo pipe

        exit(0);
    }

    return 0;
}