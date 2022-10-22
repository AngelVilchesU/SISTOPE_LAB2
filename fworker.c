#include "fworker.h"

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
        printf("\n");
    }
    else
        printf("La lista está vacía\n");
}
*/
void insertarInicio(TDAlista *lista, int anio, float precioMasCaro, 
                    float precioMasBarato, char* nombreJuegoMasCaro,
                    char* nombreJuegoMasBarato, int contadorJuegos, 
                    float sumaTotalJuegos, float promedioPrecioJuegos, 
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

char* strJuegoMasCaro(float valorA, char* juegoA, float valorB, char* juegoB)
{
    if (valorA >= valorB)
    {
        return juegoA;
    }
    return juegoB;
}

char* strJuegoMasBarato(float valorA, char* juegoA, float valorB, char* juegoB)
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
                strcpy(auxiliar->nombreJuegoMasCaro, strJuegoMasCaro(auxiliar->precioMasCaro, auxiliar->nombreJuegoMasCaro, precioMasCaro, nombreJuegoMasCaro));
                
                // Referente al nombre del juego más barato, obtenerlo en la línea de código del precio más barato
                strcpy(auxiliar->nombreJuegoMasBarato, strJuegoMasBarato(auxiliar->precioMasBarato, auxiliar->nombreJuegoMasBarato, precioMasBarato, nombreJuegoMasBarato));
                
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