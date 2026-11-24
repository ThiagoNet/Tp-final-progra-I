#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include "estructuras.h"

//FUNCIONES:

//Limpia lo que haya quedado en el buffer del teclado
void limpiar_Buffer(void);

//Solo deja escribir digitos. Hasta 9 digitos, Enter confirma, Backspace borra.
//Repite hasta que el valor sea >= minimo
int leer_Entero(const char *mensaje, int minimo);

//Igual que leer_Entero pero ademas el valor tiene que ser <= maximo (para menus y listas)
int leer_Opcion(const char *mensaje, int minimo, int maximo);

//Solo digitos y un punto decimal (maximo 2 decimales). El valor debe ser mayor a 0
float leer_Precio(const char *mensaje);

//Solo digitos, se guarda como texto (sirve para DNI y telefono).
//Pide entre minimo_Digitos y tam - 1 digitos
void leer_Digitos(const char *mensaje, char *destino, int tam, int minimo_Digitos);

//Un texto es valido si termina en '\0', no tiene caracteres raros
//y tiene al menos un caracter que no sea espacio ni '0'
int texto_Valido(const char *texto, int tam);

//Pide un texto libre (nombre, direccion, titulo)
void leer_Texto(const char *mensaje, char *destino, int tam);

#endif // VALIDACIONES_H_INCLUDED
