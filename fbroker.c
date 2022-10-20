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

int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}
/*
void recorrerLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            printf("%d ", auxiliar->dato);
            auxiliar = auxiliar->siguiente;
        }
        printf("\n");
    }
    else
        printf("La lista está vacía\n");
}
*/
void insertarInicio(TDAlista *lista, int anio, int precioMasCaro, 
                    int precioMasBarato, char* nombreJuegoMasCaro,
                    char* nombreJuegoMasBarato, int contadorJuegos, 
                    int sumaTotalJuegos, float promedioPrecioJuegos, 
                    int contadorW, int contadorMC, int contadorL, 
                    float porcentajeW, float porcentajeMC, float porcentajeL,
                    char* juegosGratis)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->anio = anio;
    nuevo->precioMasCaro = precioMasCaro;
    nuevo->precioMasBarato = precioMasBarato;
    strcpy(nuevo->nombreJuegoMasCaro, nombreJuegoMasCaro);
    strcpy(nuevo->nombreJuegoMasBarato, nombreJuegoMasBarato);
    nuevo->contadorJuegos = contadorJuegos;
    nuevo->sumaTotalJuegos = sumaTotalJuegos;
    nuevo->promedioPrecioJuegos = promedioPrecioJuegos;
    nuevo->contadorW = contadorW;
    nuevo->contadorMC = contadorMC;
    nuevo->contadorL = contadorL;
    nuevo->porcentajeW = porcentajeW;
    nuevo->porcentajeMC = porcentajeMC;
    nuevo->porcentajeL = porcentajeL;
    strcpy(nuevo->juegosGratis, juegosGratis);
    nuevo->siguiente = lista->inicio;
    lista->inicio = nuevo;
}

void eliminarInicio(TDAlista *lista)
{
    nodo *auxiliar;
    if (!esListaVacia(lista))
    {
        auxiliar = lista->inicio;
        lista->inicio = lista->inicio->siguiente;
        free(auxiliar);
    }
}

void liberarLista(TDAlista* lista)
{
    free(lista);
}