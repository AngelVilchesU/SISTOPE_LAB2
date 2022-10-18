#include "fworker.h"

int main(int argc, char* argv[])
{

    //SOLO COMPILAR WORKER Y TEST PARA PROBAR

    /*
    char bff[300];
    char gigante[5000];
    char gigante2[5000] = "leyo la flag final";
    int number;

    //no pescar este caso por el momento
    /*
    while (1)
    {
        read(STDIN_FILENO,  &bff, sizeof(char) *300);
        read(STDIN_FILENO, &number, sizeof(number));
        if (number == 0)
        {
            //en este write ira todo lo procesado
            write(STDOUT_FILENO, &gigante2, sizeof(char)*5000);
            return 0;
        }
        else{
            sprintf(gigante,"Linea: %s\n", bff);
        }
        
    }
    */

   /*
    //caso para el cual al menos se envio una linea al worker
    //trabjar con este caso por mientras
    while (1)
    {
        read(STDIN_FILENO,  &bff, sizeof(char) *300);
        read(STDIN_FILENO, &number, sizeof(number));
        if (number == 0)
        {
            //en este write ira todo lo procesado
            write(STDOUT_FILENO, &gigante, sizeof(char)*5000);
            return 0;
        }
        else{
            sprintf(gigante,"Linea: %s\n", bff);
        }
        
    }
    */

    holaMundo();
    return 0;
}