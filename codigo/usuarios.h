#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#include "estructuras.h"

void crearAdminPorDefecto(void);
int validarCredenciales(const char *usuario, const char *contrasenia, Usuario *encontrado);
int login(Usuario *usuarioLogueado);

#endif // USUARIOS_H_INCLUDED
