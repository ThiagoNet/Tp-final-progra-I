#include <stdio.h>
#include <string.h>
#include "personas.h"
#include "validaciones.h"
#include "listas.h"

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

    leer_Digitos("Ingrese un dni: ", dni, sizeof(dni), 7);

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

    leer_Texto("Ingrese el nombre de la persona: ", p->nombre, sizeof(p->nombre));
    leer_Texto("Ingrese la direccion de la persona: ", p->direccion, sizeof(p->direccion));
    leer_Digitos("Ingrese el telefono de la persona: ", p->telefono, sizeof(p->telefono), 6);
    elegir_Rol(p->rol, sizeof(p->rol));
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

//Devuelve 1 si se guardo bien y 0 si hubo error
int guardarPersonaNueva(const Persona *p)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "ab");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de personas\n");
        return 0;
    }

    int escritos = fwrite(p, sizeof(Persona), 1, archivo);
    fclose(archivo);

    return escritos == 1;
}

//Devuelve 1 si se guardo bien y 0 si hubo error
int sobrescribirPersona(int posicion, const Persona *p)
{

    FILE *archivo = fopen(ARCHIVO_PERSONAS, "rb+");
    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo de personas\n");
        return 0;
    }

    fseek(archivo, (long)posicion * (long)sizeof(Persona), SEEK_SET);
    int escritos = fwrite(p, sizeof(Persona), 1, archivo);
    fclose(archivo);

    return escritos == 1;
}

void agregarPersona(void)
{

    char dni[15];

    printf("\n=====AGREGAR PERSONA=====\n");
    leer_Digitos("Ingrese el numero de dni de la persona: ", dni, sizeof(dni), 7);

    if(buscarPosicionPersona(dni) != -1)
    {
        printf("Ya existe una persona con ese dni. Use la opcion de modificar.\n");
        return;
    }

    Persona nueva = {0};
    strcpy(nueva.dni, dni);

    pedirDatosPersona(&nueva);

    if(guardarPersonaNueva(&nueva) == 1)
    {
        printf("Persona Agregada!\n");
    }
    else
    {
        printf("Error, la persona no pudo ser agregada.\n");
    }

}

void modificarPersona(void)
{

    char dni[15];

    printf("\n=====MODIFICAR PERSONA=====\n");
    leer_Digitos("Ingrese el numero de dni de la persona: ", dni, sizeof(dni), 7);

    int posicion = buscarPosicionPersona(dni);

    if(posicion == -1)
    {
        printf("No existe una persona con ese dni\n");
        return;
    }

    Persona nueva = {0};
    strcpy(nueva.dni, dni);

    printf("La persona existe, ingrese los nuevos datos\n");
    pedirDatosPersona(&nueva);

    if(sobrescribirPersona(posicion, &nueva) == 1)
    {
        printf("Persona modificada!\n");
    }
    else
    {
        printf("Error, la persona no pudo ser modificada.\n");
    }

}
