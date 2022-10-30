#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Entradas: Valor número (0 o 1 como booleanos) que indican el ingreso (o no) de parámetros
// Salidas: No posee salida, sin embargo, la función finaliza sin problemas siempre y cuando...
//          ...se ingresen los parámetros minimos obligatorios (sin considerar bFlag)
// Descripción: Se evalua el correcto ingreso de los parámetros necesarios para las operaciones...
//              ...a realizar durante la ejecución de los procesos, en caso de faltar uno,...
//              ...el proceso es abortado, caso contrario continua su ejecución
void validacionArgsOPT(int iFlag, int oFlag, int dFlag, int pFlag, int nFlag, char* argv[])
{
    if (iFlag == 0) // Si no existe el nombre del archivo de entrada
    {
        fprintf(stderr, "%s: missing instruction -i flag parameter\n", argv[0]);
        exit(1);
    }
    if (oFlag == 0) // Si no existe el nombre del archivo de salida
    {
        fprintf(stderr, "%s: missing instruction -o flag parameter\n", argv[0]);
        exit(1);
    }
    if (dFlag == 0) // Si no existe el año de inicio del juego
    {
        fprintf(stderr, "%s: missing instruction -d flag parameter\n", argv[0]);
        exit(1);
    }
    if (pFlag == 0) // Si no existe el precio mínimo del juego
    {
        fprintf(stderr, "%s: missing instruction -p flag parameter\n", argv[0]);
        exit(1);
    }
    if (nFlag == 0) // Si no existe la cantidad de workers a generar
    {
        fprintf(stderr, "%s: missing instruction -n flag parameter\n", argv[0]);
        exit(1);
    }
}

// Entradas: Parámetros por consola/terminal en pantalla
// Salidas: No considera
// Descripción: Proceso principal del presente código que abarca hasta el punto de lógica 2
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
            case 'i': // Refiere al nombre del archivo de entrada
                iFlag = 1;
                nombreArchivoEntrada = optarg;
                break;
            case 'o': // Refiere al nombre del archivo de salida
                oFlag = 1;
                nombreArchivoSalida = optarg;
                break;
            case 'd': // Refiere al año desde el cual evaluar/considerar
                dFlag = 1;
                anioInicioJuego = optarg;
                break;
            case 'p': // Refiere al precio mínimo de juego/s
                pFlag = 1;
                precioMinimoJuego = optarg;
                break;
            case 'n': // Refiere a la cantidad de workers a generar
                nFlag = 1;
                cantidadWorkers = optarg;
                break;
            case 'b': // Indica si los datos de salida deben mostrarse (o no) por pantalla
                bFlag = 1;
                break;
            case '?': // Otro caso
                err = 1;
                break;
        }
    }
    /************************************ Lógica de solución - punto 2 ************************************/
    validacionArgsOPT(iFlag, oFlag, dFlag, pFlag, nFlag, argv); // Validación de los parámetros ingresados
    char bFlagStr[2];
    sprintf(bFlagStr, "%d", bFlag);    
    pid_t pidP;
    pidP = fork(); // Creación del proceso hijo
    int status;

    if (pidP > 0) // Si es el padre
    {
        wait(&status);
    }
    else if (pidP == 0) // Si es el hijo, se ejecuta execl con parámetros ingresados/validados
    {
        wait(&status);
        execl("./broker", nombreArchivoEntrada, nombreArchivoSalida, anioInicioJuego, precioMinimoJuego, cantidadWorkers, bFlagStr, NULL);
    }
    else // En caso de error por concepto de creación del proceso hijo
    {
        printf("Err\n");
        exit(1);
    }
    return 0; // Finaliza el proceso
}