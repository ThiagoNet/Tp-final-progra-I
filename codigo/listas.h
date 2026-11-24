#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "estructuras.h"

#define CANT_PLATAFORMAS 4
#define CANT_GENEROS 7
#define CANT_ROLES 5

//FUNCIONES:

//Muestra la lista de plataformas y deja elegir varias.
//Elegir una ya elegida la desmarca. Con 0 se confirma (tiene que haber al menos una).
//Guarda el resultado separado por comas, por ejemplo: "PS5, PC"
void elegir_Plataformas(char *destino, int tam);

//Muestra la lista de plataformas y deja elegir una sola (se usa para buscar)
void elegir_Una_Plataforma(char *destino, int tam);

//Muestra la lista de generos y deja elegir uno
void elegir_Genero(char *destino, int tam);

//Muestra la lista de roles y deja elegir uno
void elegir_Rol(char *destino, int tam);

#endif // LISTAS_H_INCLUDED
