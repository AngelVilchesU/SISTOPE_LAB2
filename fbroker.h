#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#define largoChar 300

int randomizer(int);

int estaPid(int* , int , int );

void agregarPid(int* , int , int );

void inicializarArrEstatico(int* , int );