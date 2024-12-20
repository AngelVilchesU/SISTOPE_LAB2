#include "fworker.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Entradas: No considera, a excepción de la información entregada vía PIPES
// Salidas: No considera
// Descripción: Proceso principal del presente código que abarca desde el punto de lógica...
//              ...8 hasta el punto de lógica 12
int main()
{
    char buffer[largoChar]; // Recibe lo entregado vía PIPE
    int contador = 0; // Contador de líneas evaluadas
    // Posiciones en la linea dada información entregada
    int posicionFinal = 10;
    int posicionEsL = 9;
    int posicionEsMC = 8;
    int posicionEsW = 7;
    int posicionEsGratis = 6;
    int posicionAnio = 5;
    int posicionPrecio = 3;
    int posicionNombreJuego = 1;
    float sumaTotalJuegos = 0;
    TDAlista *LE = crearListaVacia(); // Creación de lista enlazada para almacenar los resultados/calculos abarcados
    /************************************ Lógica de solución - punto 8 ************************************/
    while (1) // Ciclo infinito hasta recibir la orden 'FIN'
    {
        read(STDIN_FILENO, &buffer, sizeof(char) * 300); // Se lee una línea entregada
        /************************************ Lógica de solución - punto 11 ************************************/
        if (strcmp(buffer, "FIN") == 0) // Si dicha línea corresponde a la orden 'FIN'
        {
            // Cantidad de nodos procesados
            int largo = largoLE(LE); 
            write(STDOUT_FILENO, &largo, sizeof(int)); // Se envía los nodos existentes en la lista enlazada (largo)
            /************************************ Lógica de solución - punto 10 ************************************/
            write(STDOUT_FILENO, &contador, sizeof(int)); // Se envía la cantidad de líneas evaluadas
            if (contador != 0) // Si existen nodos por evaluar
            {
                for (int i = 0; i < contador; i++) // Por cada nodo en la lista enlazada
                {
                    for (int j = 0; j < nroElementosStruct; j++) // Por cada elemento del nodo de la lista enlazada, se envía la información al broker
                    {
                        if (j == 0) // Refiere al año
                        {
                            int anio = anioPosicionLE(LE, i);
                            write(STDOUT_FILENO, &anio, sizeof(int));
                        }
                        else if (j == 1) // Refiere al precio más caro
                        {
                            float precioMasCaro = precioMasCaroPosicionLE(LE, i);
                            write(STDOUT_FILENO, &precioMasCaro, sizeof(float));
                        }
                        else if (j == 2) // Refiere al precio más barato
                        {
                            float precioMasBarato = precioMasBaratoPosicionLE(LE, i);
                            write(STDOUT_FILENO, &precioMasBarato, sizeof(float));
                        }
                        else if (j == 3) // Refiere al nombre del juego más caro
                        {
                            char nombreJuegoMasCaro[largoChar];
                            strcpy(nombreJuegoMasCaro, nombreJuegoMasCaroPosicionLE(LE, i));
                            write(STDOUT_FILENO, &nombreJuegoMasCaro, sizeof(char)*largoChar);
                        }
                        else if (j == 4) // Refiere al nombre del juego más barato
                        {
                            char nombreJuegoMasBarato[largoChar];
                            strcpy(nombreJuegoMasBarato, nombreJuegoMasBaratoPosicionLE(LE, i));
                            write(STDOUT_FILENO, &nombreJuegoMasBarato, sizeof(char)*largoChar);
                        }
                        else if (j == 5) // Refiere al contador de juegos
                        {
                            int contadorJuegos = contadorJuegosPosicionLE(LE, i);
                            write(STDOUT_FILENO, &contadorJuegos, sizeof(int));
                        }
                        else if (j == 6) // Refiere a la suma total de juegos
                        {
                            float sumaTotalJuegos = sumaTotalJuegosPosicionLE(LE, i);
                            write(STDOUT_FILENO, &sumaTotalJuegos, sizeof(float));
                        }
                        else if (j == 7) // Refiere al promedio de precios de los juegos
                        {
                            float promedioPrecioJuegos = promedioPrecioJuegosPosicionLE(LE, i);
                            write(STDOUT_FILENO, &promedioPrecioJuegos, sizeof(float));
                        }
                        else if (j == 8) // Refiere al contador de juegos de Windows
                        {
                            int contadorW = contadorWPosicionLE(LE, i);
                            write(STDOUT_FILENO, &contadorW, sizeof(int));
                        }
                        else if (j == 9) // Refiere al contador de juegos de MacOS
                        {
                            int contadorMC = contadorMACPosicionLE(LE, i);
                            write(STDOUT_FILENO, &contadorMC, sizeof(int));
                        }
                        else if (j == 10) // Refiere al contador de juegos de Linux
                        {
                            int contadorL = contadorLPosicionLE(LE, i);
                            write(STDOUT_FILENO, &contadorL, sizeof(int));
                        }
                        else if (j == 11) // Refiere al porcentaje de juegos Windows
                        {
                            float porcentajeW = porcentajeWPosicionLE(LE, i);
                            write(STDOUT_FILENO, &porcentajeW, sizeof(float));
                        }
                        else if (j == 12) // Refiere al porcentaje de juegos MacOs
                        {
                            float porcentajeMC = porcentajeMACPosicionLE(LE, i);
                            write(STDOUT_FILENO, &porcentajeMC, sizeof(float));
                        }
                        else if (j == 13) // Refiere al porcentaje de juegos Linux
                        {
                            float porcentajeL = porcentajeLPosicionLE(LE, i);
                            write(STDOUT_FILENO, &porcentajeL, sizeof(float));
                        }
                        else if (j == 14) // Refiere a la lista de juegos gratis
                        {
                            char juegosGratis[largoCharMax];
                            strcpy(juegosGratis, juegosGratisPosicionLE(LE, i));
                            write(STDOUT_FILENO, &juegosGratis, sizeof(char)*largoCharMax);
                        }
                    }
                }
            }
            return 0;
        }
        else
        {   
            /************************************ Lógica de solución - punto 9 ************************************/
            int nroJuego = 1;
            int posicionAct = 0;
            char *token = strtok(buffer, ","); // Se fragmente la línea recibida de acuerdo a un coma(,)
            char nombreJuego[largoChar] = "";
            float precioJuego;
            int anio;
            char esGratis[largoChar] = "";
            int esWindows = 0;
            int esMac = 0;
            int esLinux = 0;
            float promWindows = 0;
            float promMac = 0;
            float promLinux = 0;
            while (token != NULL) // Mientras queden elementos por evaluar en la línea fragmentada
            {
                if (posicionAct == posicionNombreJuego) // Aquí token = nombre del juego
                {
                    strcat(nombreJuego, token); 
                }
                else if (posicionAct == posicionPrecio) // Aquí token = precio
                {
                    precioJuego = atof(token);
                }
                else if (posicionAct == posicionAnio) // Aquí token = año
                {
                    anio = atoi(token);
                }
                else if (posicionAct == posicionEsGratis) // Aquí token = si el juego es gratis
                {
                    if (strcmp(token, "True") == 0) // Si el juego es gratis...
                    {
                        strcat(esGratis, nombreJuego);
                        strcat(esGratis, "\n");
                    }
                }
                else if (posicionAct == posicionEsW) // Aquí token = si el juego está disponible en Windows
                {
                    if (strcmp(token, "Yes") == 0) // Si el juegos considera Windows...
                    {
                        esWindows = 1;
                        promWindows = 100.0;
                    }
                }
                else if (posicionAct == posicionEsMC) // Aquí token = si el juego está disponible en Mac
                {
                    if (strcmp(token, "Yes") == 0) // Si el juegos considera Mac...
                    {
                        esMac = 1;
                        promMac = 100.0;
                    }
                }
                else if (posicionAct == posicionEsL) // Aquí token = si el juego está disponible en Linux
                {
                    if (strcmp(token, "Yes") == 0) // Si el juegos considera Linux...
                    {
                        esLinux = 1;
                        promLinux = 100.0;
                    }
                }
                token = strtok(NULL, ","); // Se continua al siguiente elemento
                posicionAct++; // Aumenta la posición del elemento
            }
            // Si es lista enlazada es vacia, agrega la información obtenida
            if (esListaVacia(LE))
            {
                insertarInicio(LE, anio, precioJuego,
                               precioJuego, nombreJuego,
                               nombreJuego, nroJuego,
                               precioJuego, precioJuego,
                               esWindows, esMac, esLinux,
                               promWindows, promMac, promLinux,
                               esGratis);
            }
            // Si no, busca si los años coinciden
            else
            {
                // Si coiciden, compara y procesa con la información obtenida (deja uno solo)
                if (aniosEquivalentes(LE, anio))
                {
                    // La información se actualiza en el nodo ya existente en la LE de acuerdo a los parámetros obtenidos
                    // Puntos a considerar
                    // Referente al año, ninguno
                    // Referente al precio más caro, comparar entre la info. obtenida y el nodo del mismo año (extraer el mayor)
                    // Referente al precio más barato, comparar entre la info. obtenida y el nodo del mismo año (extraer el menor)
                    // Referente al nombre del juego más caro, obtenerlo en la línea de código del precio más caro
                    // Referente al nombre del juego más barato, obtenerlo en la línea de código del precio más barato
                    // Referente al contador de juegos, se le suma 1 al nodo con juegos del mismo año (esta condición if)
                    // Referente a la suma total de juegos, sumar precio del juego existente en el nodo y el obtenido
                    // Referente al promedio, calcularlo con el promedio existente y el precio obtenido
                    // Referente al contador de juegos Windows, sumarlo en caso de que corresponda, lo mismo con MC y L
                    // Referente al porcentaje de juegos Windows, calcular el promedio considerando que...
                    // ...si existe se calcula el promedio con el dato de nodo y un 100% del obtenido, caso contrario...
                    // ...se calcula el promedio con el dato de nodo y un 0% del obtenido, los mismo con MC y L
                    // Referente a los juegos gratis, contatenar nombre del juego obtenido si es gratis con la línea ya...
                    // ...existente en el nodo
                    // actualizarNodo
                    LE = actualizarNodo(LE, anio, precioJuego,
                                        precioJuego, nombreJuego,
                                        nombreJuego, nroJuego,
                                        precioJuego, precioJuego,
                                        esWindows, esMac, esLinux,
                                        promWindows, promMac, promLinux,
                                        esGratis);
                }
                // Si no, se agrega la información obtenida
                else
                {
                    insertarInicio(LE, anio, precioJuego,
                                   precioJuego, nombreJuego,
                                   nombreJuego, nroJuego,
                                   precioJuego, precioJuego,
                                   esWindows, esMac, esLinux,
                                   promWindows, promMac, promLinux,
                                   esGratis);
                }
            }
            contador++; // Se ha evaluado un juego más
        }
    }
    liberarLista(LE); // Se libera la memoria empleada
    return 0; // Finaliza el proceso
}