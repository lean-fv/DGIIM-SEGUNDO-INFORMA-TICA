/*
Titulo: prueba_pid2.c

Fecha:	09/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Programa de prueba para las funciones de obtención de pid's.

Opciones:
Uso: ./prueba_pid2
*/


#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(void) {

printf("Identificador de usuario: %d\n", getuid());
printf("Identificador de usuario efectivo: %d\n", geteuid());
printf("Identificador de grupo: %d\n", getgid());
printf("Identificador de grupo efectivo: %d\n", getegid());

}





