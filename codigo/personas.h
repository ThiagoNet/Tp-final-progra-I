#ifndef PERSONAS_H_INCLUDED
#define PERSONAS_H_INCLUDED

#include "estructuras.h"

int buscarPersonaPorDni(const char *dni, Persona *resultado);
void listadoPersonas(void);
void mostrarPersonaDetallada(void);
void agregarModificarPersona(void);
void listarTransaccionesResumen(void);
void mostrarTransaccionDetalle(void);
#endif // PERSONAS_H_INCLUDED
