#ifndef TRANSACCIONES_H_INCLUDED
#define TRANSACCIONES_H_INCLUDED

#include "estructuras.h"

//FUNCIONES:
int obtenerProximoIdTransaccion(void);
int guardarTransaccion(const Transaccion *t);
void registrarVenta(const char *dniEmpleado);
void listarTransaccionesResumen(void);
void mostrarTransaccionDetalle(void);

//3k:
void reporte_Recaudacion_Mensual(void);

//3l:
void reporte_Mayor_Ganancia(void);

#endif // TRANSACCIONES_H_INCLUDED
