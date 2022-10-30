#include "fbroker.h"

int main(int argc, char *argv[])
{
    // printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    pid_t pidP;
    int IDChild = 0;
    int status;
    int escrituraPipe[atoi(argv[4])][2], lecturaPipe[atoi(argv[4])][2];
    for (int i = 0; i < atoi(argv[4]); i++)
    {
        pipe(escrituraPipe[i]);
        pipe(lecturaPipe[i]);
    }
    while (IDChild < atoi(argv[4]))
    {
        pidP = fork();
        if (pidP == 0)
        {
            break;
        }
        IDChild = IDChild + 1;
    }
    if (pidP == 0) // Si es hijo
    {
        if (dup2(lecturaPipe[IDChild][READ], STDIN_FILENO) == -1)
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }
        if (dup2(escrituraPipe[IDChild][WRITE], STDOUT_FILENO) == -1)
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }

        close(escrituraPipe[IDChild][READ]);
        close(lecturaPipe[IDChild][WRITE]);
        close(escrituraPipe[IDChild][WRITE]);
        close(lecturaPipe[IDChild][READ]);
        execl("./worker", "./worker", NULL);
    }
    else // Si es padre
    {
        for (int i = 0; i < atoi(argv[4]); i++)
        {
            close(lecturaPipe[i][READ]);
        }
        FILE *dctoEntrada = fopen(argv[0], "r"); // Se abre el archivo de entrada en modo lectura
        if (dctoEntrada == NULL)                 // En caso de algún error asociado a la no existencia del documento
        {
            printf("%s: error in input file named\n", argv[0]);
            exit(-1);
        }
        srand(time(NULL));
        char linea[largoChar]; // Variable que contendrá las líneas del archivo leído
        int random = 0;
        char ordenFin[4] = "FIN"; // Orden para finalizar la espera de líneas de los hijos
        char ordenContinuar[4] = "CON";
        char lineaRespuesta[largoChar]; // Variable que contendrá las líneas del archivo leído

        ///////////
        char buff[600];
        char bff[5000];
        char lineaFinal[400];
        char numero[50];
        ///////////
        while (fgets(linea, 300, dctoEntrada) != NULL)
        {
            random = randomizer(atoi(argv[4])); // Se llama a la función randomizer obteniendo un número aleatorio entre 0 y el nro. de workers
            //printf("numero random: %d\n", random);
            ///////
            sprintf(numero, " Numero: %d\n", random);
            strcpy(lineaFinal, linea);
            strcat(lineaFinal, numero);
            // sprintf(lineaFinal, "Linea: %s ", linea);
            // printf("A: %s", lineaFinal);
            /////////
            write(lecturaPipe[random][WRITE], &linea, sizeof(char) * largoChar);
        }

        for (int i = 0; i < atoi(argv[4]); i++)
        {
            write(lecturaPipe[i][WRITE], &ordenFin, sizeof(char) * 4);
        }

        ////////////////////////////////////////////////////////////////////////////

        TDAlista *lista = crearListaVacia();

        for (int i = 0; i < atoi(argv[4]); i++)
        {

            int cantNodo;
            int contadorJuegos;
            read(escrituraPipe[i][READ], &cantNodo, sizeof(int));

            read(escrituraPipe[i][READ], &contadorJuegos, sizeof(int));
            //printf("Cantidad de nodos evaluados %d\n", cantNodo);
            printf("Hijo %d: lineas procesadas: %d\n", i + 1, contadorJuegos);
            
            if (cantNodo != 0) // Si existen nodos por evaluar
            {
                for (int j = 0; j < cantNodo; j++) // Por cada nodo en la lista enlazada
                {
                    //////////// Varibles locales ///////////
                    int anio;
                    float precioMasCaro;
                    float precioMasBarato;
                    char nombreJuegoMasCaro[largoChar];
                    char nombreJuegoMasBarato[largoChar];
                    int contadorJuegos;
                    float sumaTotalJuegos;
                    float promedioPrecioJuegos;
                    int contadorW;
                    int contadorMAC;
                    int contadorL;
                    float porcentajeW;
                    float porcentajeMAC;
                    float porcentajeL;
                    char juegosGratis[largoCharMax];
                    ////////////////////////////////////////////
                    for (int k = 0; k < nroElementosStruct; k++) // Por cada elemento del nodo de la lista enlazada
                    {
                        if (k == 0) // Refiere al año
                        {
                            read(escrituraPipe[i][READ], &anio, sizeof(int));
                            //printf("ANIO %d\n", anio);
                        }
                        else if (k == 1)
                        {
                            read(escrituraPipe[i][READ], &precioMasCaro, sizeof(float));
                            //printf("precio mas caro %f\n", precioMasCaro);
                        }
                        else if (k == 2)
                        {
                            read(escrituraPipe[i][READ], &precioMasBarato, sizeof(float));
                            //printf("precio mas barato %f\n", precioMasBarato);
                        }
                        else if (k == 3)
                        {
                            read(escrituraPipe[i][READ], &nombreJuegoMasCaro, sizeof(char) * largoChar);
                            //("nombre juego mas caro %s\n", nombreJuegoMasCaro);
                        }
                        else if (k == 4)
                        {
                            read(escrituraPipe[i][READ], &nombreJuegoMasBarato, sizeof(char) * largoChar);
                            //printf("nombre juego mas barato %s\n", nombreJuegoMasBarato);
                        }
                        else if (k == 5)
                        {
                            read(escrituraPipe[i][READ], &contadorJuegos, sizeof(int));
                            //printf("contador juegos %d\n", contadorJuegos);
                        }
                        else if (k == 6)
                        {
                            read(escrituraPipe[i][READ], &sumaTotalJuegos, sizeof(float));
                            //printf("suma total jeugos %f\n", sumaTotalJuegos);
                        }
                        else if (k == 7)
                        {
                            read(escrituraPipe[i][READ], &promedioPrecioJuegos, sizeof(float));
                            //printf("promedio precio juegos %f\n", promedioPrecioJuegos);
                        }
                        else if (k == 8)
                        {
                            read(escrituraPipe[i][READ], &contadorW, sizeof(int));
                            //printf("contador Windows %d\n", contadorW);
                        }
                        else if (k == 9)
                        {
                            read(escrituraPipe[i][READ], &contadorMAC, sizeof(int));
                            //printf("contador MAC %d\n", contadorMAC);
                        }
                        else if (k == 10)
                        {
                            read(escrituraPipe[i][READ], &contadorL, sizeof(int));
                            //printf("contador linux %d\n", contadorL);
                        }
                        else if (k == 11)
                        {
                            read(escrituraPipe[i][READ], &porcentajeW, sizeof(float));
                            //printf("porcentaje Windows %f\n", porcentajeW);
                        }
                        else if (k == 12)
                        {
                            read(escrituraPipe[i][READ], &porcentajeMAC, sizeof(float));
                            //printf("porcentaje MAC %f\n", porcentajeMAC);
                        }
                        else if (k == 13)
                        {
                            read(escrituraPipe[i][READ], &porcentajeL, sizeof(float));
                            //printf("porcentaje Linux %f\n", porcentajeL);
                        }
                        else if (k == 14)
                        {
                            read(escrituraPipe[i][READ], &juegosGratis, sizeof(char) * largoCharMax); // ARREGLAR *****************************************************************
                            //printf("juegos gratis: %s\n", juegosGratis);
                        }
                    }
                    //printf("-------------------------------------------------------------\n");
                    if (esListaVacia(lista))
                    {
                        insertarInicio(lista, anio, precioMasCaro,
                                       precioMasBarato, nombreJuegoMasCaro,
                                       nombreJuegoMasBarato, contadorJuegos,
                                       sumaTotalJuegos, promedioPrecioJuegos,
                                       contadorW, contadorMAC, contadorL,
                                       porcentajeW, porcentajeMAC, porcentajeL,
                                       juegosGratis);
                    }
                    // Si no, busca si los años coinciden
                    else
                    {
                        // Si coiciden, compara y proceso (deja uno solo)
                        if (aniosEquivalentes(lista, anio))
                        {
                            lista = actualizarNodo(lista, anio, precioMasCaro,
                                                   precioMasBarato, nombreJuegoMasCaro,
                                                   nombreJuegoMasBarato, contadorJuegos,
                                                   sumaTotalJuegos, promedioPrecioJuegos,
                                                   contadorW, contadorMAC, contadorL,
                                                   porcentajeW, porcentajeMAC, porcentajeL,
                                                   juegosGratis);
                        }
                        // Si no, agregalo
                        else
                        {
                            insertarInicio(lista, anio, precioMasCaro,
                                           precioMasBarato, nombreJuegoMasCaro,
                                           nombreJuegoMasBarato, contadorJuegos,
                                           sumaTotalJuegos, promedioPrecioJuegos,
                                           contadorW, contadorMAC, contadorL,
                                           porcentajeW, porcentajeMAC, porcentajeL,
                                           juegosGratis);
                        }
                    }
                }
            }
        }

        
        FILE * archivoSalida;
        archivoSalida = fopen(argv[1], "w");
        imprimirEnFlujoDesdeAnio(lista, archivoSalida, atoi(argv[2]));
        fclose(archivoSalida);
        
        if (atoi(argv[5]) == 1)
        {
            recorrerLista(lista, atoi(argv[2]));
        }
        













        liberarLista(lista);
    }


    
    return 0;
}