#include <stdio.h>
#include <string.h>
#include "usuarios.h"

void crearAdminPorDefecto(void){
FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");
if(archivo != NULL){
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
if(archivo == NULL){
    printf("No se pudo acceder al archivo\n");
    return;
}
fwrite(&admin, sizeof(Usuario), 1, archivo);
fclose(archivo);
}
int validarCredenciales(const char *usuario, const char *contrasenia, Usuario *encontrado){
FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");
if(archivo == NULL){
    printf("No se pudo abrir el archivo\n");
    return 0;
}
Usuario actual;
int valido = 0;

while(!valido && fread(&actual, sizeof(Usuario), 1, archivo)== 1){
    if(strcmp(actual.usuario, usuario) == 0 && strcmp(actual.contrasenia, contrasenia) == 0){
     *encontrado = actual;
    valido = 1;
    }
}
fclose(archivo);
return valido;
}

int login(Usuario *usuarioLogueado){

char usuario[20];
char contrasenia[20];
int acceso = 0;
int intentos = 0;

printf("----INICIO DE SESION----\n");
while(!acceso && intentos < 3){
    printf("Ingrese el usuario:\n");
    scanf("%19s", usuario);
    printf("Ingrese su contrasenia\n");
    scanf("%19s", contrasenia);
    acceso = validarCredenciales(usuario, contrasenia, usuarioLogueado);
    if(acceso == 0){
      intentos++;
      printf("Credenciales incorrectas. Intentos: (%d/3)\n", intentos);
    }
}
return acceso;
}




