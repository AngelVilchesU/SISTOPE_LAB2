#include "fbroker.h"

int randomizer(int nroWorkers)
{
    return (rand() % nroWorkers);
}

void leerYasignarWorker(char *nombreArchivoEntrada, int nroWorkers, TDAlista *listaEnlazada)
{
    int worker = 0;
    char linea[largoChar];
    FILE *dctoEntrada = fopen(nombreArchivoEntrada, "r");
    if (dctoEntrada == NULL)
    {
        printf("%s: error in input file named\n", nombreArchivoEntrada);
        exit(-1);
    }
    srand(time(NULL));
    while (fgets(linea, largoChar, dctoEntrada))
    {
        worker = randomizer(nroWorkers);
        insertarInicio(listaEnlazada, worker, linea);
    }

    recorrerLista(listaEnlazada);
    fclose(dctoEntrada);
}

// Entradas: void
// Salidas: Se retorna una lista del tipo TDAlista (lista enlazada)
// Descripción: Se inicializa un tipo de datos TDAlista otorgandole memoria inicial y una cabecera
TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

// Entradas: lista enlazada
// Salidas: void
// Descripción: Se libera la memoria dinamica empleada para la lista enlazada
void liberarLista(TDAlista *lista)
{
    free(lista);
}

// Entradas: Se ingresa una lista enlazada y un dato entero (posición de línea en documento)
// Salidas: void
// Descripción: Se reserva la memoria suficiente para lograr introducir un nuevo nodo
//              a la lista enlazada
void insertarInicio(TDAlista *lista, int nroWorker, char *linea)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->nroWorker = nroWorker;
    strcpy(nuevo->linea, linea);
    nuevo->puntero = lista->inicio;
    lista->inicio = nuevo;
}

// Entradas: Se ingresa una lista enlazada
// Salidas: Se retorna un valor entero que indica si una lista es vacia o no
// Descripción: Si la cabecera apunta a un nulo, entonces la lista enlazada está vacia,
//              caso contrarío, posee elementos/nodos
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
            printf("nroWorker: %d\n", auxiliar->nroWorker);
            printf("linea: %s\n", auxiliar->linea);
            auxiliar = auxiliar->puntero;
        }
        printf("\n");
    }
    else
        printf("La lista está vacía\n");
}

// Entradas: Se ingresa una lista enlazada
// Salidas: Se retorna el primer dato ubicado en la lista enlazada (del primer nodo, primer dato)
// Descripción: Si la lista enlazada no está vacia, se apunta al primer nodo y se retorna su valor
int existeNroWorker(TDAlista *lista, int nroWorker)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nroWorker == auxiliar->nroWorker)
            {
                return 1;
            }
            auxiliar = auxiliar->puntero;
        }
    }
    return 0;
}

// Función que permite calcular la cantidad de nodos que posee la lista enlazada
int longitud_nodos(TDAlista *listaEnlazada)
{
    nodo *aux = listaEnlazada->inicio;
    int longitud = 0;

    // Se recorren los nodos y mediante una variable contadora se determina el número de nodos
    while (aux != NULL)
    {
        longitud++;
        aux = aux->puntero;
    }
    return longitud;
}

int posicionNodo(TDAlista *listaEnlazada, int nroWorker)
{
    int posicion = 0;
    if (!esListaVacia(listaEnlazada))
    {
        nodo *auxiliar = listaEnlazada->inicio;
        while (auxiliar != NULL)
        {
            if (nroWorker == auxiliar->nroWorker)
            {
                return posicion;
            }
            posicion++;
            auxiliar = auxiliar->puntero;
        }
    }
    return -1;
}

// Función que permite eliminar un nodo en una posición especifíca
void eliminar_nodo_pos(TDAlista *listaEnlazada, int posicion)
{
    if (listaEnlazada->inicio)
    {
        if (posicion == 0)
        {
            nodo *remover_enlace = listaEnlazada->inicio;
            listaEnlazada->inicio = listaEnlazada->inicio->puntero;
            free(remover_enlace);
        }
        else if (posicion < longitud_nodos(listaEnlazada))
        {
            nodo *aux = listaEnlazada->inicio;
            int aux_pos = 0;
            while (aux_pos < (posicion - 1))
            {
                aux = aux->puntero;
                aux_pos++;
            }
            nodo *remover_enlace = aux->puntero;
            aux->puntero = remover_enlace->puntero;
            free(remover_enlace);
        }
    }
}

char *obtenerLineaPos(TDAlista *listaEnlazada, int posicion)
{
    int posicionAct = 0;
    nodo *auxiliar = listaEnlazada->inicio;
    while (auxiliar != NULL)
    {
        if (posicionAct == posicion)
        {
            return auxiliar->linea;
        }
        posicionAct++;
        auxiliar = auxiliar->puntero;
    }
    return NULL;
}