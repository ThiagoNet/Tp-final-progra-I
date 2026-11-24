#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include "validaciones.h"

#define INTENTOS_LOGIN 3

void crearAdminPorDefecto(void)
{
    FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");
    if(archivo != NULL)
    {
        fclose(archivo);
        return;
    }
    Usuario admin = {0};
    strcpy(admin.usuario, "admin");
    strcpy(admin.contrasenia, "admin");

    strcpy(admin.persona.dni, "40506080");
    strcpy(admin.persona.nombre, "admin");
    strcpy(admin.persona.rol, "admin");

    archivo = fopen(ARCHIVO_USUARIOS, "wb");
    if(archivo == NULL)
    {
        printf("No se pudo acceder al archivo\n");
        return;
    }
    fwrite(&admin, sizeof(Usuario), 1, archivo);
    fclose(archivo);
}

int validarCredenciales(const char *usuario, const char *contrasenia, Usuario *encontrado)
{

    FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");
    if(archivo == NULL)
    {
        return 0;
    }

    Usuario actual;
    int valido = 0;

    while(!valido && fread(&actual, sizeof(Usuario), 1, archivo) == 1)
    {
        if(strcmp(actual.usuario, usuario) == 0 && strcmp(actual.contrasenia, contrasenia) == 0)
        {
            *encontrado = actual;
            valido = 1;
        }
    }

    fclose(archivo);
    return valido;
}

//Da hasta 3 intentos. Devuelve 1 si entro y 0 si fallo los 3
int login(Usuario *usuarioLogueado)
{

    char usuario[20];
    char contrasenia[20];
    int intento = 0;
    int valido = 0;

    while(intento < INTENTOS_LOGIN && valido == 0)
    {

        printf("Usuario:\n");
        scanf("%19s", usuario);
        limpiar_Buffer();

        printf("Contrasenia:\n");
        scanf("%19s", contrasenia);
        limpiar_Buffer();

        valido = validarCredenciales(usuario, contrasenia, usuarioLogueado);

        if(valido == 0)
        {

            intento++;

            if(intento < INTENTOS_LOGIN)
            {
                printf("Usuario o contrasenia incorrectos. Intentos restantes: %d\n\n", INTENTOS_LOGIN - intento);
            }

        }

    }

    return valido;

}
