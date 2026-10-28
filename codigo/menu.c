#include <stdio.h>
#include "menu.h"
#include "usuarios.h"
#include "personas.h"
#include "videojuegos.h"
#include "transacciones.h"

void mostrarMenu(void)
{

    printf("----MENU PRINCIPAL----\n");
    printf("1. Agregar / Modificar videojuego\n");
    printf("2. Agregar / Modificar persona\n");
    printf("3. Listado de personas\n");
    printf("4. Info detallada de persona\n");
    printf("5. Listado de videojuegos\n");
    printf("6. Videojuegos por plataforma\n");
    printf("7. Info detalada de videojuego\n");
    printf("8. Resumen de transacciones\n");
    printf("9. Detalle de transaccion\n");
    printf("10. Registrar venta\n");
    printf("11. Recaudacion mensual\n");
    printf("12. Venta de mayor ganancia\n");
    printf("13. Stock critico\n");
    printf("0. Salir\n");
}

void ejecutarMenu(const Usuario *usuarioActual)
{

    int opcion;

    do
    {
        mostrarMenu();
        printf("Ingrese una opcion\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("Agregar / Modificar videojuego - En construccion\n");
            break;
        case 2:
            printf("Agregar / Modificar persona - En construccion\n");
            break;
        case 3:
            printf("Listado de personas - En construccion\n");
            break;
        case 4:
            printf("Info detallada de persona - En construccion\n");
            break;
        case 5:
            printf("Listado de videojuegos - En construccion\n");
            break;
        case 6:
            printf("Videojuegos por plataforma - En construccion\n");
            break;
        case 7:
            printf("Info detallada de videojuego - En construccion\n");
            break;
        case 8:
            printf("Resumen de transacciones - En construccion\n");
            break;
        case 9:
            printf("Detalle de transaccion - En construccion\n");
            break;
        case 10:
            printf("Registrar venta - En construccion\n");
            break;
        case 11:
            printf("Recaudacion mensual - En construccion\n");
            break;
        case 12:
            printf("Venta de mayor ganancia - En construccion\n");
            break;
        case 13:
            printf("Stock critico - En construccion\n");
            break;
        case 0:
            printf("Hasta luego\n");
            break;
        default:
            printf("Opcion invalida\n");
        }
    }
    while (opcion != 0);

}
