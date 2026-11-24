#include <stdio.h>
#include <string.h>
#include "transacciones.h"
#include "videojuegos.h"
#include "fechas.h"
#include "personas.h"
#include "validaciones.h"


int obtenerProximoIdTransaccion(void)
{

    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");

    if(archivo == NULL)
    {
        return 1;
    }

    Transaccion actual;
    int ultimoId = 0;

    while(fread(&actual, sizeof(Transaccion), 1, archivo)== 1)
    {
        ultimoId = actual.idTransaccion;
    }

    fclose(archivo);

    return ultimoId + 1;
}

int guardarTransaccion(const Transaccion *t)
{

    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "ab");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de transacciones\n");
        return 0;
    }

    int escritos = fwrite(t, sizeof(Transaccion), 1, archivo);

    fclose(archivo);

    return escritos == 1;

}

void registrarVenta(const char *dniEmpleado)
{

    Videojuego juego;
    int id = 0;
    int cantidad = 0;
    float precioVenta = 0;
    float totalVenta = 0;
    char dniCliente[15];
    Persona cliente;
    Transaccion t = {0};

    printf("\n=====REGISTRAR VENTA=====\n");

    id = leer_Entero("Ingrese el id del juego (Pon 0 para Salir): ", 0);

    if(id == 0)
    {
        return;
    }

    if(buscarVideojuegoPorId(id, &juego) == 0)
    {
        printf("El juego no existe.\n");
        return;
    }
    if(juego.stock <= 0)
    {
        printf("Juego sin stock\n");
        return;
    }

    printf("Juego: %s (stock disponible: %d)\n", juego.titulo, juego.stock);

    do
    {
        cantidad = leer_Entero("Ingrese la cantidad deseada: ", 1);

        if(cantidad > juego.stock)
        {
            printf("Stock insuficiente (disponible: %d).\n", juego.stock);
        }
    }
    while(cantidad > juego.stock);

    precioVenta = leer_Precio("Ingrese el precio de venta unitario: ");

    totalVenta = precioVenta * cantidad;
    printf("Total de la venta: $%.2f\n", totalVenta);

    leer_Digitos("Ingrese el dni del cliente: ", dniCliente, sizeof(dniCliente), 7);
    if(buscarPersonaPorDni(dniCliente,&cliente) != 1)
    {
        printf("El dni no existe! \n");
        return;
    }

    t.fecha = pedirFecha();
    t.idTransaccion = obtenerProximoIdTransaccion();
    t.idJuegoVendido = id;
    t.cantidadVendida = cantidad;
    t.precioUnitarioVenta = precioVenta;
    t.gananciaTotal = (precioVenta - juego.precioAdquisicion) * cantidad;
    strcpy(t.dniCliente, dniCliente);
    strcpy(t.dniEmpleado, dniEmpleado);

    if(guardarTransaccion(&t) == 1)
    {
        descontarStock(id, cantidad);
        printf("Venta registrada!\n");
        printf("Total de la venta: $%.2f\n", totalVenta);
        printf("Ganancia obtenida: $%.2f\n", t.gananciaTotal);
        printf("Id transaccion: %d\n", t.idTransaccion);
    }
    else
    {
        printf("Error, la venta no pudo ser registrada.\n");
    }
}

void listarTransaccionesResumen(void)
{
    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if(archivo == NULL)
    {
        printf("Todavia no hay ventas!\n");
        return;
    }

    Transaccion actual;

    while(fread(&actual, sizeof(Transaccion), 1, archivo) == 1)
    {
        mostrarFecha(actual.fecha);
        printf(" Id: %d\n", actual.idJuegoVendido);
        printf(" Id transaccion: %d\n", actual.idTransaccion);
        printf(" Total: $%.2f\n", actual.precioUnitarioVenta * actual.cantidadVendida);
    }
    fclose(archivo);
}

void mostrarTransaccionDetalle(void)
{
    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if(archivo == NULL)
    {
        printf("Todavia no hay ventas registradas!\n");
        return;
    }
    Transaccion actual;
    int encontrada = 0;
    int idBuscado = 0;

    idBuscado = leer_Entero("Ingrese el id a buscar (Pon 0 para Salir): ", 0);

    if(idBuscado == 0)
    {
        fclose(archivo);
        return;
    }

    while(!encontrada && fread(&actual, sizeof(Transaccion), 1, archivo)== 1)
    {
        if(actual.idTransaccion == idBuscado)
        {
            encontrada = 1;
            printf("ID: %d\n", actual.idTransaccion);
            printf("Fecha: ");
            mostrarFecha(actual.fecha);
            printf("\nID del juego: %d\n", actual.idJuegoVendido);
            printf("Cantidad vendida: %d\n", actual.cantidadVendida);
            printf("Precio unitario: $%.2f\n", actual.precioUnitarioVenta);
            printf("Total: $%.2f\n", actual.precioUnitarioVenta * actual.cantidadVendida);
            printf("Ganancia: $%.2f\n", actual.gananciaTotal);
            printf("Dni del cliente: %s\n", actual.dniCliente);
            printf("Dni del empleado: %s\n", actual.dniEmpleado);
        }
    }
    fclose(archivo);

    if(!encontrada)
    {
        printf("No existe una transaccion con ese id.\n");
    }
}



//3k:
void reporte_Recaudacion_Mensual(void)
{
    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");

    if(archivo == NULL)
    {
        printf("ERROR!! No se pudo abrir el archivo...\n");
        return;
    }

    int mes_Buscado;
    int anio_Buscado;
    float recaudacion_Total = 0;
    int encontrado = 0;

    printf("\n=====RECAUDACION MENSUAL=====\n");

    mes_Buscado = leer_Opcion("-----Ingrese el mes (1-12): ", 1, 12);
    anio_Buscado = leer_Entero("-----Ingrese anio: ", 1);

    Transaccion actual;

    while(fread(&actual, sizeof(Transaccion), 1, archivo) == 1)
    {
        if(actual.fecha.mes == mes_Buscado && actual.fecha.anio == anio_Buscado)
        {
            recaudacion_Total += (actual.precioUnitarioVenta * actual.cantidadVendida);
            encontrado++;
        }
    }

    fclose(archivo);

    if(encontrado > 0)
    {
        printf("-----Mes y Anio consultado: %02d/%d\n", mes_Buscado, anio_Buscado);
        printf("-----Transacciones Encontradas: %d\n", encontrado);
        printf("-----Recaudacion Total: $%.2f\n", recaudacion_Total);
    }
    else
    {
        printf("No se encontraron ventas para el Periodo %02d/%d.\n", mes_Buscado, anio_Buscado);
    }
}

//3l:
void reporte_Mayor_Ganancia(void)
{
    FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");

    if(archivo == NULL)
    {
        printf("Todavia no hay ventas registradas!\n");
        return;
    }

    Transaccion actual;
    Transaccion mayor = {0};
    int hay_ventas = 0;

    while(fread(&actual, sizeof(Transaccion), 1, archivo) == 1)
    {
        if(hay_ventas == 0 || actual.gananciaTotal > mayor.gananciaTotal)
        {
            mayor = actual;
            hay_ventas = 1;
        }
    }

    fclose(archivo);

    if(hay_ventas == 0)
    {
        printf("Todavia no hay ventas registradas!\n");
        return;
    }

    printf("\n=====VENTA DE MAYOR GANANCIA=====\n");
    printf("ID transaccion: %d\n", mayor.idTransaccion);
    printf("Fecha: ");
    mostrarFecha(mayor.fecha);
    printf("\nID del juego: %d\n", mayor.idJuegoVendido);
    printf("Cantidad vendida: %d\n", mayor.cantidadVendida);
    printf("Precio unitario: $%.2f\n", mayor.precioUnitarioVenta);
    printf("Total: $%.2f\n", mayor.precioUnitarioVenta * mayor.cantidadVendida);
    printf("Ganancia total: $%.2f\n", mayor.gananciaTotal);
    printf("Dni del cliente: %s\n", mayor.dniCliente);
    printf("Dni del empleado: %s\n", mayor.dniEmpleado);
}
