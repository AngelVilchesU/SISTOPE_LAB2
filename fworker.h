#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define largoChar 300
#define largoCharMax 9999
#define nroElementosStruct 15

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

int esListaVacia(TDAlista *);

//void recorrerLista(TDAlista *);

void insertarInicio(TDAlista *, int , float , 
                    float , char* ,
                    char* , int , 
                    float , float , 
                    int , int , int , 
                    float , float , float ,
                    char* );

void eliminarInicio(TDAlista *);

void liberarLista(TDAlista* );

int aniosEquivalentes(TDAlista* , int);

TDAlista *actualizarNodo(TDAlista *, int , float ,
                         float , char *,
                         char *, int ,
                         float , float ,
                         int , int , int ,
                         float , float , float ,
                         char *);

int anioPosicionLE(TDAlista * , int );

float precioMasCaroPosicionLE(TDAlista * , int );

float precioMasBaratoPosicionLE(TDAlista * , int );

char* nombreJuegoMasCaroPosicionLE(TDAlista * , int );

char* nombreJuegoMasBaratoPosicionLE(TDAlista * , int );

int contadorJuegosPosicionLE(TDAlista * , int );

float sumaTotalJuegosPosicionLE(TDAlista * , int );

float promedioPrecioJuegosPosicionLE(TDAlista * , int );

int contadorWPosicionLE(TDAlista * , int );

int contadorMACPosicionLE(TDAlista * , int );

int contadorLPosicionLE(TDAlista * , int );

float porcentajeWPosicionLE(TDAlista * , int );

float porcentajeMACPosicionLE(TDAlista * , int );

float porcentajeLPosicionLE(TDAlista * , int);

char* juegosGratisPosicionLE(TDAlista * , int );