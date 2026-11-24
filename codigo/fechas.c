#include <stdio.h>
#include "fechas.h"
#include "validaciones.h"

static const int DIAS_POR_MES[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Fecha pedirFecha(void)
{

    Fecha f = {0, 0, 0};
    int valida = 0;
    int diasMes;

    do
    {
        f.dia = leer_Entero("Ingrese el dia: ", 1);
        f.mes = leer_Entero("Ingrese el mes: ", 1);
        f.anio = leer_Entero("Ingrese el anio: ", 1);

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
