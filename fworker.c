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


int anioPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->anio;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

float precioMasCaroPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->precioMasCaro;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

float precioMasBaratoPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->precioMasBarato;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

char* nombreJuegoMasCaroPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->nombreJuegoMasCaro;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return NULL;
    }
    else
        return NULL;
}

char* nombreJuegoMasBaratoPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->nombreJuegoMasBarato;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return NULL;
    }
    else
        return NULL;
}

int contadorJuegosPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->contadorJuegos;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

float sumaTotalJuegosPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->sumaTotalJuegos;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

float promedioPrecioJuegosPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->promedioPrecioJuegos;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

int contadorWPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->contadorW;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

int contadorMACPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->contadorMC;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

int contadorLPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->contadorL;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0;
    }
    else
        return 0;
}

float porcentajeWPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->porcentajeW;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

float porcentajeMACPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->porcentajeMC;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

float porcentajeLPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->porcentajeL;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return 0.0;
    }
    else
        return 0.0;
}

char* juegosGratisPosicionLE(TDAlista * lista, int nodoEsp)
{
    if (!esListaVacia(lista))
    {
        int nodoAct = 0;
        nodo * auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            if (nodoAct == nodoEsp)
            {
                return auxiliar->juegosGratis;
            }
            nodoAct++;
            auxiliar = auxiliar->siguiente;
        }
        return NULL;
    }
    else
        return NULL;
}

int largoLE(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        int largo = 0;
        while (auxiliar != NULL)
        {
            largo++;
            auxiliar = auxiliar->siguiente;
        }
        return largo;
    }
    else
        return 0;
}