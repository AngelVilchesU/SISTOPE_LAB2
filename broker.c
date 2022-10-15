#include "fbroker.h"

int main(int argc, char *argv[])
{
    printf("--------------\n");
    printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    printf("--------------\n");
    pid_t pidP;
    int status;
    for (int i = 0; i < atoi(argv[4]); i++)
    {
        pidP = fork();
        if (pidP > 0)
        {
            wait(&status);
        }
        else if (pidP == 0)
        {
            wait(&status);
            printf("Soy el hijo\n");
            execl("./worker", "./worker", NULL);
            exit(1);
        }
        else
        {
            printf("Err\n");
            exit(1);
        }
    }

    return 0;
}