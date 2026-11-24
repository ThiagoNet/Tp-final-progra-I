#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "usuarios.h"
#include "personas.h"
#include "videojuegos.h"
#include "transacciones.h"
#include "reservas.h"
#include "validaciones.h"

void mostrarMenu(void)
{
    system("cls");
    printf("                             MENU PRINCIPAL                                \n");

    printf("\n[VIDEOJUEGOS]\n");
    printf(" 1. Agregar videojuego\n");
    printf(" 2. Modificar videojuego\n");
    printf(" 3. Listado de videojuegos\n");
    printf(" 4. Videojuegos por plataforma\n");
    printf(" 5. Info detallada de videojuego\n");
    printf(" 6. Stock critico\n");

    printf("\n[PERSONAS]\n");
    printf(" 7. Agregar persona\n");
    printf(" 8. Modificar persona\n");
    printf(" 9. Listado de personas\n");
    printf("10. Info detallada de persona\n");

    printf("\n[TRANSACCIONES]\n");
    printf("11. Registrar venta\n");
    printf("12. Resumen de transacciones\n");
    printf("13. Detalle de transaccion\n");

    printf("\n[REPORTES]\n");
    printf("14. Recaudacion mensual\n");
    printf("15. Venta de mayor ganancia\n");

    printf("\n 0. Salir\n");
}

void ejecutarMenu(const Usuario *usuarioActual)
{
    int opcion;

    do
    {
        mostrarMenu();
        opcion = leer_Opcion("Ingrese una opcion: ", 0, 17);

        switch (opcion)
        {
        case 1:
            agregar_Videojuego(ARCHIVO_VIDEOJUEGOS);
            break;
        case 2:
            modificar_Videojuego(ARCHIVO_VIDEOJUEGOS);
            break;
        case 3:
            listado_Videojuego(ARCHIVO_VIDEOJUEGOS);
            break;
        case 4:
            ver_Juegos_Por_Plataforma(ARCHIVO_VIDEOJUEGOS);
            break;
        case 5:
            info_De_Videojuego(ARCHIVO_VIDEOJUEGOS);
            break;
        case 6:
            reporte_Stock_Critico(ARCHIVO_VIDEOJUEGOS);
            break;
        case 7:
            agregarPersona();
            break;
        case 8:
            modificarPersona();
            break;
        case 9:
            listadoPersonas();
            break;
        case 10:
            mostrarPersonaDetallada();
            break;
        case 11:
            registrarVenta(usuarioActual->persona.dni);
            break;
        case 12:
            listarTransaccionesResumen();
            break;
        case 13:
            mostrarTransaccionDetalle();
            break;
        case 14:
            reporte_Recaudacion_Mensual();
            break;
        case 15:
            reporte_Mayor_Ganancia();
            break;
        case 0:
            printf("Hasta luego\n");
            break;
        default:
            printf("Opcion invalida. Elija una opcion entre 0 y 17\n");
            break;
        }

        if (opcion != 0)
        {
            system("pause");
        }
    }
    while (opcion != 0);
}
