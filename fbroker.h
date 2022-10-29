#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define WRITE 1
#define READ 0
#define largoChar 300
#define largoCharMax 9999
#define nroElementosStruct 15

int randomizer(int);

/*------------- estructura de datos -------------*/
typedef struct nodoGenerico
{
    int anio;
    float precioMasCaro;
    float precioMasBarato;
    char nombreJuegoMasCaro[largoChar];
    char nombreJuegoMasBarato[largoChar];
    int contadorJuegos;
    float sumaTotalJuegos;
    float promedioPrecioJuegos;
    int contadorW;
    int contadorMC;
    int contadorL;
    float porcentajeW;
    float porcentajeMC;
    float porcentajeL;
    char juegosGratis[largoCharMax];
    struct nodoGenerico *siguiente;
} nodo;

typedef struct listaGenerica
{
    nodo *inicio;
} TDAlista;

TDAlista *crearListaVacia();

void liberarLista(TDAlista* );

void recorrerLista(TDAlista *);

int esListaVacia(TDAlista *);







struct nodoGenerico *copyList(struct nodoGenerico *);

