#include "fbroker.h"

int main(int argc, char *argv[])
{
    // printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    pid_t pidP;
    int IDChild = 0;
    int status;
    int escrituraPipe[atoi(argv[4])][2], lecturaPipe[atoi(argv[4])][2];
    for (int i = 0; i < atoi(argv[4]); i++)
    {
        pipe(escrituraPipe[i]);
        pipe(lecturaPipe[i]);
    }
    while (IDChild < atoi(argv[4]))
    {
        pidP = fork();
        if (pidP == 0)
        {
            break;
        }
        IDChild = IDChild + 1;
    }
    if (pidP == 0) // Si es hijo
    {
        if (dup2(lecturaPipe[IDChild][READ], STDIN_FILENO) == -1)
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }
        if (dup2(escrituraPipe[IDChild][WRITE], STDOUT_FILENO) == -1)
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }

        close(escrituraPipe[IDChild][READ]);
        close(lecturaPipe[IDChild][WRITE]);
        close(escrituraPipe[IDChild][WRITE]);
        close(lecturaPipe[IDChild][READ]);
        execl("./worker", "./worker", NULL);
    }
    else // Si es padre
    {
        for (int i = 0; i < atoi(argv[4]); i++)
        {
            close(lecturaPipe[i][READ]);
        }
        FILE *dctoEntrada = fopen(argv[0], "r"); // Se abre el archivo de entrada en modo lectura
        if (dctoEntrada == NULL)                 // En caso de algún error asociado a la no existencia del documento
        {
            printf("%s: error in input file named\n", argv[0]);
            exit(-1);
        }
        srand(time(NULL));
        char linea[largoChar]; // Variable que contendrá las líneas del archivo leído
        int random = 0;
        char ordenFin[4] = "FIN"; // Orden para finalizar la espera de líneas de los hijos
        char ordenContinuar[4] = "CON";
        char lineaRespuesta[largoChar]; // Variable que contendrá las líneas del archivo leído

        ///////////
        char buff[600];
        char bff[5000];
        char lineaFinal[400];
        char linea[300];
        char numero[50];
        ///////////
        while (fgets(linea, 300, dctoEntrada) != NULL)
        {
            random = randomizer(atoi(argv[4])); // Se llama a la función randomizer obteniendo un número aleatorio entre 0 y el nro. de workers
            printf("numero random: %d\n", random);
            ///////
            sprintf(numero, " Numero: %d\n", random);
            strcpy(lineaFinal,linea);
            strcat(lineaFinal, numero);
            //sprintf(lineaFinal, "Linea: %s ", linea);
            //printf("A: %s", lineaFinal);
            /////////
            write(lecturaPipe[contador][WRITE], &linea, sizeof(char) * largoChar);
        }

        for (int i = 0; i < atoi(argv[4]); i++)
        {
            write(lecturaPipe[i][WRITE], &ordenFin, sizeof(char) * 4);
        }
        for (int i = 0; i < atoi(argv[4]); i++)
        {
            read(escrituraPipe[i][READ], &lineaRespuesta, sizeof(char) * largoChar);

            printf("REspuesta del worker: %s\n", lineaRespuesta);
        }
    }
    return 0;
}