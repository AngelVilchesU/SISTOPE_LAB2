#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void validacionArgsOPT(int iFlag, int oFlag, int dFlag, int pFlag, int nFlag, char* argv[])
{
    if (iFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -i flag parameter\n", argv[0]);
        exit(1);
    }
    if (oFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -o flag parameter\n", argv[0]);
        exit(1);
    }
    if (dFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -d flag parameter\n", argv[0]);
        exit(1);
    }
    if (pFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -p flag parameter\n", argv[0]);
        exit(1);
    }
    if (nFlag == 0)
    {
        fprintf(stderr, "%s: missing instruction -n flag parameter\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    /************************************ Lógica de solución - punto 1 ************************************/
    char* nombreArchivoEntrada, * nombreArchivoSalida, * anioInicioJuego, * precioMinimoJuego, * cantidadWorkers;
    int iFlag = 0, oFlag = 0, dFlag = 0, pFlag = 0, nFlag = 0, bFlag = 0;
    int opt, err;
    while ((opt = getopt(argc, argv, "i:o:d:p:n:b")) != -1)
    {
        switch (opt)
        {
            case 'i':
                iFlag = 1;
                nombreArchivoEntrada = optarg;
                break;
            case 'o':
                oFlag = 1;
                nombreArchivoSalida = optarg;
                break;
            case 'd':
                dFlag = 1;
                anioInicioJuego = optarg;
                break;
            case 'p':
                pFlag = 1;
                precioMinimoJuego = optarg;
                break;
            case 'n':
                nFlag = 1;
                cantidadWorkers = optarg;
                break;
            case 'b':
                bFlag = 1;
                break;
            case '?':
                err = 1;
                break;
        }
    }
    validacionArgsOPT(iFlag, oFlag, dFlag, pFlag, nFlag, argv);
    printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\nbFlag: %d\n", nombreArchivoEntrada, nombreArchivoSalida, anioInicioJuego, precioMinimoJuego, cantidadWorkers, bFlag);
    
    /************************************ Lógica de solución - punto 2 y 3 ************************************/
    pid_t pidP;
    pidP = fork();
    int status;

    if (pidP > 0)
    {
        wait(&status);
    }
    else if (pidP == 0)
    {
        wait(&status);
        execl("./broker", nombreArchivoEntrada, nombreArchivoSalida, anioInicioJuego, precioMinimoJuego, cantidadWorkers, NULL);
    
    }
    else
    {
        printf("Err\n");
        exit(1);
    }
    
    

}