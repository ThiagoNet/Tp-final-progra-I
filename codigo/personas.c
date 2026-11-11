#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "personas.h"

int buscarPersonaPorDni(const char *dni, Persona *resultado)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb");

    if(archivo == NULL)
    {
        return 0;
    }

    Persona actual;
    int encontrada = 0;

    while(!encontrada && fread(&actual, sizeof(Persona), 1, archivo) == 1)
    {
        if(strcmp(actual.dni, dni) == 0)
        {
            *resultado = actual;
            encontrada = 1;
        }
    }

    fclose(archivo);
    return encontrada;
}

void listadoPersonas(void)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb");
    if(archivo == NULL)
    {
        printf("No hay personas cargadas o el archivo no existe\n");
        return;
    }

    Persona actual;

    while(fread(&actual, sizeof(Persona), 1, archivo) == 1)
    {
        printf("Nombre: %-20s\n DNI: %-20s\n Rol: %-20s\n", actual.nombre, actual.dni, actual.rol);
    }

    fclose(archivo);
    return;
}

void mostrarPersonaDetallada(void)
{

    char dni[15];
    Persona encontrada;

    printf("Ingrese un dni:\n");
    scanf("%14s", dni);

    if (buscarPersonaPorDni(dni, &encontrada) == 1)
    {
        printf("Dni: %s Nombre: %s Telefono: %s Direccion: %s Rol: %s\n", encontrada.dni, encontrada.nombre, encontrada.telefono,encontrada.direccion, encontrada.rol);
    }
    else
    {
        printf("No existe una persona con ese dni\n");
    }
}

void pedirDatosPersona(Persona *p)
{

    printf("Ingrese el nombre de la persona\n");
    scanf(" %49[^\n]", p->nombre);
    printf("Ingrese la direccion de la persona\n");
    scanf(" %29[^\n]", p->direccion);
    printf("Ingrese el telefono de la persona\n");
    scanf(" %19s", p->telefono);
    printf("Ingrese el rol de la persona\n");
    scanf(" %14[^\n]", p->rol);
}

int buscarPosicionPersona(const char *dni)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb");
    if(archivo == NULL)
    {
        return -1;
    }

    Persona actual;
    int posicion = -1;
    int indice = 0;

    while(posicion == -1 && fread(&actual, sizeof(Persona), 1,archivo)== 1)
    {
        if(strcmp(actual.dni, dni) == 0)
        {
            posicion = indice;
        }
        indice++;
    }
    fclose(archivo);
    return posicion;
}

void guardarPersonaNueva(const Persona *p)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "ab");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de personas\n");
        return;
    }

    fwrite(p, sizeof(Persona), 1, archivo);
    fclose(archivo);
}

void sobrescribirPersona(int posicion, const Persona *p)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb+");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de personas\n");
        return;
    }

    fseek(archivo, posicion * sizeof(Persona), SEEK_SET);
    fwrite(p, sizeof(Persona), 1, archivo);
    fclose(archivo);
}

void agregarModificarPersona(void)
{

    char dni[15];

    printf("Ingrese el numero de dni de la persona:\n");
    scanf("%14s", dni);

    int posicion = buscarPosicionPersona(dni);

    Persona nueva = {0};
    strcpy(nueva.dni, dni);
    if(posicion != -1)
    {
        printf("La persona ya existe, ingrese los nuevos datos\n");
    }
    pedirDatosPersona(&nueva);

    if(posicion == -1)
    {
        guardarPersonaNueva(&nueva);
        printf("Persona Agregada!\n");
    }
    else
    {
        sobrescribirPersona(posicion, &nueva);
        printf("Persona modificada!\n");
    }

}
