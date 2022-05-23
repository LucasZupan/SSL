/* Conversion.c
* Definicion de funciones de conversion de temperatura
* Zupan Lucas
* 20220523
*/

#include "Conversion.h"

double Fahrenheit (double celsius) {
    return (celsius * 9/5) +32;
}

double Celsius (double fahrenheit) {
    return  (fahrenheit - 32) * 5 / 9;
}