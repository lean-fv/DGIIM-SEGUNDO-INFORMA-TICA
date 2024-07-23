


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<malloc.h>

int main(int argc, char* argv[]){


	//Creamos vector que almacene argumentos de la orden de Linux. Tendra tamaño argc-2 (caracter < o > y el nombre del archivo.
	char* args[argc-2];
	
	if (argc<2){
		printf("Numero incorrecto de argumentos.\n");
		exit(-1);
	}
	
	for (int i=1; i<=argc-3; i++){
	
		args[i-1]=(char*) malloc(strlen(argv[i])+1);
		strcpy(args[i-1],argv[i]);
	}
	
	//El ultimo es nulo siempre.
	args[argc-3]=NULL;
	
	//Extraemos < o >
	
	char* simbolo=argv[argc-2];
	
	//Extraemos archivo.
	char* file=argv[argc-1];
	
	int fd;
	
	
	
	//Vemos casos de entrada, salida o ninguno.
	
	//Redireccion de entrada.
	if ( (strcmp(simbolo,"<")) ==0){
	
		//Cerramos entrada estandar.
		close(0);
	
		if ( (fd=open(file,O_RDONLY))<0 ){
			printf("Error en open, %d\n",errno);
			perror("Error en open.\n");
			exit(-1);
		}
		
		if ( (fcntl(fd, F_DUPFD,0))<0 ){
		
			printf("Error en fcntl, %d\n",errno);
			perror("Error en fcntl.\n");
			exit(-1);	
		}
		
		if ( (execvp(argv[1],args)<0) ){
		
			printf("Error en execvp, %d\n",errno);
			perror("Error en execvp.\n");
			exit(-1);
		
		}
	
	}
	
	//Redireccion de salida.
	else if ( (strcmp(simbolo,">")) ==0){
	
	
		//Cerramos salida estandar.
		close(1);
	
		if ( (fd=open(file, O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU))<0 ){
			printf("Error en open, %d\n",errno);
			perror("Error en open.\n");
			exit(-1);
		}
		
		if ( (fcntl(fd, F_DUPFD,1))<0 ){
		
			printf("Error en fcntl, %d\n",errno);
			perror("Error en fcntl.\n");
			exit(-1);
		
		}
		
		if ( (execvp(argv[1],args)<0) ){
		
			printf("Error en execvp, %d\n",errno);
			perror("Error en execvp.\n");
			exit(-1);
		}
	
	
	}
	
	
	//No se encuentra el simbolo.
	else {
	
		printf("No se ha encontrado simbolo < o >\n");
		exit(-1);
		
	}
	
	
	return 0;
}
