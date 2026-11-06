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

void mostrarPersonaDetallada(void){

char dni[15];
Persona encontrada;

printf("Ingrese un dni:\n");
scanf("%14s", dni);

if (buscarPersonaPorDni(dni, &encontrada) == 1){
    printf("Dni: %s Nombre: %s Telefono: %s Direccion: %s Rol: %s\n", encontrada.dni, encontrada.nombre, encontrada.telefono,encontrada.direccion, encontrada.rol);
}else{
printf("No existe una persona con ese dni\n");
}
}
