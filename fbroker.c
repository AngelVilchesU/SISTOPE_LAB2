#include "fbroker.h"

int randomizerWorker(char* nombreArchivoEntrada)
{
    FILE* dctoEntrada = fopen(nombreArchivoEntrada, "r");
    if (dctoEntrada == NULL)
    {
        printf("%s: error in input file named\n", nombreArchivoEntrada);
        exit(-1);
    }
    while (fgets(linea, largoChar, dctoEntrada))
    {
        
    }
    
    
    return 1;


}