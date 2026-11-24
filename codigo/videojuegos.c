#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "videojuegos.h"

//Funciones auxiliares de validacion:
void limpiar_Buffer(void)
{

    int c;

    while((c = getchar()) != '\n' && c != EOF)
    {
    }

}

int leer_Entero(const char *mensaje, int minimo)
{

    int valor = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);

        if(scanf("%d", &valor) != 1)
        {
            printf("Debe ingresar un numero.\n");
        }
        else if(valor < minimo)
        {
            printf("Valor invalido (minimo %d).\n", minimo);
        }
        else
        {
            ok = 1;
        }

        limpiar_Buffer();

    }
    while(ok == 0);

    return valor;

}

float leer_Precio(const char *mensaje)
{

    float valor = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);

        if(scanf("%f", &valor) != 1)
        {
            printf("Debe ingresar un numero.\n");
        }
        else if(valor <= 0)
        {
            printf("El precio debe ser mayor a 0.\n");
        }
        else
        {
            ok = 1;
        }

        limpiar_Buffer();

    }
    while(ok == 0);

    return valor;

}

//Un texto es valido si termina en '\0', no tiene caracteres raros
//y tiene al menos un caracter que no sea espacio ni '0'
int texto_Valido(const char *texto, int tam)
{

    int i = 0;
    int hay_Contenido = 0;

    while(i < tam && texto[i] != '\0')
    {

        if((unsigned char)texto[i] < 32)
        {
            return 0;
        }

        if(texto[i] != ' ' && texto[i] != '0')
        {
            hay_Contenido = 1;
        }

        i++;

    }

    if(i == tam)
    {
        return 0;
    }

    return hay_Contenido;

}

void leer_Texto(const char *mensaje, char *destino, int tam)
{

    char texto[50];
    int ok = 0;

    do
    {

        texto[0] = '\0';

        printf("%s", mensaje);
        scanf(" %49[^\n]", texto);
        limpiar_Buffer();

        if((int)strlen(texto) >= tam)
        {
            printf("Texto demasiado largo (maximo %d caracteres).\n", tam - 1);
        }
        else if(texto_Valido(texto, 50) == 0)
        {
            printf("Dato invalido: no puede estar vacio ni ser solo ceros.\n");
        }
        else
        {
            ok = 1;
        }

    }
    while(ok == 0);

    strcpy(destino, texto);

}

void pedir_Datos_Videojuego(Videojuego *v)
{

    v->stock = leer_Entero("\n---Nuevo Stock: ", 0);
    v->precioAdquisicion = leer_Precio("\n---Nuevo Precio de Adquisicion: ");
    leer_Texto("\n---Nuevo Titulo de Juego: ", v->titulo, sizeof(v->titulo));
    leer_Texto("\n---Nueva Plataforma: ", v->plataforma, sizeof(v->plataforma));
    leer_Texto("\n---Nuevo Genero: ", v->genero, sizeof(v->genero));

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

    int id_Buscado = leer_Entero("Ingrese el ID del Videojuego (Pon 0 para Salir): ", 0);

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

        pedir_Datos_Videojuego(&v);

        fseek(archivo, -(long)sizeof(Videojuego), SEEK_CUR);
        fwrite(&v, sizeof(Videojuego), 1, archivo);

    }
    else
    {

        v.idJuego = id_Buscado;

        pedir_Datos_Videojuego(&v);

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

int plataforma_Coincide(const char *plataformas, const char *plataforma_Buscada)
{

    int i = 0;
    int j;
    int coincide = 0;
    int largo = strlen(plataforma_Buscada);

    while(plataformas[i] != '\0' && coincide == 0)
    {

        //saltar espacios y comas
        while(plataformas[i] == ' ' || plataformas[i] == ',')
        {
            i++;
        }

        //comparar desde esta posicion
        j = 0;

        while(j < largo && plataformas[i + j] != '\0' && pasar_Minuscula(plataformas[i + j]) == pasar_Minuscula(plataforma_Buscada[j]))
        {
            j++;
        }

        //coincide si leyo todo lo buscado y la plataforma termina ahi
        if(j == largo && (plataformas[i + j] == '\0' || plataformas[i + j] == ',' || plataformas[i + j] == ' '))
        {
            coincide = 1;
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

    printf("=====Ingrese una Plataforma=====\n");
    scanf(" %49[^\n]", plataforma_Buscada);
    limpiar_Buffer();


    Videojuego v;
    int encontrado = 0;


    printf("=====JUEGOS PARA LA PLATAFORMA: %s =====\n", plataforma_Buscada);
    printf("|| %-30s || %-5s || %-9s ||\n", "TITULO", "STOCK", "PRECIO");


    while(fread(&v, sizeof(Videojuego), 1, archivo) == 1)
    {

        if(plataforma_Coincide(v.plataforma, plataforma_Buscada) == 1 && videojuego_Es_Valido(v) == 1)
        {

            printf("|| %-30.30s || %-5d || $%-8g ||\n", v.titulo, v.stock, v.precioAdquisicion);
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


    int id_Buscado = leer_Entero("=====Ingrese el ID del Videojuego que desea Buscar=====\n", 0);


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
