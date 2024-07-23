#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


int main(int argc, char* argv[]){

	if (argc!=3){
		printf("Numero incorrecto de argumentos, %d\n",errno);
		perror("Numero incorrecto de argumentos\n");
		exit(-1);
	}
	
	//Intervalo
	int inf=atoi(argv[1]);
	int sup=atoi(argv[2]);
	int medio=(inf+sup)/2;
	
	
	//Descriptores y PIDs de cada hijo esclavo.
	int fd1[2],fd2[2];
	int child_pid1, child_pid2;
	
	//Creamos cauces sin nombre.
	if ( (pipe(fd1) < 0) || (pipe(fd2) < 0) ){
		
		printf("Error en pipe,%d\n", errno);
		perror("Error en pipe\n");
		exit(-1);
	}
	
	
	//Mensaje inicial.
	printf ("Calculo de los numeros primos de un intervalo [%d,%d]\nPrimos: ",inf,sup);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	//Flujo del primer esclavo
	
	if ( (pid1=fork()) < 0){
	
		printf("Error en primer fork, %d\n", errno);
		perror("Error en primer fork.\n");
		exit(-1);
	}
	
	if (pid1==0){ //Primer esclavo
	
		//Cerramos lectura.
		close(fd1[0]);
		
		//Copiamos descriptor de escritura en salida estandar.
		dup2(fd1[1],STDOUT_FILENO);
		
		//Ejecutamos esclavo.
		
		char inicio[10], fin[10];
		sprintf(inicio,"%d",inf);
		sprintf(fin,"%d",medio);
		
		if (execl("./esclavo", "esclavo", inicio, fin, NULL)<0) {
		
		    printf("Error ejecutando el primer esclavo, %d\n", errno);
		    perror("Error ejecutando el primer esclavo");
		    exit(-1);
		}
	
	} //if(esclavo1)
	
	
	else{ //Padre
		
		//Cerramos escritura.
		close(fd1[1]);
		
		//Copiamos descriptor de lectura en entrada estandar.
		dup2(fd1[0],STDIN_FILENO);
		
		while(1){
		
			int leidos=1;
			int primo;
			
			if ( (leidos=read(fd1[0],&primo,sizeof(int))) <0){
			
				printf("Error leyendo datos, %d\n", errno);
               		perror("Error leyendo datos");
                		exit(-1);
			}
			
			//Si no lee mas se sale del bucle.
			if (leidos==0) break;
			
			//Imprimir primo.
			printf("%d ",primo);
		} //while(1)
		
		//Cerramos cauce.
		close(fd1[0]);
		printf("\n");
		
	}//else (padre)
	
	
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	//Flujo del segundo esclavo
	
	if ( (pid2=fork()) < 0){
	
		printf("Error en segundo fork, %d\n", errno);
		perror("Error en segundo fork.\n");
		exit(-1);
	}
		
	if (pid2==0){ //Segundo esclavo
	
		//Cerramos lectura.
		close(fd2[0]);
		
		//Copiamos descriptor de escritura en salida estandar.
		dup2(fd2[1],STDOUT_FILENO);
		
		//Ejecutamos esclavo.
		
		char inicio[10], fin[10];
		sprintf(inicio,"%d",medio+1);
		sprintf(fin,"%d",sup);
		
		if (execl("./esclavo", "esclavo", inicio, fin, NULL)<0) {
		
		    printf("Error ejecutando el primer esclavo, %d\n", errno);
		    perror("Error ejecutando el primer esclavo");
		    exit(-1);
		}
	
	} //if(esclavo2)
	
	
	else{ //Padre
		
		//Cerramos escritura.
		close(fd2[1]);
		
		//Copiamos descriptor de lectura en entrada estandar.
		dup2(fd2[0],STDIN_FILENO);
		
		while(1){
		
			int leidos=1;
			int primo;
			
			if ( (leidos=read(fd2[0],&primo,sizeof(int))) <0){
			
				printf("Error leyendo datos, %d\n", errno);
               		perror("Error leyendo datos");
                		exit(-1);
			}
			
			//Si no lee mas se sale del bucle.
			if (leidos==0) break;
			
			//Imprimir primo.
			printf("%d ",primo);
		} //while(1)
		
		//Cerramos cauce.
		close(fd2[0]);
		printf("\n");
	
	}//else (padre)
	
	

	return 0;
}
