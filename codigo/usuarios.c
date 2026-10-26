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

while(!valido && fread(&actual, sizeof(Usuario), 1, archivo)== 1){
    if(strcmp(actual.usuario, usuario) == 0 && strcmp(actual.contrasenia, contrasenia) == 0){
     *encontrado = actual;
    valido = 1;
    }
}
fclose(archivo);
return valido;
}



