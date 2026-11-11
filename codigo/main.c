#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "menu.h"
#include "videojuegos.h"
#include "transacciones.h"
#include "fechas.h"

int main()
{
    Usuario usuarioActual;

    crearAdminPorDefecto();

    if(login(&usuarioActual) == 1)
    {
        ejecutarMenu(&usuarioActual);
    }
    else
    {
        printf("Usuario o contrasenia incorrectos\n");
    }

    return 0;
}
