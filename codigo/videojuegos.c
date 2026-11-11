#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "videojuegos.h"
#include <ctype.h>


//FUNCION 3a:

void agregar_Videojuego(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb+");

    if(archivo == NULL)
    {

        archivo = fopen(archivo_Videojuego, "wb+");

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

    Videojuego v = {0};
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
        scanf(" %50[^\n]", v.plataforma);

        printf("\n---Nuevo Genero: ");
        scanf(" %50[^\n]", v.genero);


        fseek(archivo, sizeof(Videojuego), SEEK_CUR);
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
        scanf(" %50[^\n]", v.plataforma);

        printf("\n---Nuevo Genero: ");
        scanf(" %50[^\n]", v.genero);

        fseek(archivo, 0, SEEK_END);
        fwrite(&v, sizeof(Videojuego), 1, archivo);

    }

    fclose(archivo);

}

//3e:
void listado_Videojuego(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb");


    if(archivo == NULL)
    {
        printf("ERROR!! No se pudo abrir el archivo...\n");
        return;
    }

    Videojuego v;

    printf("=====LISTADO DE VIDEOJUEGOS=====\n");
    printf("|| %.30s || %.50s || %s\n", "TITULO", "PLATAFORMA", "STOCK");


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        printf("|| %.30s || %.50s || %d\n", v.titulo, v.plataforma, v.stock);

    }

    fclose(archivo);

}

//Funciones para la venta (3j):
int buscarVideojuegoPorId(int id, Videojuego *resultado)
{

    FILE *archivo = fopen(ARCHIVO_VIDEOJUEGOS, "rb");

    if(archivo == NULL)
    {
        return 0;
    }

    Videojuego actual;
    int encontrado = 0;

    while(!encontrado && fread(&actual, sizeof(Videojuego), 1, archivo) == 1)
    {
        if(actual.idJuego == id)
        {
            *resultado = actual;
            encontrado = 1;
        }
    }

    fclose(archivo);
    return encontrado;
}

int descontarStock(int id, int cantidad)
{

    FILE *archivo = fopen(ARCHIVO_VIDEOJUEGOS, "rb+");

    if(archivo == NULL)
    {
        return 0;
    }

    Videojuego actual;
    int actualizado = 0;

    while(!actualizado && fread(&actual, sizeof(Videojuego), 1, archivo) == 1)
    {
        if(actual.idJuego == id)
        {
            actual.stock -= cantidad;
            fseek(archivo, sizeof(Videojuego), SEEK_CUR);
            fwrite(&actual, sizeof(Videojuego), 1, archivo);
            actualizado = 1;
        }
    }

    fclose(archivo);
    return actualizado;
}

//FUNCIONES AUXILIARES:
char pasar_Minuscula(char c)
{

    if(c >= 'A' && c <= 'Z')
    {

        c = c + 32;
    }
    return c;
}

int plataforma_Coincide(const char *plataformas, const char *plataforma_Buscada)
{

    int i = 0;
    int j;
    int coincide = 0;
    int largo = strlen(plataforma_Buscada);

    while(plataformas[i] != '\0' && coincide == 0)
    {

        while(plataformas[i] == ' ' || plataformas[i] == ',')
        {
            i++;
        }


        j = 0;

        while(j < largo && plataformas[i + j] != '\0' && pasar_Minuscula(plataformas[i + j]) == pasar_Minuscula(plataforma_Buscada[j]))
        {
            j++;
        }


        if(j == largo && (plataformas[i + j] == '\0' || plataformas[i + j] == ',' || plataformas[i + j] == ' '))
        {
            coincide = 1;
        }

        while(plataformas[i] != '\0' && plataformas[i] != ',')
        {
            i++;
        }

    }

    return coincide;

}
//3f:
void ver_Juegos_Por_Plataforma(const char *archivo_Videojuego)
{


    FILE *archivo = fopen(archivo_Videojuego, "rb");


    if(archivo == NULL)
    {
        printf("ERROR!! No se pudo abrir el archivo...\n");
        return;
    }

    char plataforma_Buscada[50];

    printf("=====Ingrese una Plataforma=====\n");
    scanf(" %49[^\n]", plataforma_Buscada);


    Videojuego v;
    int encontrado = 0;


    printf("=====JUEGOS PARA LA PLATAFORMA: %s =====\n", plataforma_Buscada);
    printf("|| %-15s || %-5s || %-9s ||\n", "TITULO", "STOCK", "PRECIO");


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(plataforma_Coincide(v.plataforma, plataforma_Buscada) == 1)
        {

            printf("|| %-15.15s || %-5d || $%g ||\n", v.titulo, v.stock, v.precioAdquisicion);
            encontrado++;

        }

    }

    if(encontrado == 0)
    {

        printf("\nNo se encontraron juegos para la Plataforma %s\n", plataforma_Buscada);

    }

    fclose(archivo);

}
//3g:
void info_De_Videojuego(const char *archivo_Videojuego)
{


    FILE *archivo = fopen(archivo_Videojuego, "rb");


    if(archivo == NULL)
    {
        printf("ERROR!! No se pudo abrir el archivo...\n");
        return;
    }


    int id_Buscado = 0;

    printf("=====Ingrese el ID del Videojuego que desea Buscar=====\n");
    scanf("%d", &id_Buscado);


    if(id_Buscado == 0)
    {

        fclose(archivo);
        return;
    }


    Videojuego v;
    int encontrado = 0;


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(v.idJuego == id_Buscado)
        {

            encontrado = 1;
            break;

        }

    }

    if(encontrado == 1)
    {

        printf("\n=====INFORMACION DEL JUEGO=====\n");
        printf("===== ID DE JUEGO:      %d\n", v.idJuego);
        printf("===== TITULO:      %s\n", v.titulo);
        printf("===== PLATAFORMA(s):      %s\n", v.plataforma);
        printf("===== GENERO:      %s\n", v.genero);
        printf("===== STOCK DISPONIBLE:      %d\n", v.stock);
        printf("===== PRECIO ADQUISICION:      %.2f\n", v.precioAdquisicion);

    }
    else
    {

        printf("No se encontro ningun Videojuego con el ID %d.\n", id_Buscado);

    }


    fclose(archivo);


}

//3m:
void reporte_Stock_Critico(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb");


    if(archivo == NULL)
    {
        printf("ERROR!! No se pudo abrir el archivo...\n");
        return;
    }


    Videojuego v;
    int stock_Actual;
    int encontrado = 0;


    printf("=====STOCK CRITICO (<= 5 unidades)=====\n");
    printf("|| %-5s || %-50s || %-10s || %-5s ||\n", "ID", "TITULO", "PLATAFORMA", "STOCK");


    for(stock_Actual = 0; stock_Actual <= 5; stock_Actual++)
    {

        fseek(archivo, 0, SEEK_SET);

        while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
        {

            if(v.stock == stock_Actual)
            {

                printf("|| %-5d || %-15.15s || %-50s || %-5d ||\n", v.idJuego, v.titulo, v.plataforma, v.stock);
                encontrado++;

            }

        }

    }

    if(encontrado == 0)
    {

        printf("\nNo hay videojuegos con stock critico.\n");

    }

    fclose(archivo);

}
