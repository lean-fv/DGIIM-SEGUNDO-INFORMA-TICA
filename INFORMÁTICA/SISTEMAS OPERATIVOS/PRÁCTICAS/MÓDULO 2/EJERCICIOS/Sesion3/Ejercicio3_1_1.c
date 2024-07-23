/*
Titulo: Ejercicio3_1_1.c

Fecha:	09/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o no usando igualmente la salida estándar.

Opciones:

Uso: ./Ejercicio3_1_1 <numero entero>
*/


#include <dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <sys/mman.h>
#include <linux/sched.h>
#include <malloc.h>
#include<sched.h>
#include <ftw.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char** argv){

	if (argc!=2){
		printf("Numero de argumentos incorrecto.\n");
		exit(-1);
	}
	
	int integer=atoi(argv[1]);
	pid_t child_pid;
	
	//Creamos proceso hijo.
	if ((child_pid=fork())<0){
	
		printf("Error en fork(),%d\n", errno);
		perror("Error en fork()\n");
	}
	
	//Proceso hijo.
	else if (child_pid==0){
		if (integer%2==0) printf("El entero es par.\n");
		else printf("El entero es impar.\n");
		printf("PID del que crea el proceso: %d\nPID Hijo: %d\n", getppid(),getpid());
	}
	
	//Proceso padre.
	else{
		if (integer%4==0) printf("El entero es divisible por 4.\n");
		else printf("El entero no es divisible por 4.\n");
		printf("PID propio programa en ejecucion(Padre): %d\nPID Hijo: %d\n\n",getpid(),child_pid);
	}

	return 0;
}
