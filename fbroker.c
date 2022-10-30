#include "fbroker.h"

// Entradas: Número entero (nro. de workers) considerado como el "límite"
// Salidas: // Número aleatorio entre 0 y el valor ingresado
// Descripción: Se genera y retorna un número aleatorio entre 0 y el valor ingresado
int randomizer(int nroWorkers)
{
    return (rand() % nroWorkers);
}

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
// Salidas: No considera
// Descripción: Se libera la memoria utlizada en la lista enlazada
void liberarLista(TDAlista *lista)
{
    free(lista);
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

// Entradas: Una lista enlazada y un año como entero "base"
// Salidas: No considera
// Descripción: Imprime por pantalla la información en cada nodo de la lista enlazada...
//              ... desde un año especifico (el ingresado)
void recorrerLista(TDAlista *lista, int anioBase)
{
    if (!esListaVacia(lista)) // Si no es lista vacia
    {
        nodo *aux = lista->inicio;
        while (aux != NULL) // Mientras no sea nulo
        {
            if (aux->anio >= anioBase) // Si el año del nodo es mayor/igual al año ingresado...
            {
                printf("Año %d\nJuego mas caro: %s %f\nJuego mas barato: %s %f\nPromedio de precios: %f\nWindows: %f%% Mac: %f%% Linux: %f%%\nJuegos gratis:\n%s",
                        aux->anio, aux->nombreJuegoMasCaro, aux->precioMasCaro, aux->nombreJuegoMasBarato, aux->precioMasBarato, aux->promedioPrecioJuegos,
                        aux->porcentajeW, aux->porcentajeMC, aux->porcentajeL, aux->juegosGratis);
            }
            aux = aux->siguiente; // Siguiente nodo
        }
    }
    else // Si es lista vacia
        printf("La lista está vacía\n");
}

// Entradas: Una lista enlazada y todos los datos de acuerdo a su estructura definida en fbroker.h
// Salidas: No considera
// Descripción: Dado los datos ingresados, estos son adicionados en un nuevo nodo de la lista enlazada ingresada
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
    if (!esListaVacia(lista)) // si la lista no es vacia...
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL) // Mientras no sea nula
        {
            if (auxiliar->anio == anio) // Si el año coincide
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
                return lista; // Finaliza el proceso y se retorna la lista enlazada actualizada
            }
            auxiliar = auxiliar->siguiente; // Siguiente elemento
        }
        return lista; // Retorno de la lista sin modificación (en caso de no existir año)
    }
    else // Es lista vacia
        return lista;
}

// Entradas: Una lista enlazada y un año
// Salidas: 1 si el años existe en la lista enlazada, 0 si no existe
// Descripción: Se evalua la existencia de un año en los nodos de la lista enlazada...
//              que coincida con el ingresado
int aniosEquivalentes(TDAlista *lista, int anio)
{
    if (!esListaVacia(lista)) // Si la lista no es vacia...
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL) // Mientras no sea nula
        {
            if (auxiliar->anio == anio) // Si los años coinciden
            {
                return 1; // retorna 1
            }
            auxiliar = auxiliar->siguiente; // Siguiente nodo
        }
        return 0;
    }
    else // Si la lista es vacia
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
char *strJuegoMasCaro(float valorA, char *juegoA, float valorB, char *juegoB)
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
char *strJuegoMasBarato(float valorA, char *juegoA, float valorB, char *juegoB)
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

// Entradas: Una lista enlazada, el flujo de escritura y un año
// Salidas: No considera
// Descripción: Dada la lista enlazada, su contenido es impreso en el flujo ingresado...
//              ...considerando un filtro de los años en cada nodo de la lista enlazada
void imprimirEnFlujoDesdeAnio(TDAlista *lista_enlace, FILE *flujo, int anioBase)
{
    nodo *aux = lista_enlace->inicio;
    while (aux != NULL)
    {
        if (aux->anio >= anioBase)
        {
            fprintf(flujo, "Año %d\nJuego mas caro: %s %f\nJuego mas barato: %s %f\nPromedio de precios: %f\nWindows: %f%% Mac: %f%% Linux: %f%%\nJuegos gratis:\n%s",
                    aux->anio, aux->nombreJuegoMasCaro, aux->precioMasCaro, aux->nombreJuegoMasBarato, aux->precioMasBarato, aux->promedioPrecioJuegos,
                    aux->porcentajeW, aux->porcentajeMC, aux->porcentajeL, aux->juegosGratis);
        }
        aux = aux->siguiente;
    }
}
