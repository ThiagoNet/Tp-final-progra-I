#include <stdio.h>
#include <string.h>
#include "transacciones.h"
#include "videojuegos.h"
#include "fechas.h"
#include "personas.h"
int obtenerProximoIdTransaccion(void){

FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");

if(archivo == NULL){
    return 1;
}

Transaccion actual;
int ultimoId = 0;

while(fread(&actual, sizeof(Transaccion), 1, archivo)== 1){
    ultimoId = actual.idTransaccion;
}

fclose(archivo);

return ultimoId + 1;
}

int guardarTransaccion(const Transaccion *t){

FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "ab");

if(archivo == NULL){
    printf("No se pudo abrir el archivo de transacciones\n");
    return 0;
}

int escritos = fwrite(t, sizeof(Transaccion), 1, archivo);

fclose(archivo);

return escritos == 1;

}

void registrarVenta(const char *dniEmpleado){

Videojuego juego;
int id = 0;
int cantidad = 0;
float precioVenta = 0;
char dniCliente[15];
Persona cliente;
Transaccion t = {0};

printf("Ingrese el id del juego:\n");
scanf("%d", &id);

if(buscarVideojuegoPorId(id, &juego) == 0){
    printf("El juego no existe.\n");
    return;
}
if(juego.stock <= 0){
    printf("Juego sin stock\n");
    return;
}

printf("Ingrese la cantidad deseada:\n");
scanf("%d", &cantidad);

if(cantidad <= 0 || cantidad > juego.stock){
    printf("Cantidad invalida o stock insuficiente.\n");
    return;
}

printf("Ingrese el precio de venta:\n");
scanf("%f", &precioVenta);
if(precioVenta <= 0){
    printf("El precio no puede ser menor a 0\n");
    return;
}
printf("Ingrese el dni del cliente:\n");
scanf("%14s", dniCliente);
if(buscarPersonaPorDni(dniCliente,&cliente) != 1){
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

if(guardarTransaccion(&t) == 1){
    descontarStock(id, cantidad);
    printf("Venta registrada!\n");
    printf("Ganancia obtenida: $%.2f\n", t.gananciaTotal);
    printf("Id transaccion: %d\n", t.idTransaccion);
}else{
printf("Error, la venta no pudo ser registrada.\n");
}
}

void listarTransaccionesResumen(void){
FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");
if(archivo == NULL){
    printf("Todavia no hay ventas!\n");
    return;
}

Transaccion actual;

while(fread(&actual, sizeof(Transaccion), 1, archivo) == 1){
    mostrarFecha(actual.fecha);
    printf(" Id: %d\n", actual.idJuegoVendido);
    printf(" Id transaccion: %d\n", actual.idTransaccion);
}
fclose(archivo);
}

void mostrarTransaccionDetalle(void){
FILE *archivo = fopen(ARCHIVO_TRANSACCIONES, "rb");
if(archivo == NULL){
    printf("Todavia no hay ventas registradas!\n");
    return;
}
Transaccion actual;
int encontrada = 0;
int idBuscado = 0;
printf("Ingrese el id a buscar: \n");
scanf("%d", &idBuscado);

while(!encontrada && fread(&actual, sizeof(Transaccion), 1, archivo)== 1){
if(actual.idTransaccion == idBuscado){
    encontrada = 1;
    printf("ID: %d\n", actual.idTransaccion);
    mostrarFecha(actual.fecha);
    printf("\nID del juego: %d\n", actual.idJuegoVendido);
    printf("Cantidad vendida: %d\n", actual.cantidadVendida);
    printf("Precio: %g\n", actual.precioUnitarioVenta);
    printf("Ganancia: %g\n", actual.gananciaTotal);
    printf("Dni del cliente: %s\n", actual.dniCliente);
    printf("Dni del empleado: %s\n", actual.dniEmpleado);
}
}
fclose(archivo);

if(!encontrada){
    printf("No existe una transaccion con ese id.\n");
}
}

