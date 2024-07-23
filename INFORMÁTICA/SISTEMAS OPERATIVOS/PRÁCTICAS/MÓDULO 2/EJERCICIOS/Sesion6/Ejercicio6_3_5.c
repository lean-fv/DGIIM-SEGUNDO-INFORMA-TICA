
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <sys/mman.h>
#include <dirent.h>

int main (int argc, char* argv[]){


	if (argc!=3){
		printf("Numero invalido de argumentos.\n");
		exit(-1);
	
	}
	
	//fd1 es la fuente, fd2 el destino.
	int fd1,fd2;
	char* file1;
	char* file2;
	
	
	//Abrimos ambos archivos.
	
	if ( (fd1=open(argv[1], O_RDONLY)) <0){
		
		printf("Error en open(), %d\n",errno);
		perror("Error en open().\n");
		exit(-1);
	}
	
	if ( (fd2=open(argv[2], O_CREAT|O_RDWR, S_IRWXU)) <0){
		
		printf("Error en open(), %d\n",errno);
		perror("Error en open().\n");
		exit(-1);
	}
	
	struct stat atributos1;
	
	if ( (lstat(argv[1],&atributos1)) <0){
	
		printf("Error en lstat(), %d\n",errno);
		perror("Error en lstat().\n");
		exit(-1);
	
	}
	
	//Ponemos ajustamos el tamaño del segundo archivo con el del primero.
	int tam=atributos1.st_size;
	
	if ( (ftruncate(fd2,tam)) <0){
	
		printf("Error en ftruncate(), %d\n",errno);
		perror("Error en ftruncate().\n");
		exit(-1);
	
	}
	
	//Region de memoria de fd1;
	file1= (char*) mmap (NULL,tam,PROT_READ,MAP_SHARED,fd1,0);
	if (file1==MAP_FAILED){
	
		printf("Error en mmap(), %d\n",errno);
		perror("Error en mmap().\n");
		exit(-1);
	
	}
	
	
	//Region de memoria de fd1;
	file2= (char*) mmap (NULL,tam,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
	if (file2==MAP_FAILED){
	
		printf("Error en mmap(), %d\n",errno);
		perror("Error en mmap().\n");
		exit(-1);
	
	}
	
	//Cerramos archivos
	close(fd1);
	close(fd2);
	
	//Copiamos una proyeccion en otra.
	
	memcpy(file2,file1,tam);
	
	//Eliminamos proyecciones.
	
	if ( (munmap(file1,tam)) <0){
	
		printf("Error en munmap(), %d\n",errno);
		perror("Error en munmap().\n");
		exit(-1);
	
	}
	
	if ( (munmap(file2,tam)) <0){
	
		printf("Error en munmap(), %d\n",errno);
		perror("Error en munmap().\n");
		exit(-1);
	
	}
	

	return 0;
}
