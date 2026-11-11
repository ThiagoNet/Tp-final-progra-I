#include <stdio.h>
#include "fechas.h"
static const int DIAS_POR_MES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Fecha pedirFecha(void)
{

    Fecha f;
    int valida = 0;
    int diasMes;
    do
    {
        printf("Ingrese el dia:\n");
        scanf("%d", &f.dia);

        printf("Ingrese el mes:\n");
        scanf("%d", &f.mes);

        printf("Ingrese el anio:\n");
        scanf("%d", &f.anio);

        if(f.mes >= 1 && f.mes <= 12 && f.anio > 0)
        {
            diasMes = DIAS_POR_MES[f.mes - 1];
            if(f.mes == 2 && ((f.anio % 4 == 0 && f.anio % 100 != 0) || f.anio % 400 == 0))
            {
                diasMes = 29;
            }
            if(f.dia >= 1 && f.dia <= diasMes)
            {
                valida = 1;
            }
        }

        if(valida != 1)
        {
            printf("La fecha no es valida!\n");
        }
    }
    while(valida != 1);

    return f;
}

void mostrarFecha(Fecha f)
{
    printf("%02d/%02d/%d", f.dia, f.mes, f.anio);
}
