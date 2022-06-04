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

> El programa se ejecuta y funciona porque por default gcc tiene a libc en sus programas. Pero no se deberian ignorar los errores del compilador, para que sea correcta la solucion habria que incluir a stdio.h


