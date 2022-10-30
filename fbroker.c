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

void recorrerLista(TDAlista *lista, int anioBase)
{
    if (!esListaVacia(lista))
    {

        nodo *aux = lista->inicio;
        while (aux != NULL)
        {
            if (aux->anio >= anioBase)
            {
                printf("Año %d\nJuego mas caro: %s\nJuego mas barato: %s\nPromedio de precios: %f\nWindows: %f%% Mac: %f%% Linux: %f%%\nJuegos gratis:\n%s",
                        aux->anio, aux->nombreJuegoMasCaro, aux->nombreJuegoMasBarato, aux->promedioPrecioJuegos,
                        aux->porcentajeW, aux->porcentajeMC, aux->porcentajeL, aux->juegosGratis);
            }
            aux = aux->siguiente;
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

void insertarInicio(TDAlista *lista, int anio, float precioMasCaro,
                    float precioMasBarato, char *nombreJuegoMasCaro,
                    char *nombreJuegoMasBarato, int contadorJuegos,
                    float sumaTotalJuegos, float promedioPrecioJuegos,
                    int contadorW, int contadorMC, int contadorL,
                    float porcentajeW, float porcentajeMC, float porcentajeL,
                    char *juegosGratis)
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

TDAlista *actualizarNodo(TDAlista *lista, int anio, float precioMasCaro,
                         float precioMasBarato, char *nombreJuegoMasCaro,
                         char *nombreJuegoMasBarato, int contadorJuegos,
                         float sumaTotalJuegos, float promedioPrecioJuegos,
                         int contadorW, int contadorMC, int contadorL,
                         float porcentajeW, float porcentajeMC, float porcentajeL,
                         char *juegosGratis)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (auxiliar->anio == anio)
            {
                // La información se actualiza en el nodo ya existente en la LE de acuerdo a los parámetros obtenidos
                // Puntos a considerar
                // Referente al año, ninguno

                // Referente al nombre del juego más caro, obtenerlo en la línea de código del precio más caro
                char auxStr[largoChar];
                strcpy(auxStr, auxiliar->nombreJuegoMasCaro);
                strcpy(auxiliar->nombreJuegoMasCaro, "");
                strcpy(auxiliar->nombreJuegoMasCaro, strJuegoMasCaro(auxiliar->precioMasCaro, auxStr, precioMasCaro, nombreJuegoMasCaro));

                // Referente al nombre del juego más barato, obtenerlo en la línea de código del precio más barato
                strcpy(auxStr, "");
                strcpy(auxStr, auxiliar->nombreJuegoMasBarato);
                strcpy(auxiliar->nombreJuegoMasBarato, "");
                strcpy(auxiliar->nombreJuegoMasBarato, strJuegoMasBarato(auxiliar->precioMasBarato, auxStr, precioMasBarato, nombreJuegoMasBarato));

                // Referente al precio más caro, comparar entre la info. obtenida y el nodo del mismo año (extraer el mayor)
                auxiliar->precioMasCaro = valorMayor(auxiliar->precioMasCaro, precioMasCaro);

                // Referente al precio más barato, comparar entre la info. obtenida y el nodo del mismo año (extraer el menor)
                auxiliar->precioMasBarato = valorMenor(auxiliar->precioMasBarato, precioMasBarato);

                // Referente al contador de juegos, se le suma 1 al nodo con juegos del mismo año (esta condición if)
                auxiliar->contadorJuegos++;

                // Referente a la suma total de juegos, sumar precio del juego existente en el nodo y el obtenido
                auxiliar->sumaTotalJuegos = auxiliar->sumaTotalJuegos + precioMasCaro; // Es lo mismo que precioJuego

                // Referente al promedio, calcularlo con el promedio existente y el precio obtenido
                auxiliar->promedioPrecioJuegos = promedio(auxiliar->promedioPrecioJuegos, promedioPrecioJuegos);

                // Referente al contador de juegos Windows, sumarlo en caso de que corresponda, lo mismo con MC y L
                if (contadorW)
                {
                    auxiliar->contadorW++;
                }
                if (contadorMC)
                {
                    auxiliar->contadorMC++;
                }
                if (contadorL)
                {
                    auxiliar->contadorL++;
                }

                // Referente al porcentaje de juegos Windows, calcular el promedio considerando que...
                // ...si existe se calcula el promedio con el dato de nodo y un 100% del obtenido, caso contrario...
                // ...se calcula el promedio con el dato de nodo y un 0% del obtenido, los mismo con MC y L
                auxiliar->porcentajeW = promedio(auxiliar->porcentajeW, porcentajeW);
                auxiliar->porcentajeMC = promedio(auxiliar->porcentajeMC, porcentajeMC);
                auxiliar->porcentajeL = promedio(auxiliar->porcentajeL, porcentajeL);

                // Referente a los juegos gratis, contatenar nombre del juego obtenido si es gratis con la línea ya...
                // ...existente en el nodo
                strcat(juegosGratis, "\n");
                strcat(auxiliar->juegosGratis, juegosGratis);

                // actualizarNodo

                return lista;
            }
            auxiliar = auxiliar->siguiente;
        }
        return lista;
    }
    else
        return lista;
}

int aniosEquivalentes(TDAlista *lista, int anio)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (auxiliar->anio == anio)
            {
                return 1;
            }
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

float valorMayor(float valorA, float valorB)
{
    if (valorA >= valorB)
    {
        return valorA;
    }
    return valorB;
}

float valorMenor(float valorA, float valorB)
{
    if (valorA <= valorB)
    {
        return valorA;
    }
    return valorB;
}

char *strJuegoMasCaro(float valorA, char *juegoA, float valorB, char *juegoB)
{
    if (valorA >= valorB)
    {
        return juegoA;
    }
    return juegoB;
}

char *strJuegoMasBarato(float valorA, char *juegoA, float valorB, char *juegoB)
{
    if (valorA <= valorB)
    {
        return juegoA;
    }
    return juegoB;
}

float promedio(float valorA, float valorB)
{
    return ((valorA + valorB) / 2);
}

void imprimirEnFlujoDesdeAnio(TDAlista *lista_enlace, FILE *flujo, int anioBase)
{
    nodo *aux = lista_enlace->inicio;
    while (aux != NULL)
    {
        if (aux->anio >= anioBase)
        {
            fprintf(flujo, "Año %d\nJuego mas caro: %s\nJuego mas barato: %s\nPromedio de precios: %f\nWindows: %f%% Mac: %f%% Linux: %f%%\nJuegos gratis:\n%s",
                    aux->anio, aux->nombreJuegoMasCaro, aux->nombreJuegoMasBarato, aux->promedioPrecioJuegos,
                    aux->porcentajeW, aux->porcentajeMC, aux->porcentajeL, aux->juegosGratis);
        }
        aux = aux->siguiente;
    }
}
