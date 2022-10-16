#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define largoChar 300

int randomizer(int);













typedef struct nodoGenerico
{
  int nroWorker;
  char linea[largoChar];
  struct nodoGenerico* puntero;
}nodo;

// Cabecera de la estructura anterior con la cual se realiza una lista enlazada
typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;

void leerYasignarWorker(char* , int, TDAlista*);

TDAlista* crearListaVacia();

void liberarLista(TDAlista* );

void insertarInicio(TDAlista*, int, char*);

int esListaVacia(TDAlista* );

void imprimirLista(TDAlista* );

void recorrerLista(TDAlista * );

int existeNroWorker(TDAlista* , int);

void eliminar_nodo_pos(TDAlista *, int );

int longitud_nodos(TDAlista * );

int posicionNodo(TDAlista* , int );

char* obtenerLineaPos(TDAlista * , int);