#include <stdio.h>
#include <string.h>
#include "videojuegos.h"
#include "validaciones.h"
#include "listas.h"

//Devuelve el mayor id que hay en el archivo + 1 (1 si no hay archivo o esta vacio)
int obtenerProximoIdVideojuego(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb");

    if(archivo == NULL)
    {
        return 1;
    }

    Videojuego actual;
    int ultimoId = 0;

    while(fread(&actual, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(actual.idJuego > ultimoId)
        {
            ultimoId = actual.idJuego;
        }

    }

    fclose(archivo);

    return ultimoId + 1;

}

void pedir_Datos_Videojuego(Videojuego *v)
{

    v->stock = leer_Entero("\n---Stock: ", 0);
    v->precioAdquisicion = leer_Precio("\n---Precio de Adquisicion: ");
    leer_Texto("\n---Titulo de Juego: ", v->titulo, sizeof(v->titulo));
    elegir_Plataformas(v->plataforma, sizeof(v->plataforma));
    elegir_Genero(v->genero, sizeof(v->genero));

}

//Sirve para detectar juegos guardados mal en el archivo
int videojuego_Es_Valido(Videojuego v)
{

    int valido = 1;

    if(v.idJuego <= 0)
    {
        valido = 0;
    }

    if(v.stock < 0)
    {
        valido = 0;
    }

    if(!(v.precioAdquisicion > 0))
    {
        valido = 0;
    }

    if(texto_Valido(v.titulo, sizeof(v.titulo)) == 0)
    {
        valido = 0;
    }

    if(texto_Valido(v.plataforma, sizeof(v.plataforma)) == 0)
    {
        valido = 0;
    }

    if(texto_Valido(v.genero, sizeof(v.genero)) == 0)
    {
        valido = 0;
    }

    return valido;

}

//FUNCION 3a:

void agregar_Videojuego(const char *archivo_Videojuego)
{

    Videojuego v = {0};

    v.idJuego = obtenerProximoIdVideojuego(archivo_Videojuego);

    printf("\n=====AGREGAR VIDEOJUEGO=====\n");

    pedir_Datos_Videojuego(&v);

    FILE *archivo = fopen(archivo_Videojuego, "ab");

    if(archivo == NULL)
    {

        printf("Error al Abrir o Crear el Archivo\n");
        return;

    }

    fwrite(&v, sizeof(Videojuego), 1, archivo);
    fclose(archivo);

    printf("\nVideojuego agregado! ID asignado: %d\n", v.idJuego);

}

//3b:
void modificar_Videojuego(const char *archivo_Videojuego)
{

    FILE *archivo = fopen(archivo_Videojuego, "rb+");

    if(archivo == NULL)
    {

        printf("No hay videojuegos cargados o el archivo no existe\n");
        return;

    }

    int id_Buscado = leer_Entero("Ingrese el ID del Videojuego a Modificar (Pon 0 para Salir): ", 0);

    if(id_Buscado == 0)
    {

        fclose(archivo);
        return;

    }

    Videojuego v = {0};
    int encontrado = 0;

    while(encontrado == 0 && fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(v.idJuego == id_Buscado)
        {
            encontrado = 1;
        }

    }

    if(encontrado == 1)
    {

        printf("\nModificando: %s\n", v.titulo);

        pedir_Datos_Videojuego(&v);

        fseek(archivo, -(long)sizeof(Videojuego), SEEK_CUR);
        fwrite(&v, sizeof(Videojuego), 1, archivo);

        printf("\nVideojuego modificado!\n");

    }
    else
    {

        printf("No se encontro ningun Videojuego con el ID %d.\n", id_Buscado);

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
    int invalidos = 0;

    printf("=====LISTADO DE VIDEOJUEGOS=====\n");
    printf("|| %-30s || %-50s || %-5s ||\n", "TITULO", "PLATAFORMA", "STOCK");


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(videojuego_Es_Valido(v) == 1)
        {
            printf("|| %-30.30s || %-50.50s || %-5d ||\n", v.titulo, v.plataforma, v.stock);
        }
        else
        {
            invalidos++;
        }

    }

    if(invalidos > 0)
    {
        printf("\nSe omitieron %d registros guardados con datos invalidos.\n", invalidos);
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
        if(actual.idJuego == id && videojuego_Es_Valido(actual) == 1)
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
            fseek(archivo, -(long)sizeof(Videojuego), SEEK_CUR);
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

//Compara el nombre exacto contra cada item de la lista separada por comas
//(ej: "PS5, Nintendo Switch 2" tiene dos items)
int plataforma_Coincide(const char *plataformas, const char *plataforma_Buscada)
{

    int i = 0;
    int j;
    int fin;
    int largo_Item;
    int coincide = 0;
    int largo = strlen(plataforma_Buscada);

    while(plataformas[i] != '\0' && coincide == 0)
    {

        //saltar espacios y comas antes del item
        while(plataformas[i] == ' ' || plataformas[i] == ',')
        {
            i++;
        }

        //buscar donde termina el item (proxima coma o fin del texto)
        fin = i;

        while(plataformas[fin] != '\0' && plataformas[fin] != ',')
        {
            fin++;
        }

        //sacar los espacios del final del item
        while(fin > i && plataformas[fin - 1] == ' ')
        {
            fin--;
        }

        largo_Item = fin - i;

        //solo se compara si el item tiene el mismo largo que lo buscado
        if(largo_Item == largo)
        {

            j = 0;

            while(j < largo && pasar_Minuscula(plataformas[i + j]) == pasar_Minuscula(plataforma_Buscada[j]))
            {
                j++;
            }

            if(j == largo)
            {
                coincide = 1;
            }

        }

        //avanzar hasta la proxima coma
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

    elegir_Una_Plataforma(plataforma_Buscada, sizeof(plataforma_Buscada));


    Videojuego v;
    int encontrado = 0;


    printf("\n=====JUEGOS PARA LA PLATAFORMA: %s =====\n", plataforma_Buscada);
    printf("|| %-30s || %-5s || %-9s ||\n", "TITULO", "STOCK", "PRECIO");


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(plataforma_Coincide(v.plataforma, plataforma_Buscada) == 1 && videojuego_Es_Valido(v) == 1)
        {

            printf("|| %-30.30s || %-5d || $%-8.2f ||\n", v.titulo, v.stock, v.precioAdquisicion);
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


    int id_Buscado = leer_Entero("=====Ingrese el ID del Videojuego que desea Buscar (Pon 0 para Salir)=====\n", 0);


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
    printf("|| %-5s || %-30s || %-50s || %-5s ||\n", "ID", "TITULO", "PLATAFORMA", "STOCK");


    for(stock_Actual = 0; stock_Actual <= 5; stock_Actual++)
    {

        fseek(archivo, 0, SEEK_SET);

        while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
        {

            if(v.stock == stock_Actual && videojuego_Es_Valido(v) == 1)
            {

                printf("|| %-5d || %-30.30s || %-50.50s || %-5d ||\n", v.idJuego, v.titulo, v.plataforma, v.stock);
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
