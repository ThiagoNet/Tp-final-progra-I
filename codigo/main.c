#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "menu.h"
#include <string.h>
#include "videojuegos.h"

int main()
{
    Usuario usuarioActual;

    crearAdminPorDefecto();
    if (login(&usuarioActual)) {
        printf("Bienvenido, %s\n", usuarioActual.persona.nombre);
        ejecutarMenu(&usuarioActual);
    } else {
        printf("Acceso denegado.\n");
    }

    agregar_Videojuego("videojuegos.dat");

    listado_Videojuego("videojuegos.dat");

    return 0;
}
