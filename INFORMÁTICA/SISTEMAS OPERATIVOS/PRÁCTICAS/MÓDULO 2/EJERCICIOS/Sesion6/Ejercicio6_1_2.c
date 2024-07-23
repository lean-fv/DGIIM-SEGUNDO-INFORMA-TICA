
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(int argc, char* argv[]){


	if (argc < 4){
		printf("Numero  incorrecto de argumentos.\n");
		exit(-1);
	}
	
	
	//Almacena posicion de "|".
	int i=0;
	
	//Vemos en que posicion esta "|".
	while(strcmp(argv[i],"|") != 0) i++;
	
	if (!i){
		printf("No se ha encontrado cauce.\n");
		exit(-1);
	}
	
	//Creamos vectores de argumentos de las ordenes.
	
	//char** orden1= (char**) malloc(sizeof(char*) * (i+1));
	char** orden1;
	
	for (int j=1; j<i; i++){
		orden1[j-1]= (char*) malloc (strlen(argv[j]) +1);
		strcpy(orden1[j-1],argv[j]);
	}
	
	orden1[i]=NULL;
	
	//char** orden2= (char**) malloc(sizeof(char*) * (argc-i+1));
	char** orden2;
	
	for (int j=1; j<(argc-i); i++){
		orden2[j-1]= (char*) malloc (strlen(argv[j+i]) +1);
		strcpy(orden2[j-1],argv[j+i]);
	}
	
	orden2[argc-i]=NULL;
	
	//Cauce
	int fd[2];
	if ( (pipe(fd)) <0){
		printf("Error en pipe(), %d\n", errno);
		perror("Error en pipe().\n");
		exit(-1);
	}
	
	//Hijo
	int childpid;
	if ( (childpid=fork()) <0){
		printf("Error en fork(), %d\n", errno);
		perror("Error en fork().\n");
		exit(-1);
	}
	
	if (childpid==0){ //Proceso hijo (entrada de datos).
		
		//Cerramos escritura
		close(fd[1]);
		
		//Cerramos entrada estandar para duplicar despues.
		close(0);
		
		if ( (fcntl(fd[0],F_DUPFD,0)) <0){
			printf("Error en fcntl(), %d\n", errno);
			perror("Error en fcntl().\n");
			exit(-1);
		}
		
		if ( (execvp(argv[i+1],orden2)) <0){
			printf("Error en execvp(), %d\n", errno);
			perror("Error en execvp().\n");
			exit(-1);
		}
		
	} //Proceso hijo
	
	
	else{ //Proceso padre (salida de datos).
	
		//Cerramos lectura
		close(fd[0]);
		
		//Cerramos salida estandar para duplicar despues.
		close(1);
		
		if ( (fcntl(fd[1],F_DUPFD,1)) <0){
			printf("Error en fcntl(), %d\n", errno);
			perror("Error en fcntl().\n");
			exit(-1);
		}
		
		if ( (execvp(argv[1],orden1)) <0){
			printf("Error en execvp(), %d\n", errno);
			perror("Error en execvp().\n");
			exit(-1);
		}
		
	} //Proceso padre
	

	return 0;
}
