#include "fworker.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char buffer[largoChar];
    char gigante[5000];
    int number = 0;
    int contador = 0;

    // Posiciones en la linea
    int posicionFinal = 10;
    int posicionEsL = 9;
    int posicionEsMC = 8;
    int posicionEsW = 7;
    int posicionEsGratis = 6;
    int posicionAnio = 5;
    int posicionPrecio = 3;
    int posicionNombreJuego = 1;
    float sumaTotalJuegos = 0;
    



    TDAlista* LE = crearListaVacia();

    while (1)
    {
        read(STDIN_FILENO, &buffer, sizeof(char) * 300);
        // read(STDIN_FILENO, &number, sizeof(int));
        if (strcmp(buffer, "FIN") == 0)
        {

            // en este write ira todo lo procesado
            write(STDOUT_FILENO, &gigante, sizeof(char) * 5000);
            return 0;
        }
        else
        {
            //sprintf(gigante, "Linea: %s\n", buffer);
            //strcat(gigante, buffer);
            contador++;


            ///////////////////////////////////////////////
            //980880,Twinfold,0,60.0,False,2018,False,Yes,No,No
            int posicionAct = 0;
            char* token = strtok(buffer, ",");
            //////////////////////////
            char nombreJuego[largoChar];
            float precioJuego;
            int anio;
            char esGratis[largoChar] = "";
            int esWindows = 0;
            int esMac = 0;
            int esLinux = 0;
            float promWindows = 0;
            float promMac = 0;
            float promLinux = 0;

            while (token != NULL)
            {
                if (posicionAct == posicionNombreJuego) // Aquí token = nombre del juego
                {
                    strcat(nombreJuego, token);
                }
                else if (posicionAct == posicionPrecio) // Aquí token = precio
                {
                    precioJuego = atof(token);
                    sumaTotalJuegos = sumaTotalJuegos + precioJuego;
                }
                else if (posicionAct == posicionAnio) // Aquí token = año
                {
                    anio = atoi(token);
                }
                else if (posicionAct == posicionEsGratis) // Aquí token = si el juego es gratis
                {
                    if (strcmp(token, "Yes"))
                    {
                        strcat(esGratis, token);
                    }
                }
                else if (posicionAct == posicionEsW) // Aquí token = si el juego está disponible en Windows
                {
                    if (strcmp(token, "Yes"))
                    {
                        esWindows = 1;
                        promWindows = 100.0;
                    }                    
                }
                else if (posicionAct == posicionEsMC) // Aquí token = si el juego está disponible en Mac
                {
                    if (strcmp(token, "Yes"))
                    {
                        esMac = 1;
                        promMac = 100.0;
                    }
                }
                else if (posicionAct == posicionEsL) // Aquí token = si el juego está disponible en Linux
                {
                    if (strcmp(token, "Yes"))
                    {
                        esLinux = 1;
                        promLinux = 100.0;
                    }
                }
                token = strtok(NULL, ",");
                posicionAct++;
            }
            // Si es lista vacia, lo agrega
            if (esListaVacia(LE))
            {
                insertarInicio(LE, anio, precioJuego,
                               precioJuego, nombreJuego,
                               nombreJuego, contador,
                               sumaTotalJuegos, precioJuego,
                               esWindows, esMac, esLinux,
                               promWindows, promMac, promLinux,
                               esGratis);
            }
            // Si no, busca si los años coinciden
            else
            {
                // Si coiciden, compara y proceso (deja uno solo)
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
                    //actualizarNodo
                    LE = actualizarNodo(LE, anio, precioJuego,
                               precioJuego, nombreJuego,
                               nombreJuego, contador,
                               sumaTotalJuegos, precioJuego,
                               esWindows, esMac, esLinux,
                               promWindows, promMac, promLinux,
                               esGratis);
                }
                // Si no, agregalo
                else
                {
                    insertarInicio(LE, anio, precioJuego,
                               precioJuego, nombreJuego,
                               nombreJuego, contador,
                               sumaTotalJuegos, precioJuego,
                               esWindows, esMac, esLinux,
                               promWindows, promMac, promLinux,
                               esGratis);
                }
            }
            
            
                
                
            



        }
    }

    liberarLista(LE);
    return 0;
}