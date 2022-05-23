/* TablasDeConversion.c
* Invocacion a funciones de impresion de las tablas de temperatura
* Zupan Lucas
* 20220523
*/

#include "Conversion.h"
#include "FuncionesPrint.h"
#include <stdio.h>
#include <stdlib.h>



int main (void) {

    const int LOWER = 0;
    const int UPPER = 300;
    const int STEP = 20;

    FILE *opening;
    opening = fopen("TablasTemperatura.txt", "w");

    PrintTablaCelsius (opening, LOWER, STEP, UPPER);
    fprintf(opening, "\n");
    PrintTablaFahrenheit (opening, LOWER, STEP, UPPER);

    fclose(opening);

    printf ("Las tablas se imprimieron con exito \n");

    system("pause");

    return 0;
}