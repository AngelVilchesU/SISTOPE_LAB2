#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define WRITE 1
#define READ 0

int main(int argc, char const *argv[])
{
    int nroWorker = 4, IDChild = 0;
    char *nombreArchivo = "datos_juegos.csv";
    pid_t pid;

    FILE *archivo = fopen(nombreArchivo, "r");

    int escrituraPipe[nroWorker][2], lecturaPipe[nroWorker][2];
    int status;

    for (int i = 0; i < nroWorker; i++)
    {
        pipe(escrituraPipe[i]);
        pipe(lecturaPipe[i]);
    }

    while (IDChild < nroWorker)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
        IDChild = IDChild + 1;
    }
    if (pid == 0)
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
        execl("worker", "worker", NULL);
    }
    else
    {
        char buff[500];
        char bff[5000];
        char linea[300];
        int random = 0;
        FILE *archivo = fopen("datos_juegos.csv", "r");

        for (int i = 0; i < nroWorker; i++)
        {
            close(lecturaPipe[i][READ]);
        }

        srand(time(NULL));
        int contador = 0;
        int flagFinal = 0;
        while (fgets(linea, 300, archivo) != NULL)
        {
            random = rand() % nroWorker;
            printf("numero random: %d\n", random);
            // sprintf(buff, "Linea: %s Hijo: %d\n", linea, random);
            write(lecturaPipe[contador][WRITE], &linea, sizeof(char) * 300);
            contador = contador + 1;
            // printf("COntador: %d\n", contador);
        }

        //FLAG FINAL
        for (int i = 0; i < nroWorker; i++)
        {
            write(lecturaPipe[i][WRITE], &flagFinal, sizeof(flagFinal));
        }

        //para que el printf del read no se quede pegado, al menos un worker tuvo que haber trabajado alguna linea
        //eso significa que hasta que el random funcione, la cantidad de workers, debe ser la misma que la cantidad de lineas del csv file
        //ESTO ES SOLO PARA DEMOSTRAR QUE LOS WORKER RECIBEN BIEN LO ENVIADO Y ENVIAN CORRECTAMENTE
        for (int i = 0; i < nroWorker; i++)
        {
            read(escrituraPipe[i][READ], &bff, sizeof(char) * 5000);

            printf("REspuesta del worker: %s\n", bff);
        }
    }

    return 0;
}
