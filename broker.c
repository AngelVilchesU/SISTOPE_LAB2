#include "fbroker.h"
//////////////////
// Entradas: Parámetros entregados por el proceso lab2.c
// Salidas: No considera
// Descripción: Proceso principal del presente código que abarca desde el punto de lógica...
//              ...3 hasta el punto de lógica 12
int main(int argc, char *argv[])
{
    /************************************ Lógica de solución - punto 3 ************************************/
    // En este punto, los parámetros son recibidos correctamente desde el proceso lab2.c
    pid_t pidP;
    int IDChild = 0; // ID personal para facilitar el proceso de identificación del proceso hijo
    int status;
    int escrituraPipe[atoi(argv[4])][2], lecturaPipe[atoi(argv[4])][2]; // PIPES
    for (int i = 0; i < atoi(argv[4]); i++) // Se crea la cantidad de PIPES equivalente a los procesos hijos a generar
    {
        pipe(escrituraPipe[i]);
        pipe(lecturaPipe[i]);
    }
    /************************************ Lógica de solución - punto 4 ************************************/
    while (IDChild < atoi(argv[4])) // Se crean tantos procesos hijos como workers se indique
    {
        pidP = fork(); // Creación del proceso hijo
        if (pidP == 0) // Si es hijo
        {
            break;
        }
        IDChild = IDChild + 1; // ID para facilitar su identificación en el programa
    }
    /************************************ Lógica de solución - punto 5 ************************************/
    if (pidP == 0) // Si es hijo
    {
        if (dup2(lecturaPipe[IDChild][READ], STDIN_FILENO) == -1) // Uso de dup2 para PIPE de lectura
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }
        if (dup2(escrituraPipe[IDChild][WRITE], STDOUT_FILENO) == -1) // Uso de dup2 para PIPE de escritura
        {
            printf("Error en el dup2 del pipe de lectura\n");
            exit(-1);
        }
        // Cierre de los extremos que no se utilizarán
        close(escrituraPipe[IDChild][READ]);
        close(lecturaPipe[IDChild][WRITE]);
        close(escrituraPipe[IDChild][WRITE]);
        close(lecturaPipe[IDChild][READ]);
        execl("./worker", "./worker", NULL); // Llamado a execl
    }
    else // Si es padre
    {
        /************************************ Lógica de solución - punto 6 ************************************/
        for (int i = 0; i < atoi(argv[4]); i++) // Cierre del PIPE de lectura (read) de todos los hijos
        {
            close(lecturaPipe[i][READ]);
        }
        FILE *dctoEntrada = fopen(argv[0], "r"); // Se abre el archivo de entrada en modo lectura
        if (dctoEntrada == NULL)                 // En caso de algún error asociado a la no existencia del documento
        {
            printf("%s: error in input file named\n", argv[0]);
            exit(-1);
        }
        srand(time(NULL)); // Semilla aleatoria
        char linea[largoChar]; // Variable que contendrá las líneas del archivo leído
        int random = 0; // variable que contendrá el número random generado
        char ordenFin[4] = "FIN"; // Orden para finalizar la espera de líneas de los hijos
        char lineaRespuesta[largoChar]; // Variable que contendrá las líneas del archivo leído
        while (fgets(linea, 300, dctoEntrada) != NULL) // Mientras no se haya leído cada línea del archivo de entrada
        {
            random = randomizer(atoi(argv[4])); // Se llama a la función randomizer obteniendo un número aleatorio entre 0 y el nro. de workers
            write(lecturaPipe[random][WRITE], &linea, sizeof(char) * largoChar); // Se envía la línea al worker correspondiente dado el número random generado
        }
        /************************************ Lógica de solución - punto 7 ************************************/
        for (int i = 0; i < atoi(argv[4]); i++) // Envío de la orden 'FIN' cada worker
        {
            write(lecturaPipe[i][WRITE], &ordenFin, sizeof(char) * 4);
        }
        /************************************ Lógica de solución - punto 8 ************************************/
        TDAlista *lista = crearListaVacia(); // Creación de lista enlazada que contendrá los resultados entregados por cada worker
        for (int i = 0; i < atoi(argv[4]); i++)
        {
            int cantNodo;
            int contadorJuegos;
            /************************************ Lógica de solución - punto 12 ************************************/
            read(escrituraPipe[i][READ], &cantNodo, sizeof(int)); // Se lee la cantidad de nodos evaluados
            read(escrituraPipe[i][READ], &contadorJuegos, sizeof(int)); // Se lee la cantidad de líneas evaluadas dado un worker particular
            printf("Hijo %d: lineas procesadas: %d\n", i + 1, contadorJuegos);
            // A continuación se reciben secuencialmente los datos obtenidos por el worker en la medida...
            // ...que son almacenados en la lista enlazada creada anterioremente
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
                    for (int k = 0; k < nroElementosStruct; k++) // Por cada elemento del nodo de la lista enlazada
                    {
                        if (k == 0) // Refiere al año
                        {
                            read(escrituraPipe[i][READ], &anio, sizeof(int));
                        }
                        else if (k == 1)
                        {
                            read(escrituraPipe[i][READ], &precioMasCaro, sizeof(float));
                        }
                        else if (k == 2)
                        {
                            read(escrituraPipe[i][READ], &precioMasBarato, sizeof(float));
                        }
                        else if (k == 3)
                        {
                            read(escrituraPipe[i][READ], &nombreJuegoMasCaro, sizeof(char) * largoChar);
                        }
                        else if (k == 4)
                        {
                            read(escrituraPipe[i][READ], &nombreJuegoMasBarato, sizeof(char) * largoChar);
                        }
                        else if (k == 5)
                        {
                            read(escrituraPipe[i][READ], &contadorJuegos, sizeof(int));
                        }
                        else if (k == 6)
                        {
                            read(escrituraPipe[i][READ], &sumaTotalJuegos, sizeof(float));
                        }
                        else if (k == 7)
                        {
                            read(escrituraPipe[i][READ], &promedioPrecioJuegos, sizeof(float));
                        }
                        else if (k == 8)
                        {
                            read(escrituraPipe[i][READ], &contadorW, sizeof(int));
                        }
                        else if (k == 9)
                        {
                            read(escrituraPipe[i][READ], &contadorMAC, sizeof(int));
                        }
                        else if (k == 10)
                        {
                            read(escrituraPipe[i][READ], &contadorL, sizeof(int));
                        }
                        else if (k == 11)
                        {
                            read(escrituraPipe[i][READ], &porcentajeW, sizeof(float));
                        }
                        else if (k == 12)
                        {
                            read(escrituraPipe[i][READ], &porcentajeMAC, sizeof(float));
                        }
                        else if (k == 13)
                        {
                            read(escrituraPipe[i][READ], &porcentajeL, sizeof(float));
                        }
                        else if (k == 14)
                        {
                            read(escrituraPipe[i][READ], &juegosGratis, sizeof(char) * largoCharMax); // ARREGLAR *****************************************************************
                        }
                    }
                    // En la lista enlazada de broker, si esta es vacia, se agrega la información obtenida desde el worker
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
                    // Si no está vacia, busca si los años coinciden
                    else
                    {
                        // Si coiciden, compara y procesa con la información obtenida del worker (deja uno solo)
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
                        // Si no, se agrega
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
        archivoSalida = fopen(argv[1], "w"); // Se crea el archivo de salida dado el nombre ingresado por pantalla desde lab2.c
        imprimirEnFlujoDesdeAnio(lista, archivoSalida, atoi(argv[2])); // Se imprimen los resultados obtenidos en el flujo
        fclose(archivoSalida); // Se cierra el archivo
        // Si -b fue ingresada, se imprimen los resultados obtenidos por pantalla
        if (atoi(argv[5]) == 1)
        {
            recorrerLista(lista, atoi(argv[2]));
        }
        liberarLista(lista); // Se libera la memoria empleada
    }
    return 0; // Finaliza el proceso
}
