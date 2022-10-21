#include "fbroker.h"

int randomizer(int nroWorkers)
{
    return (rand() % nroWorkers);
}

/*------------- operaciones -------------*/
TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

void liberarLista(TDAlista* lista)
{
    free(lista);
}