#ifndef VIDEOJUEGOS_H_INCLUDED
#define VIDEOJUEGOS_H_INCLUDED

#include "estructuras.h"

//FUNCIONES:

//3a:
void agregar_Videojuego(const char *archivo_Videojuego);
void listado_Videojuego(const char *archivo_Videojuego);
int buscarVideojuegoPorId(int id, Videojuego *resultado);
int descontarStock(int id, int cantidad);

#endif // VIDEOJUEGOS_H_INCLUDED
