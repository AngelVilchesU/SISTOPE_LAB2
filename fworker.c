#include "fworker.h"

// Entradas: No considera
// Salidas: Una lista enlazada nula (pero con memoria reservada)
// Descripción: Se reserva la memoria necesaria para generar una lista enlaza inicialmente vacia
TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

// Entradas: Una lista enlazada
// Salidas: 1 si la lista está vacia, caso contrario un 0
// Descripción: Se evalua la cabecera de la lista enlazada (nula o no) para determinar si es vacia o no
int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

// Entradas: Una lista enlazada y todos los datos de acuerdo a su estructura definida en fbroker.h
// Salidas: No considera
// Descripción: Dado los datos ingresados, estos son adicionados en un nuevo nodo de la lista enlazada ingresada
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

// Entradas: Una lista enlazada
// Salidas: No considera
// Descripción: Se elimina el primer nodo de la lista enlazada
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

// Entradas: Una lista enlazada
// Salidas: No considera
// Descripción: Se libera la memoria utlizada en la lista enlazada
void liberarLista(TDAlista* lista)
{
    free(lista);
}

// Entradas: Una lista enlazada y un año
// Salidas: 1 si el años existe en la lista enlazada, 0 si no existe
// Descripción: Se evalua la existencia de un año en los nodos de la lista enlazada...
//              que coincida con el ingresado
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

// Entradas: Dos valores flotantes (precios en dolares)
// Salidas: El valor mayor entre los ingresados
// Descripción: Se comparan los valores ingresados en búsqueda del mayor
float valorMayor(float valorA, float valorB)
{
    if (valorA >= valorB)
    {
        return valorA;
    }
    return valorB;
}

// Entradas: Dos valores flotantes (precios en dolares)
// Salidas: El valor menor entre los ingresados
// Descripción: Se comparan los valores ingresados en búsqueda del menor
float valorMenor(float valorA, float valorB)
{
    if (valorA <= valorB)
    {
        return valorA;
    }
    return valorB;
}

// Entradas: Dos valores flotantes (precios en dolares) asociados a nombres (de juego)
// Salidas: El nombre asociado al valor mayor
// Descripción: Se comparan los valores ingresados en búsqueda del mayor retornando su nombre asociado
char* strJuegoMasCaro(float valorA, char* juegoA, float valorB, char* juegoB)
{
    if (valorA >= valorB)
    {
        return juegoA;
    }
    return juegoB;
}

// Entradas: Dos valores flotantes (precios en dolares) asociados a nombres (de juego)
// Salidas: El nombre asociado al valor menor
// Descripción: Se comparan los valores ingresados en búsqueda del menor retornado su nombre asociado
char* strJuegoMasBarato(float valorA, char* juegoA, float valorB, char* juegoB)
{
    if (valorA <= valorB)
    {
        return juegoA;
    }
    return juegoB;
}

// Entradas: Dos valores flotantes
// Salidas: El promedio entre ambos
// Descripción: Se realiza y retorna el calculo del promedio entre los valores ingresados
float promedio(float valorA, float valorB)
{
    return ((valorA + valorB) / 2);
}

// Entradas: Una lista enlazada y todos los datos de acuerdo a su estructura definida en fbroker.h
// Salidas: Una lista enlazada actualizada
// Descripción: Dados los parámetros recibidos, estos con procesados en el nodo en el cual los años...
//              ...coincidan comparando la información existente y la información ingresada considerando...
//              ...los calculos necesarios dado el enunciado del laboratorio
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
                //strcat(juegosGratis, "\n");
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: Año del nodo
// Descripción: Se busca el nodo especifico retornando su año
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: precio más caro
// Descripción: Se busca el nodo especifico retornando su precio más caro
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: precio más barato
// Descripción: Se busca el nodo especifico retornando su precio más barato
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: nombre del juego más caro
// Descripción: Se busca el nodo especifico retornando el nombre del juego más caro
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: nombre del juego más barato
// Descripción: Se busca el nodo especifico retornando el nombre del juego más barato
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: contador de juegos
// Descripción: Se busca el nodo especifico retornando su contador de juegos
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: suma total de precios de juegos
// Descripción: Se busca el nodo especifico retornando la suma total de precios de juegos
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: promedio de precios de juegos
// Descripción: Se busca el nodo especifico retornando su promedio de precios de juegos
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: contador de juegos Windows
// Descripción: Se busca el nodo especifico retornando su contador de juegos Windows
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: contador de juegos Mac
// Descripción: Se busca el nodo especifico retornando su contador de juegos Mac
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: contador de juegos Linux
// Descripción: Se busca el nodo especifico retornando su contador de juegos Linux
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: porcentaje de juegos Windows
// Descripción: Se busca el nodo especifico retornando su porcentaje de juegos Windows
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: porcentaje de juegos Mac
// Descripción: Se busca el nodo especifico retornando su porcentaje de juegos Mac
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: porcentaje de juegos Linux
// Descripción: Se busca el nodo especifico retornando su porcentaje de juegos Linux
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

// Entradas: Una lista enlazada y una posición de nodo
// Salidas: String de juegos gratis
// Descripción: Se busca el nodo especifico retornando su string de juegos gratis
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

// Entradas: Una lista enlazada
// Salidas: largo de la lista enlazada
// Descripción: Se recorre la lista enlazada contabilizando sus nodos
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