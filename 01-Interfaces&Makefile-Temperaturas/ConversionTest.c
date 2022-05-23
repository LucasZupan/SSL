/* ConversionTest.c
* Tests de las funciones de Conversion.c
* Zupan Lucas
* 20220523
*/

#include "Conversion.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main (void) {

    //Pruebas de Conversion a Fahrenheit
    assert(Fahrenheit(0)  == 32);
    assert(Fahrenheit(0)  != 25);
    assert(Fahrenheit(15) == 59);
    assert(Fahrenheit(15) != 0);

    //Pruebas de Conversion a Celsius
    assert(Celsius(32)  == 0);
    assert(Celsius(25)  != 0);
    assert(Celsius(59) == 15);
    assert(Celsius(0) != 15);

    printf("Los test se han ejecutado correctamente! \n");
    system("pause");

    return 0;
}