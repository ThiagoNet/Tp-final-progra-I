#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "videojuegos.h"

void agregar_Videojuego(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb+");

    if(archivo == NULL)
    {

        archivo == fopen(archivo_Videojuego, "wb+");

        if(archivo == NULL)
        {

            printf("Error al Abrir o Crear el Archivo");
            return;

        }

    }

    int id_Buscado;

    printf("Ingrese el ID del Videojuego (Pon 0 para Salir): ");
    scanf("%d", &id_Buscado);


    if(id_Buscado == 0)
    {

        fclose(archivo);
        return;

    }

    Videojuego v;
    int encontrado = 0;

    rewind(archivo);

    while(fread(&v, sizeof(Videojuego), 1, archivo))
    {

        if(v.idJuego == id_Buscado)
        {

            encontrado = 1;
            break;

        }

    }

    if(encontrado == 1)
    {

        printf("\n---Nuevo Stock: ");
        scanf("%d", &v.stock);

        printf("\n---Nuevo Precio de Adquisicion: ");
        scanf("%f", &v.precioAdquisicion);

        printf("\n---Nuevo Titulo de Juego: ");
        scanf(" %[^\n]", v.titulo);

        printf("\n---Nueva Plataforma: ");
        scanf("%s", v.plataforma);

        printf("\n---Nuevo Genero: ");
        scanf("%s", v.genero);


        fseek(archivo, -sizeof(Videojuego), SEEK_CUR);
        fwrite(&v, sizeof(Videojuego), 1, archivo);

    }
    else
    {

        v.idJuego = id_Buscado;


        printf("\n---Nuevo Stock: ");
        scanf("%d", &v.stock);

        printf("\n---Nuevo Precio de Adquisicion: ");
        scanf("%f", &v.precioAdquisicion);

        printf("\n---Nuevo Titulo de Juego: ");
        scanf(" %[^\n]", v.titulo);

        printf("\n---Nueva Plataforma: ");
        scanf("%s", v.plataforma);

        printf("\n---Nuevo Genero: ");
        scanf("%s", v.genero);

        fseek(archivo, 0, SEEK_END);
        fwrite(&v, sizeof(Videojuego), 1, archivo);

    }

}


