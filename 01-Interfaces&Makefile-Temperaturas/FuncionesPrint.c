/* FuncionesPrint.c
* Definicion de funciones impresion de las tablas de temperatura
* Zupan Lucas
* 20220523
*/

#include "FuncionesPrint.h"
#include "Conversion.h"
#include <stdio.h>

void PrintFila(FILE *tabla, char *formato, double valor1, double valor2){
    fprintf(tabla, formato, valor1, valor2);
}

void PrintFilas(FILE *tabla, double (*funcion)(double), char formato[], int lower, int step, int upper){
    int valorAConvertir;
    for (valorAConvertir = lower; valorAConvertir <= upper; valorAConvertir += step){
        PrintFila(tabla, formato, valorAConvertir, funcion(valorAConvertir));
        
    }
}

void PrintTablaFahrenheit(FILE *tabla ,int lower, int step, int upper){
    fprintf(tabla, "Tabla de celsius a fahrenheit \n");
    PrintFilas(tabla, Fahrenheit, "Celsius: %3.2f  Fahrenheit: %6.2f\n", lower, step, upper);
}

void PrintTablaCelsius(FILE *tabla, int lower, int step, int upper){
    fprintf(tabla, "Tabla de fahrenheit a celsius \n");
    PrintFilas(tabla, Celsius, "Fahrenheit: %3.2f Celsius: %6.2f\n", lower, step, upper);
}


