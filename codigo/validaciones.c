#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "validaciones.h"

void limpiar_Buffer(void)
{

    int c;

    while((c = getchar()) != '\n' && c != EOF)
    {
    }

}

//Lee tecla por tecla y solo acepta digitos (y un punto si permite_Punto es 1).
//Guarda lo escrito en texto y devuelve la cantidad de caracteres.
//Enter solo confirma si hay algo escrito y no termina en punto.
static int leer_Numeros(char *texto, int max_Largo, int permite_Punto)
{

    int largo = 0;
    int hay_Punto = 0;
    int decimales = 0;
    int terminado = 0;
    int tecla;

    texto[0] = '\0';

    while(terminado == 0)
    {

        tecla = _getch();

        if(tecla == 0 || tecla == 224)
        {
            //tecla especial (flechas, F1, etc): hay que descartar el segundo codigo
            _getch();
        }
        else if(tecla == '\r')
        {

            if(largo > 0 && texto[largo - 1] != '.')
            {
                terminado = 1;
            }

        }
        else if(tecla == 8)
        {

            if(largo > 0)
            {

                largo--;

                if(texto[largo] == '.')
                {
                    hay_Punto = 0;
                    decimales = 0;
                }
                else if(hay_Punto == 1)
                {
                    decimales--;
                }

                texto[largo] = '\0';
                printf("\b \b");
                fflush(stdout);

            }

        }
        else if(tecla >= '0' && tecla <= '9')
        {

            if(largo < max_Largo && !(hay_Punto == 1 && decimales >= 2))
            {

                texto[largo] = (char)tecla;
                largo++;
                texto[largo] = '\0';

                if(hay_Punto == 1)
                {
                    decimales++;
                }

                putchar(tecla);
                fflush(stdout);

            }

        }
        else if(tecla == '.' && permite_Punto == 1)
        {

            if(hay_Punto == 0 && largo > 0 && largo < max_Largo)
            {

                texto[largo] = '.';
                largo++;
                texto[largo] = '\0';
                hay_Punto = 1;

                putchar('.');
                fflush(stdout);

            }

        }

    }

    printf("\n");

    return largo;

}

int leer_Entero(const char *mensaje, int minimo)
{

    char texto[20];
    int valor = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);
        fflush(stdout);

        leer_Numeros(texto, 9, 0);
        valor = atoi(texto);

        if(valor < minimo)
        {
            printf("Valor invalido (minimo %d).\n", minimo);
        }
        else
        {
            ok = 1;
        }

    }
    while(ok == 0);

    return valor;

}

int leer_Opcion(const char *mensaje, int minimo, int maximo)
{

    char texto[20];
    int valor = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);
        fflush(stdout);

        leer_Numeros(texto, 9, 0);
        valor = atoi(texto);

        if(valor < minimo || valor > maximo)
        {
            printf("Opcion invalida (entre %d y %d).\n", minimo, maximo);
        }
        else
        {
            ok = 1;
        }

    }
    while(ok == 0);

    return valor;

}

float leer_Precio(const char *mensaje)
{

    char texto[20];
    float valor = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);
        fflush(stdout);

        leer_Numeros(texto, 12, 1);
        valor = (float)atof(texto);

        if(valor <= 0)
        {
            printf("El precio debe ser mayor a 0.\n");
        }
        else
        {
            ok = 1;
        }

    }
    while(ok == 0);

    return valor;

}

void leer_Digitos(const char *mensaje, char *destino, int tam, int minimo_Digitos)
{

    char texto[50];
    int largo = 0;
    int ok = 0;

    do
    {

        printf("%s", mensaje);
        fflush(stdout);

        largo = leer_Numeros(texto, tam - 1, 0);

        if(largo < minimo_Digitos)
        {
            printf("Debe tener al menos %d digitos.\n", minimo_Digitos);
        }
        else
        {
            ok = 1;
        }

    }
    while(ok == 0);

    strcpy(destino, texto);

}

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
