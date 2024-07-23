/*
Titulo: Ejercicio3_3_7.c

Fecha:	09/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena “bg”. Nuesto programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena “bg” y en background en caso contrario. Si el programa tiene argumentos hay que ejecutarlo con éstos.

Opciones: Presencia del argumento <bg>: el programa pasado como primer argumento se ejecuta en background. En caso contrario, en foregound.

Uso: ./Ejercicio3_1_7 <nombre_programa> <argumentos_programa> [<bg>]
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(int argc, char* argv[]){

	
	int child_pid;
	char* args[argc];
	
	//Contruimos vector con los argumentos del programa que se ejecutará.
	for (int i=1; i<argc; i++){
	
		args[i-1]= (char*) malloc(strlen(argv[i])+1);
		strcpy(args[i-1],argv[i]);
	}
	
	//El ultimo siempre es nulo.
	args[argc]=NULL;
	
	//Creamos proceso hijo.
	if ((child_pid=fork())<0){
		printf("Error en fork(), %d\n",errno);
		perror("Error en fork()\n");
	}
	
	else if (child_pid==0){
	
		if ( (execvp(argv[1],args) )<0){
			printf("Error en execpv, %d\n", errno);
			perror("Error en execpv\n");
		}
	}
	
	//Obtenemos estado.
	int estado;
	wait(&estado);
	printf("El hijo de PID %d ha finalizado con estado %d.\n", child_pid, estado>>8);
	
	return 0;
}
