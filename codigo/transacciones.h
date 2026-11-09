#ifndef TRANSACCIONES_H_INCLUDED
#define TRANSACCIONES_H_INCLUDED

#include "estructuras.h"

int obtenerProximoIdTransaccion(void);
int guardarTransaccion(const Transaccion *t);
void registrarVenta(const char *dniEmpleado);
#endif // TRANSACCIONES_H_INCLUDED
