
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[]){


	int fd;
	
	if ( (fd=open("archivo",O_CREAT|O_RDWR|O_TRUNC,S_IRWXU)) <0 ){
	
		printf("Error abriendo archivo, %d\n", errno);
		perror("Error abriendo archivo.\n");
		exit(-1);
	}
	
	struct flock cerrojo;
	
	cerrojo.l_type=F_WRLCK;
	cerrojo.l_whence=SEEK_SET;
	cerrojo.l_start=0;
	cerrojo.l_len=0;
	
	if ( (fcntl(fd,F_SETLK,&cerrojo)) <0 ){
	
		printf("Error en fcntl(), %d\n", errno);
		perror("Error en fcntl().\n");
		exit(-1);
	}

	
	//Bucle infinito para que no acabe el programa y hagamos las comprobaciones. Una vez puesto el cerrojo, cuando el bucle de la segunda vuelta y se ejecute el programa de nuevo dara error pues ya se ha puesto un cerrojo en una posicion y no se ha desbloqueado.
	for(;;){}
	
	return 0;
}
