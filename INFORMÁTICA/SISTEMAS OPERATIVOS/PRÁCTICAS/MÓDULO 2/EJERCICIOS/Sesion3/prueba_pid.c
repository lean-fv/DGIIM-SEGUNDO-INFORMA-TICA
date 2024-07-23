/*
Titulo: prueba_pid.c

Fecha:	09/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Programa de prueba para las funciones de obtención de pid's.

Opciones:
Uso: ./prueba_pid
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(void){

pid_t id_proceso;
pid_t id_padre;

id_proceso = getpid();
id_padre = getppid();

printf("Identificador de proceso: %d\n", id_proceso);
printf("Identificador del proceso padre: %d\n", id_padre);

}
