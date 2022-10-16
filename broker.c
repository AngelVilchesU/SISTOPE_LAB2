#include "fbroker.h"

int main(int argc, char *argv[])
{
    printf("--------------\n");
    printf("Los parametros ingresados son:\niFlag: %s\noFlag: %s\ndFlag: %s\npFlag: %s\nnFlag: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    printf("--------------\n");
    pid_t pidP;
    int status;
    int fd1[2]; // Primer pipe (0 refiere a lectura y 1 a escritura)
    int fd2[2]; // Segundo pipe
    pipe(fd1);
    pipe(fd2);

    TDAlista* listaEnlazada = crearListaVacia();
    leerYasignarWorker(argv[0], atoi(argv[4]), listaEnlazada);

    for (int i = 0; i < atoi(argv[4]); i++)
    {
        pidP = fork();
        if (pidP > 0) // Es padre
        {
            wait(&status);

            while (existeNroWorker(listaEnlazada, i))
            {
                printf("ASINAR VIA PIPE INFO AL WORKER %d\n", i);
                printf("Su posicione en la LE es: %d\n", posicionNodo(listaEnlazada, i));
                //printf("Linea: %s\n", obtenerLineaPos(listaEnlazada, posicionNodo(listaEnlazada, i)));
                close(fd1[0]); // Se cierra el canal de lectura del primer pipe
                write(fd1[1], obtenerLineaPos(listaEnlazada, posicionNodo(listaEnlazada, i)), strlen(obtenerLineaPos(listaEnlazada, posicionNodo(listaEnlazada, i))) + 1);
                close(fd1[1]);

                wait(NULL);
                char lineaH[largoChar];
                close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
                read(fd2[0], lineaH, 300);
                printf("Linea por parte de PADRE: %s\n", lineaH);
                close(fd2[0]); // Se cierra el canal de lectura del segundo pipe

                eliminar_nodo_pos(listaEnlazada, posicionNodo(listaEnlazada, i));
            }
            

          
        }
        else
        {
            wait(&status);

            
            close(fd1[1]); // Se cierra el canal de escritura del primer pipe
            char lineaH[largoChar];
            read(fd1[0], lineaH, 300);
            printf("Linea por parte de HIJO: %s\n", lineaH);
            close(fd1[0]); // Se cierra el canal de lectura del primer pipe
            close(fd2[0]); // Se cierra el canal de lectura del segundo pipe

            write(fd2[1], lineaH, strlen(lineaH) + 1);
            close(fd2[1]); // Se cierra el canal de escritura del segundo pipe
            

            execl("./worker", "./worker", NULL);

            exit(0);
        }
    }
    liberarLista(listaEnlazada);
    return 0;
}