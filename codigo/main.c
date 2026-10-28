#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "menu.h"
#include <string.h>

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
    return 0;
}

