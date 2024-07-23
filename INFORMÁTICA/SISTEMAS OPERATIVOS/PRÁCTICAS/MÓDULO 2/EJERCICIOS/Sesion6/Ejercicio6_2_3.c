
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


/*
El programa ilustra cómo el kernel comprueba que puede darse una situación de interbloqueo en el bloqueo de archivos. Se puede ver que el kernel hace esto fijándonos en que a la hora de establecer en el hijo el primer cerrojo en el archivo nos va a saltar un error.
*/

int main(int argc, char* argv[]){

	struct flock cerrojo1,cerrojo2;
	int fd;
	int childpid;
	
	//Abrimos archivo sobre el que poner cerrojos.
	
	if ( (fd=open("archivo",O_CREAT|O_RDWR)) <0){
		printf("Error abriendo archivo, %d\n",errno);
		perror("Error abriendo archivo.\n");
	
	}
	
	//Cerrojo1
	cerrojo1.l_type=F_WRLCK;
	cerrojo1.l_whence=SEEK_SET;
	cerrojo1.l_start=0;
	cerrojo1.l_len=9;
	
	//Cerrojo2
	cerrojo2.l_type=F_WRLCK;
	cerrojo2.l_whence=SEEK_SET;
	cerrojo2.l_start=10;
	cerrojo2.l_len=0;
	
	
	//Establecemos cerrojo1 desde el padre (no da error).
	if( (fcntl(fd,F_SETLK,&cerrojo1)) <0){
	
		printf("Error estableciendo cerrojo1 (padre), %d\n",errno);
		perror("Error en fcntl().\n");
	}
	
	//Creamos hijo.
	if( (childpid=fork()) <0){
	
		printf("Error en fork(), %d\n",errno);
		perror("Error en fork().\n");
	}
	
	if(childpid==0){ //Proceso hijo
	
	
		//Establecemos cerrojo2 desde el hijo (no da error).	
		if( (fcntl(fd,F_SETLK,&cerrojo2)) <0){
		
			printf("Error estableciendo cerrojo2 (hijo), %d\n",errno);
			perror("Error en fcntl().\n");
		}
		
		sleep(1);
		
		//Establecemos cerrojo1 desde el hijo (si da error).	
		if( (fcntl(fd,F_SETLK,&cerrojo1)) <0){
		
			printf("Error estableciendo cerrojo1 (hijo), %d\n",errno);
			perror("Error en fcntl().\n");
		}
		
	}
	
	else{ //Proceso padre
	
		sleep(2);
		
		//Establecemos cerrojo2 desde el padre (no da error).	
		if( (fcntl(fd,F_SETLK,&cerrojo2)) <0){
		
			printf("Error estableciendo cerrojo2 (padre), %d\n",errno);
			perror("Error en fcntl().\n");
		}
		
		//Recoge informacion de todos los hijos, pero el padre sigue haciendo cosas.
		wait(-1,NULL,WNOHANG);
	
	}
	
	return 0;
	
	
}
