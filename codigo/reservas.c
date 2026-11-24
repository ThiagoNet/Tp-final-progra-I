#include <stdio.h>
#include <string.h>
#include "reservas.h"
#include "videojuegos.h"
#include "personas.h"
#include "transacciones.h"
#include "fechas.h"

//1:
int obtenerProximoIdReserva(void)
{

    FILE *archivo = fopen(ARCHIVO_RESERVAS, "rb");

    if(archivo == NULL)
    {
        return 1;
    }

    Reserva actual;
    int ultimoId = 0;

    while(fread(&actual, sizeof(Reserva), 1, archivo) == 1)
    {
        ultimoId = actual.idReserva;
    }

    fclose(archivo);

    return ultimoId + 1;
}

//2:
void registrarReserva(const char *dniEmpleado)
{

    Videojuego juego;
    Persona cliente;
    Reserva r = {0};
    int id = 0;
    int cantidad = 0;
    float precioVenta = 0;
    float sena = 0;
    char dniCliente[15];

    printf("Ingrese el id del juego a reservar:\n");
    scanf("%d", &id);

    if(buscarVideojuegoPorId(id, &juego) == 0)
    {
        printf("El juego no existe.\n");
        return;
    }

    printf("Ingrese la cantidad a reservar:\n");
    scanf("%d", &cantidad);

    if(cantidad <= 0)
    {
        printf("Cantidad invalida.\n");
        return;
    }

    if(cantidad <= juego.stock)
    {
        printf("Hay stock suficiente (%d). Registre una venta directa.\n", juego.stock);
        return;
    }

    printf("Ingrese el dni del cliente:\n");
    scanf("%14s", dniCliente);

    if(buscarPersonaPorDni(dniCliente, &cliente) != 1)
    {
        printf("El dni no existe!!\n");
        return;
    }

    printf("Ingrese el precio de venta unitario pactado:\n");
    scanf("%f", &precioVenta);

    if(precioVenta <= 0)
    {
        printf("El precio debe ser mayor a 0!!\n");
        return;
    }

    printf("Ingrese la sena entregada:\n");
    scanf("%f", &sena);

    if(sena < 0 || sena > precioVenta * cantidad)
    {
        printf("Sena invalida.\n");
        return;
    }

    r.fecha = pedirFecha();
    r.idReserva = obtenerProximoIdReserva();
    r.idJuego = id;
    r.cantidad = cantidad;
    r.precioVenta = precioVenta;
    r.sena = sena;
    r.estado = 0;
    strcpy(r.dniCliente, dniCliente);
    strcpy(r.dniEmpleado, dniEmpleado);

    FILE *archivo = fopen(ARCHIVO_RESERVAS, "ab");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de reservas\n");
        return;
    }

    fwrite(&r, sizeof(Reserva), 1, archivo);
    fclose(archivo);

    printf("Reserva registrada!! Id reserva: %d\n", r.idReserva);
}

//3:
void listarReservas(void)
{

    FILE *archivo = fopen(ARCHIVO_RESERVAS, "rb");

    if(archivo == NULL)
    {
        printf("Todavia no hay reservas!\n");
        return;
    }

    Reserva actual;

    printf("=====LISTADO DE RESERVAS=====\n");
    printf("|| %-4s || %-8s || %-12s || %-8s || %-10s || %-10s ||\n", "ID", "JUEGO", "CLIENTE", "CANTIDAD", "FECHA", "ESTADO");

    while(fread(&actual, sizeof(Reserva), 1, archivo) == 1)
    {

        printf("|| %-4d || %-8d || %-12s || %-8d || ", actual.idReserva, actual.idJuego, actual.dniCliente, actual.cantidad);
        mostrarFecha(actual.fecha);

        if(actual.estado == 0)
        {
            printf(" || %-10s ||\n", "Pendiente");
        }
        else if(actual.estado == 1)
        {
            printf(" || %-10s ||\n", "Cumplida");
        }
        else
        {
            printf(" || %-10s ||\n", "Cancelada");
        }
    }

    fclose(archivo);
}

//4:
void cancelarReserva(void)
{

    FILE *archivo = fopen(ARCHIVO_RESERVAS, "rb+");

    if(archivo == NULL)
    {
        printf("Todavia no hay reservas!\n");
        return;
    }

    Reserva actual;
    int idBuscado = 0;
    int encontrada = 0;

    printf("Ingrese el id de la reserva a cancelar:\n");
    scanf("%d", &idBuscado);

    while(!encontrada && fread(&actual, sizeof(Reserva), 1, archivo) == 1)
    {
        if(actual.idReserva == idBuscado)
        {
            encontrada = 1;

            if(actual.estado != 0)
            {
                printf("La reserva no esta pendiente, no se puede cancelar.\n");
            }
            else
            {
                actual.estado = 2;
                fseek(archivo, sizeof(Reserva), SEEK_CUR);
                fwrite(&actual, sizeof(Reserva), 1, archivo);
                printf("Reserva cancelada. Sena a devolver: $%.2f\n", actual.sena);
            }
        }
    }

    fclose(archivo);

    if(!encontrada)
    {
        printf("No existe una reserva con ese id.\n");
    }
}

//5:
void cumplirReservasPendientes(int idJuego)
{

    FILE *archivo = fopen(ARCHIVO_RESERVAS, "rb+");

    if(archivo == NULL)
    {
        return;
    }

    Reserva r;
    Videojuego juego;
    Transaccion t;
    Fecha fechaVenta = {0, 0, 0};
    int fechaPedida = 0;

    while(fread(&r, sizeof(Reserva), 1, archivo) == 1)
    {

        if(r.estado == 0 && r.idJuego == idJuego)
        {

            if(buscarVideojuegoPorId(idJuego, &juego) == 1 && juego.stock >= r.cantidad)
            {

                if(fechaPedida == 0)
                {
                    printf("\nHay reservas para cumplir. Ingrese la fecha de hoy:\n");
                    fechaVenta = pedirFecha();
                    fechaPedida = 1;
                }

                memset(&t, 0, sizeof(Transaccion));
                t.fecha = fechaVenta;
                t.idTransaccion = obtenerProximoIdTransaccion();
                t.idJuegoVendido = r.idJuego;
                t.cantidadVendida = r.cantidad;
                t.precioUnitarioVenta = r.precioVenta;
                t.gananciaTotal = (r.precioVenta - juego.precioAdquisicion) * r.cantidad;
                strcpy(t.dniCliente, r.dniCliente);
                strcpy(t.dniEmpleado, r.dniEmpleado);

                if(guardarTransaccion(&t) == 1)
                {
                    descontarStock(r.idJuego, r.cantidad);

                    r.estado = 1;
                    fseek(archivo, sizeof(Reserva), SEEK_CUR);
                    fwrite(&r, sizeof(Reserva), 1, archivo);
                    fseek(archivo, 0, SEEK_CUR);

                    printf("Reserva %d cumplida. Cliente: %s. Resta cobrar: $%.2f. Id transaccion: %d\n",
                           r.idReserva, r.dniCliente, r.precioVenta * r.cantidad - r.sena, t.idTransaccion);
                }
            }
        }
    }

    fclose(archivo);
}
