#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "personas.h"

int buscarPersonaPorDni(const char *dni, Persona *resultado){

FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb");

if(archivo == NULL){
    return 0;
}

Persona actual;
int encontrada = 0;

while(!encontrada && fread(&actual, sizeof(Persona), 1, archivo) == 1){
    if(strcmp(actual.dni, dni) == 0){
        *resultado = actual;
        encontrada == 1;
    }
}

fclose(archivo);
return encontrada;
}
