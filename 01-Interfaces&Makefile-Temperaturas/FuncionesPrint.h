/* FuncionesPrint.h
* Header de FuncionesPrint.c
* Zupan Lucas
* 20220523
*/

#include <stdio.h>

void PrintFila(FILE *tabla, char *, double, double); //Recibe como parámetros el string de formato y los dos valores a mostrar, e imprime la fila

void PrintFilas(FILE *tabla, double (*funcion)(double), char[], int lower, int step, int upper); //Recibe como como parámetros el formato de los string a imprimir, los datos de los limites, el step y un puntero a la funcion que debe ejecutar, calcula los valores e imprime las filas 

void PrintTablaFahrenheit(FILE *tabla, int lower, int step, int upper); //Recibe como parámetros solo los límites y el step, que luego pasará a la función PrintFilas

void PrintTablaCelsius(FILE *tabla, int lower, int step, int upper); //Recibe como parámetros solo los límites y el step, que luego pasará a la función PrintFilas