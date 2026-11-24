#ifndef RESERVAS_H_INCLUDED
#define RESERVAS_H_INCLUDED


#include "estructuras.h"

int obtenerProximoIdReserva(void);
void registrarReserva(const char *dniEmpleado);
void listarReservas(void);
void cancelarReserva(void);
void cumplirReservasPendientes(int idJuego);

#endif // RESERVAS_H_INCLUDED
