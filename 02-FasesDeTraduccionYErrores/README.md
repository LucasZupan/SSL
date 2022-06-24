# Trabajo #02 - Fases de la traducción y errores

### Objetivo: 
- Identificar las fases de traducción y errores.
---
### Tareas:
1. Investigar las funcionalidades y opciones que su compilador presenta para limitar el inicio y fin de las fases de traducción.
2. La siguiente tarea es poner en uso lo que se encontró. Para eso se debe transcribir al readme.md cada comando ejecutado y su resultado
o error correspondiente a la siguiente secuencia de pasos. También en readme.md se vuelcan las conclusiones y se resuelven los puntos solicitados. Para claridad, mantener en readme.md la misma numeración de la secuencia de pasos.
---

# 1. Investigación

> #### Comandos

| Comando     						| Resultado												|
|-----------------------------------|-------------------------------------------------------|
| gcc -E source.c > source.i		| Devuelve el preprocesamiento.							|
| gcc -S source.c					| Devuelve el programa en assembler. 					|
| gcc -c source.c					| Devuelve código objeto, para fabricar un ejecutable 	|

> #### Etapas de compilación.
El proceso de compilación involucra cuatro etapas sucesivas: **preprocesamiento**, **compilación**, **ensamblado** y **enlazado**. Para pasar de un programa fuente escrito por un humano a un archivo ejecutable es necesario realizar estas cuatro etapas en forma sucesiva. Los comandos gcc y g++ son capaces de realizar todo el proceso de una sola vez.



# 2- Etapas

### 1 - Preprocesador

#### a. Escribir *hello2.c* 

```c
#include <stdio.h>

int/*medio*/main(void){
     int i=42;
      prontf("La respuesta es %d\n");
```

#### b. Preprocesar hello2.c, no compilar, y generar hello2.i. Analizar su contenido. 

Comando utilizado: 

	gcc -E hello2.c -o hello2.i

Contenido de **hello2.i**:

> En el archivo "hello2.i" se ve el código en lenguaje C, pero se ven modificadas ciertas líneas. Lo que se realizó, fue la **interpretación de las directivas** al preprocesador. Un ejemplo puede ser el reemplazo de los comentarios por `" "`. A su vez se incluye el header stdio.h ocupando mas de 700 lineas.

#### c. Escribir *hello3.c*, una nueva variante.

```c
int printf(const char * restrict s, ...);

int main(void){
     int i=42;
     prontf("La respuesta es %d\n");
```

#### d. Investigar e indicar la semántica de la primera línea.

> Declaracion de una funcion que retorna un entero, espera por lo menos 1 argumento.
El primer argumento es un puntero a un char, con este puntero no puedo modificar a lo que apunta (por eso el const). El restricted dice que el unico que apunta a "s" es ese puntero, no hay otro mas. En resumidas cuentas,  es la manera de decir "cadena constante"

#### e. Preprocesar *hello3.c*, no compilar, y generar *hello3.i*. Buscar diferencias entre hello3.c y hello3.i.

Comando utilizado: 

	gcc -E hello3.c -o hello3.i

Contenido de **"hello3.i"**:


	# 1 "hello3.c"
	# 1 "<built-in>"
	# 1 "<command-line>"
	# 1 "hello3.c"
	int printf(const char *s, ...);
	int main(void){
	int i=42;
	prontf("La respuesta es %d\n");

Contenido de **"hello3.c"**:

	int printf(const char *s, ...);
	int main(void){
	int i=42;
	prontf("La respuesta es %d\n");

> Al no incluir el header stdio.h el archivo queda mucho mas compacto al no estar esas mas de 700 lineas de codigo

### 2. Compilación

#### a. Compilar el resultado y generar *hello3.s*, no ensamblar.

Comando utilizado:

	gcc -S hello3.c

Error mostrado por consola:

```c
hello3.c: In function 'main':
hello3.c:5:1: warning: implicit declaration of function 'prontf'; did you mean 'printf'? [-Wimplicit-function-declaration]
    5 | prontf("La respuesta es %d\n");
      | ^~~~~~
      | printf
	hello3.c:5:1: error: expected declaration or statement at end of input
```

#### b. Corregir solo los errores, no los warnings, en el nuevo archivo *hello4.c* y empezar de nuevo, generar *hello4.s*, no ensamblar.

Contenido de **"hello4.c"**:

```c
	int  printf(const  char *s, ...);
	int  main(void){
	int i=42;
	printf("La respuesta es %d\n");}
```

Comando utilizado:

	gcc -S hello4.c

Contenido de **"hello4.s"**:

```c
	.file	"hello4.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "La respuesta es %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$42, -4(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	prontf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev6, Built by MSYS2 project) 11.2.0"
	.def	prontf;	.scl	2;	.type	32;	.endef
```

#### c. Leer *hello4.s*, investigar sobre lenguaje ensamblador, e indicar de formar sintética cual es el objetivo de ese código.

> La compilación resulta en un archivo que contiene el programa en código Assembler. Este es utilizado posteriormente para ser ensamblado y concluir en el archivo objeto.

#### d. Ensamblar *hello4.s* en *hello4.o*, no vincular.

Comando utilizado:

	gcc -c  hello4.s 

## 3. Vinculación

#### a. Vincular *hello4.o* con la biblioteca estándar y generar el ejecutable.

Comando utilizado:

	gcc hello4.o -o hello.exe

Error resultante:

	hello4.o:hello4.c:(.text+0x1e): undefined reference to `prontf'
	collect2.exe: error: ld returned 1 exit status

#### b. Corregir en hello5.c y generar el ejecutable. Solo corregir lo necesario para que vincule.

Contenido de **"hello5.c"**:

```c
int printf(const char * restrict s, ...);

int main(void){
int i=42;
printf("La respuesta es %d\n");
```

Comando utilizado:

	gcc hello5.c -o hello5.exe

#### c. Ejecutar y analizar el resultado.

Resultado obtenido:

	"La respuesta es -110029856"

> El resultado es erróneo debido a que no se especifica la variable a ser mostrada en el printf.

### 4. Corrección de Bug

#### a. Corregir en *hello6.c* y empezar de nuevo; verificar que funciona como se espera.

Contenido de **"hello6.c"**:

```c
	int printf(const char * restrict s, ...);

	int main(void){
	int i=42;
	printf("La respuesta es %d\n", i);
```

Comando utilizado:

	gcc hello6.c -o hello6.exe

Resultado obtenido:

	"La respuesta es 42" ✅

## 5. Remoción de prototipo

#### a. Escribir hello7.c, una nueva variante:

Contenido de **"hello7.c"**:

```c
	int main(void){
		int i=42;
		printf("La respuesta es %d\n", i);
		}
```

#### b. Explicar porqué funciona.
> *EN TIEMPO DE LINKEO BUSCA SIEMPRE LA LIBRERÍA ESTÁNDAR*
> La variante anterior compila porque printf está declarada implícitamente. Arroja el siguiente warning:

	hello7.c: In function 'main':
	hello7.c:3:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
	     printf("La respuesta es %d\n", i);
	     ^~~~~~
	hello7.c:3:5: warning: incompatible implicit declaration of built-in function 'printf'
	hello7.c:3:5: note: include '<stdio.h>' or provide a declaration of 'printf'

> El programa se ejecuta y funciona porque por default gcc tiene a libc en sus programas, otros compiladores no lo tienen y el programa no compila. Pero no se deberian ignorar los errores del compilador, para que sea correcta la solucion habria que incluir a stdio.h. No cumple con el estandar de C de no permitir la declaracion implicita.

## 6. Compilación Separada: Contratos y Módulos

#### a. Escribir studio1.c (sí, studio1, no stdio) y hello8.c.

La unidad de traducción studio1.c tiene una implementación de la función prontf, que es solo un wrappwer1 de la función estándar printf:
  ~~~
  void prontf(const char* s, int i){
    printf("La respuesta es %d\n", i);
  }
  ~~~

La unidad de traducción hello8.c, muy similar a hello4.c, invoca a prontf, pero no incluye ningún header.
  ~~~
  int main(void){
  int i=42;
  prontf("La respuesta es %d\n", i);
  }
  ~~~

#### b. Investigar como en su entorno de desarrollo puede generar un programa ejecutable que se base en las dos unidades de traducción       (i.e, archivos fuente, archivos con extensión .c). Luego generar ese ejecutable y probarlo.

 Mi entorno de desarrolo es VSCode, así que siempre compilo usando la terminal, y para compilar mas de un archivo .c simplemente hay que escribir ambos archivos en el comando para que el compilador los use como fuentes. El comando quedaría "gcc hello8.c studio1.c -std=c18 -o hello8.ex".  
  Como el main no tiene disponible el prototipo de la función "prontf", y "prontf" tampoco tiene el prototipo de "printf", se crea el ejecutable pero surgen los siguientes warnings:
  ~~~
  hello8.c: In function ‘main’:
  hello8.c:3:2: warning: implicit declaration of function ‘prontf’ [-Wimplicit-function-declaration]
      3 |  prontf("La respuesta es %d\n", i);
        |  ^~~~~~
  studio1.c: In function ‘prontf’:
  studio1.c:2:3: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
      2 |   printf("La respuesta es %d\n", i);
        |   ^~~~~~
  studio1.c:2:3: warning: incompatible implicit declaration of built-in function ‘printf’
  studio1.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
    +++ |+#include <stdio.h>
      1 | void prontf(const char* s, int i){
  ~~~
  El ejecutable funciona correctamente.  

#### c. Responder ¿qué ocurre si eliminamos o agregamos argumentos a la invocación de prontf? Justifique.

Si eliminamos o agregamos argumentos a la invocación no cambia nada, al finalizar todos los pasos surgen los mismos warnings detallados en el punto b). Esto se debe a que al no tener disponibles los prototipos de las funciones, es decir, sus contratos, a la hora de hacer todos los pasos para crear el ejecutable no se tiene información de cúales serían los argumentos que debería recibir la función "prontf" y que tipo de dato debería retornar. Por lo tanto no hay errores y solo muestra los mismos warnings.  
Particularmente si agregamos argumentos, simplemente en la ejecución se va a imprimir el printf con el texto "La respuesta es: " y luego el segundo parametro que le pasemos a la funcion prontf, si es un entero definido como "i", imprime 42, si es una cadena de texto imprime un numero raro que es lo que interpretó de dicha cadena.  
En el caso de que le saquemos argumentos va a ocurrir algo que paso en un punto anterior, como no recibe un segundo argumento prontf, printf interpreta lo que hay en un espacio de memoria del tamaño de un int y lo pone en lugar del %d.  

#### d. Revisitar el punto anterior, esta vez utilizando un contrato de interfaz en un archivo header.

* Escribir el contrato en studio.h.
    ~~~
    #ifndef _STUDIO_H_INCULDED_
    #define _STUDIO_H_INCULDED_
    void prontf(const char*, int);
    #endif    
    ~~~
* Escribir hello9.c, un cliente que sí incluye el contrato.
    ~~~
    #include "studio.h" // Interfaz que importa
    int main(void){
    int i=42;
    prontf("La respuesta es %d\n", i);
    }   
    ~~~
* Escribir studio2.c, el proveedor que sí incluye el contrato.
    ~~~
    #include "studio.h" // Interfaz que exporta
    #include <stdio.h> // Interfaz que importa
    void prontf(const char* s, int i){
    printf("La respuesta es %d\n", i);
    }
    ~~~

* Responder: ¿Qué ventaja da incluir el contrato en los clientes y en el proveedor.  
      
    La ventaja que da incluir el contrato en los clientes y en el proveedor es que ayuda al programador a asegurarse de que invocó las funciones de la manera que fueron diseñadas. Corrobora en tiempo de compilación que las funciones fueron invocadas de la manera correcta, es decir, que reciban como argumentos la cantidad que el prototipo indica, de esta manera no habrá invocaciones ambiguas, sino bien especificadas. 
    Sorpresivamente solo arroja un warning y no un error cuando la función espera un tipo de dato y en la invocación se le asigna otro.  

    Por ejemplo si quiero agregar argumentos de más que no estén contemplados en el prototipo, el compilador me arroja el siguiente error:  
    ~~~
    hello9.c: In function ‘main’:
    hello9.c:4:2: error: too many arguments to function ‘prontf’
        4 |  prontf("La respuesta es %d\n", i,i);
          |  ^~~~~~
    In file included from hello9.c:1:
    studio.h:3:6: note: declared here
        3 | void prontf(const char*, int);
          |      ^~~~~~
    ~~~  
    Pero si la función es invocada con la cantidad correcta de argumentos pero el tipo de dato no coincide con el prototipo (en este caso, en vez de invocar prontf con la variable "i", la invoqué con una cadena de caracteres) arroja el siguiente warning:
    ~~~
    hello9.c: In function ‘main’:
    hello9.c:4:33: warning: passing argument 2 of ‘prontf’ makes integer from pointer without a cast [-Wint-conversion]
        4 |  prontf("La respuesta es %d\n", "estoEsUnTexto");
          |                                 ^~~~~~~~~~~~~~~
          |                                 |
          |                                 char *
    In file included from hello9.c:1:
    studio.h:3:26: note: expected ‘int’ but argument is of type ‘char *’
        3 | void prontf(const char*, int);
          |                          ^~~
    ~~~  
    Al probar el ejecutable, funciona pero imprime un valor raro, que es lo que interpreta como un int de un espacio de memoria al cual no le fue asignado un valor entero: 
    ~~~
    La respuesta es -370335740
    ~~~  

###  Punto Extra  
  a) Investigue sobre bibliotecas. ¿Qué son? ¿Se puden distribuir? ¿Son portables? ¿Cuáles son sus ventajas y desventajas?  
    
  Las bibliotecas son colecciones de archivos de código objeto, resultantes de la compilación de código de implementaciones funcionales en un determinado lenguaje de programación. Las bilbiotecas ayudan con funcionalidades al programador, ya que puede reutilizar lo que se haya desarrollado en las mismas.  
  Las bibilotecas al ser código objeto, están compiladas para la arquitectura en donde fueron compiladas justamente. Una arquitectura diferente no entendería el código objeto, por lo tanto no son portables. La única manera sería que ambas computadoras tuvieran la misma arquitectura.  
  **Ventajas:**  
  * Ayudan a mantener prolijo y entendible el código al abstraer funcionalidades que utiliza el programador.
  * Ayuda a la reutilización de código, ahorrandole tiempo y trabajo al programador.
  * Suponen tener todas las funcionalidades bien testeadas.
  * El creador de la biblioteca solo comparte el código objeto, así que puede ocultar la implementación en el lenguaje de programación que utilice
    
  **Desventajas:**
  * El usuario de una biblioteca no puede ver las implementaciones de las funciones, solo sus contratos.
  * No son portables