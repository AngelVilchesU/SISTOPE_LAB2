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

void recorrerLista(TDAlista *, int);

int esListaVacia(TDAlista *);

void insertarInicio(TDAlista *, int , float , 
                    float , char* ,
                    char* , int , 
                    float , float , 
                    int , int , int , 
                    float , float , float ,
                    char* );

TDAlista *actualizarNodo(TDAlista *, int , float ,
                         float , char *,
                         char *, int ,
                         float , float ,
                         int , int , int ,
                         float , float , float ,
                         char *);

int aniosEquivalentes(TDAlista* , int);

char* strJuegoMasCaro(float , char* , float , char* );

char* strJuegoMasBarato(float , char* , float , char* );

float promedio(float , float );

float valorMayor(float , float );

float valorMenor(float , float );

void imprimirEnFlujoDesdeAnio(TDAlista * , FILE * , int);