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
        encontrada = 1;
    }
}

fclose(archivo);
return encontrada;
}

void listadoPersonas(void){

FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb");
if(archivo == NULL){
    printf("No hay personas cargadas o el archivo no existe\n");
    return;
}

Persona actual;

while(fread(&actual, sizeof(Persona), 1, archivo) == 1){
    printf("Nombre: %-20s\n DNI: %-20s\n Rol: %-20s\n", actual.nombre, actual.dni, actual.rol);
}

fclose(archivo);
return;
}
