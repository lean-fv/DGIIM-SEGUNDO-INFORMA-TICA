#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int main(int argc, char* argv[]){

	char* pathname;
	unsigned int permisos_old,permisos_new;
	DIR* directorio;


	if (argc==3){
		
		pathname=argv[1];
		directorio= opendir(pathname);
		permisos_new=strtol(argv[2],NULL,8);
	}
	
	else{
	printf("Uso: Ejercicio2.c <pathname> <permisos>\n");
	exit(-1);
	}
	
	
	struct dirent* a_leer;
	struct stat atributos;
	char cad1[300],cad2[300];
	
	while((a_leer=readdir(directorio))!=NULL){
		
		sprintf(cad1,"%s%s",pathname,a_leer->d_name);
		
		/*if(lstat(cad2,&atributos)<0){
		
			printf("Error al acceder a los atributos del archivo.\n");
			perror("Error en lstat.\n");
			exit(-1);
		}
		*/
		
		lstat(cad1,&atributos);
		permisos_old=atributos.st_mode;
		if (chmod(pathname,permisos_new)<0)
			printf("%s: %d %o \n", a_leer->d_name, errno, permisos_old);
			
		else printf ("%s: %o %o \n", a_leer->d_name, permisos_old, permisos_new);
		
	} //while
	
	closedir(directorio);

	return 0;
	
}
