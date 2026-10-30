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


    agregar_Videojuego("videojuegos.dat");

    return 0;
}
