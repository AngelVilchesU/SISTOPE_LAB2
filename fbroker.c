#include "fbroker.h"



int randomizer(int nroWorkers)
{
    return (rand()%nroWorkers);
}

int estaPid(int* arrPids, int largoArr, int pidBuscado)
{
    for (int i = 0; i < largoArr; i++)
    {
        if (pidBuscado == arrPids[i])
        {
            return 1;
        }
    }
    return 0;
}

void agregarPid(int* arrPids, int largoArr, int pidNuevo)
{
    for (int i = 0; i < largoArr; i++)
    {
        if (arrPids[i] == 0)
        {
            arrPids[i] = pidNuevo;
            break;
        }
    }
}

void inicializarArrEstatico(int* arrPids, int largoArr)
{
    for (int i = 0; i < largoArr; i++)
    {
        arrPids[i] = 0;
    }
}