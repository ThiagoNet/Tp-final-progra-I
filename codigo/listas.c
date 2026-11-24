#include <stdio.h>
#include <string.h>
#include "listas.h"
#include "validaciones.h"

static const char *PLATAFORMAS[CANT_PLATAFORMAS] = {"Xbox Series", "PS5", "Nintendo Switch 2", "PC"};
static const char *GENEROS[CANT_GENEROS] = {"Accion", "Aventura", "RPG", "Deportes", "Estrategia", "Carreras", "Simulacion"};
static const char *ROLES[CANT_ROLES] = {"cliente", "vendedor", "cajero", "gerente", "admin"};

//Muestra una lista numerada y deja elegir una sola opcion
static void elegir_De_Lista(const char *titulo, const char *lista[], int cantidad, char *destino, int tam)
{

    int i;
    int opcion;

    printf("\n=====%s=====\n", titulo);

    for(i = 0; i < cantidad; i++)
    {
        printf("%d. %s\n", i + 1, lista[i]);
    }

    opcion = leer_Opcion("Elija una opcion: ", 1, cantidad);

    strncpy(destino, lista[opcion - 1], tam - 1);
    destino[tam - 1] = '\0';

}

void elegir_Plataformas(char *destino, int tam)
{

    int marcadas[CANT_PLATAFORMAS] = {0};
    int i;
    int opcion;
    int cantidad_Marcadas;
    int terminado = 0;

    do
    {

        printf("\n=====PLATAFORMAS=====\n");

        cantidad_Marcadas = 0;

        for(i = 0; i < CANT_PLATAFORMAS; i++)
        {

            if(marcadas[i] == 1)
            {
                printf("%d. [X] %s\n", i + 1, PLATAFORMAS[i]);
                cantidad_Marcadas++;
            }
            else
            {
                printf("%d. [ ] %s\n", i + 1, PLATAFORMAS[i]);
            }

        }

        printf("0. Confirmar\n");

        opcion = leer_Opcion("Marque o desmarque una plataforma: ", 0, CANT_PLATAFORMAS);

        if(opcion == 0)
        {

            if(cantidad_Marcadas == 0)
            {
                printf("Debe elegir al menos una plataforma.\n");
            }
            else
            {
                terminado = 1;
            }

        }
        else
        {
            marcadas[opcion - 1] = !marcadas[opcion - 1];
        }

    }
    while(terminado == 0);

    destino[0] = '\0';

    for(i = 0; i < CANT_PLATAFORMAS; i++)
    {

        if(marcadas[i] == 1 && strlen(destino) + strlen(PLATAFORMAS[i]) + 2 < (size_t)tam)
        {

            if(destino[0] != '\0')
            {
                strcat(destino, ", ");
            }

            strcat(destino, PLATAFORMAS[i]);

        }

    }

}

void elegir_Una_Plataforma(char *destino, int tam)
{

    elegir_De_Lista("PLATAFORMAS", PLATAFORMAS, CANT_PLATAFORMAS, destino, tam);

}

void elegir_Genero(char *destino, int tam)
{

    elegir_De_Lista("GENEROS", GENEROS, CANT_GENEROS, destino, tam);

}

void elegir_Rol(char *destino, int tam)
{

    elegir_De_Lista("ROLES", ROLES, CANT_ROLES, destino, tam);

}
