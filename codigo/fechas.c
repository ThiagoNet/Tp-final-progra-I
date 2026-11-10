#include <stdio.h>
#include "fechas.h"
static const int DIAS_POR_MES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Fecha pedirFecha(void){

Fecha f;
int valida = 0;
do{
    printf("Ingrese el dia:\n");
    scanf("%d", &f.dia);

    printf("Ingrese el mes:\n");
    scanf("%d", &f.mes);

    printf("Ingrese el anio:\n");
    scanf("%d", &f.anio);
    if(f.mes >= 1 && f.mes <= 12 && f.dia >= 1 && f.dia <= DIAS_POR_MES[f.mes - 1] && f.anio > 0){
            valida = 1;
    }else{
    printf("La fecha no es valida!\n");
    }
}while(valida != 1);

return f;
}

void mostrarFecha(Fecha f){
printf("%02d/%02d/%d", f.dia, f.mes, f.anio);
}
