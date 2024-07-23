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


	//Argumentos.
	char* dir_name=argv[1];
	char* octal=argv[2];
	int permisos=strtol(octal,NULL,8);
	
	
	//Archivos de directorio.
	struct dirent* archivo;
	struct stat atributos;
	
	//Directorio.
	DIR* directorio;
	
	
	if (argc != 3){
	
		printf("Numero de argumentos incorrecto\n");
		exit(-1);
	}

	
	if ((directorio=opendir(dir_name))==NULL){
		printf("Error abriendo directorio, %d\n",errno);
		perror("Error abriendo directorio");
		exit(-1);
	}

	
	while((archivo=readdir(directorio))!=NULL){
	
		char pathname[512]; //Ruta del archivo: <directorio>/<nombre_archivo>
		
		//Escribimos en el mensaje a mostrar el nombre del directorio y del archivo en él.
		strcpy(pathname,dir_name);
		strcat(pathname,"/");
		strcat(pathname,archivo->d_name);
		
		//Accedemos a los atributos del archivo.
		
		if ((lstat(pathname,&atributos))<0){
			printf("Error accediendo a los atributos del archivo, %d\n", errno);
			perror("Error accediendo a los atributos del archivo.");
			exit(-1);
		}
		
		//Comprobamos que es fichero regular.
		if(S_ISREG(atributos.st_mode)){
		
			mode_t permisos_old=atributos.st_mode;
		
			printf("%s:", archivo->d_name);
			
			//Cambiamos permisos: si se cambian se imprimen los antiguos y los nuevos. Si no, el error y los antiguos.
			
			if ((chmod(pathname, permisos))<0) printf("%d %o",errno,permisos_old);
				
			
			else{
				if ((lstat(pathname,&atributos))<0){
					printf("Error accediendo a los atributos del archivo, %d\n", errno);
					perror("Error accediendo a los atributos del archivo.");
					exit(-1);
				}
		
				mode_t permisos_new=atributos.st_mode;
				printf("%o %o\n",permisos_old,permisos_new);
			
			}
		
		}
	
	}
	
	closedir(directorio);


	return 0;
}
