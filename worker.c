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
            char esGratis[largoChar];
            char esWindows[largoChar];
            char esMac[largoChar];
            char esLinux[largoChar];

            while (token != NULL)
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
                    strcat(esGratis, token);
                }
                else if (posicionAct == posicionEsW) // Aquí token = si el juego está disponible en Windows
                {
                    strcat(esWindows, token);
                }
                else if (posicionAct == posicionEsMC) // Aquí token = si el juego está disponible en Mac
                {
                    strcat(esMac, token);
                }
                else if (posicionAct == posicionEsL) // Aquí token = si el juego está disponible en Linux
                {
                    strcat(esLinux, token);
                }
                token = strtok(NULL, ",");
                posicionAct++;
            }
            // Si es lista vacia, lo agrega
            // Si no, busca si los años coinciden
                // Si coiciden, compara y proceso (deja uno solo)
                // Si no, agregalo
            



        }
    }

    liberarLista(LE);
    return 0;
}