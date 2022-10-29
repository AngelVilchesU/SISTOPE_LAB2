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

void liberarLista(TDAlista *lista)
{
    free(lista);
}

int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

void recorrerLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {

        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            printf("%d ", auxiliar->anio);
            printf("%f ", auxiliar->precioMasCaro);
            printf("%f ", auxiliar->precioMasBarato);
            printf("%s ", auxiliar->nombreJuegoMasCaro);
            printf("%s ", auxiliar->nombreJuegoMasBarato);
            printf("%d ", auxiliar->contadorJuegos);
            printf("%f ", auxiliar->sumaTotalJuegos);
            printf("%f ", auxiliar->promedioPrecioJuegos);
            printf("%d ", auxiliar->contadorW);
            printf("%d ", auxiliar->contadorMC);
            printf("%d ", auxiliar->contadorL);
            printf("%f ", auxiliar->porcentajeW);
            printf("%f ", auxiliar->porcentajeMC);
            printf("%f ", auxiliar->porcentajeL);
            printf("%s ", auxiliar->juegosGratis);
            auxiliar = auxiliar->siguiente;
        }
    }
    else
        printf("La lista está vacía\n");
}

/*
TDAlista *copyList(TDAlista *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {

        // Allocate the memory for new Node
        // in the heap and set its data
        struct  *nuevo = (struct nodoGenerico *)malloc(sizeof(struct nodoGenerico));

        //newNode->anio = head->data;

        nuevo->anio = head->anio;
        nuevo->precioMasCaro = head->precioMasCaro;
        nuevo->precioMasBarato = head->precioMasBarato;
        strcpy(nuevo->nombreJuegoMasCaro, head->nombreJuegoMasCaro);
        strcpy(nuevo->nombreJuegoMasBarato, head->nombreJuegoMasBarato);
        nuevo->contadorJuegos = head->contadorJuegos;
        nuevo->sumaTotalJuegos = head->sumaTotalJuegos;
        nuevo->promedioPrecioJuegos = head->promedioPrecioJuegos;
        nuevo->contadorW = head->contadorW;
        nuevo->contadorMC = head->contadorMC;
        nuevo->contadorL = head->contadorL;
        nuevo->porcentajeW = head->porcentajeW;
        nuevo->porcentajeMC = head->porcentajeMC;
        nuevo->porcentajeL = head->porcentajeL;
        strcpy(nuevo->juegosGratis, head->juegosGratis);

        // Recursively set the next pointer of
        // the new Node by recurring for the
        // remaining nodes
        nuevo->siguiente = copyList(head->siguiente);

        return nuevo;
    }
}
*/

