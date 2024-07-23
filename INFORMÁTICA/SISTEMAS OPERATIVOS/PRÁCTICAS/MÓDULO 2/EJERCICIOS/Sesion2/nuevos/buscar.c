/*
Titulo:buscar.c

Fecha:	7/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Programa que busca de forma recursiva en un directorio los ficheros regulares con permiso de ejecución para el grupo y para otros e imprime sus inodos. Después imprime el total de ficheros regulares con estos permisos y el espacio total que ocupan.

Opciones: Si no se introduce argumento, se toma el directorio actual. En caso contrario el introducido como argumento.

Uso: ./buscar [<directorio>]
*/


#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

void Buscar(DIR* dir, char pathname[], int* num_registros, int* tam){

	
	if ((dir=opendir(pathname))==NULL){
		printf("Error abriendo directorio %s\n:", pathname);
	}
	
	struct dirent* file;
	
	while ((file=readdir(dir))!=NULL){
	
		char pathname2[1000];
		
		if(strcmp(file->d_name,".") !=0 && strcmp(file->d_name,"..") !=0){
		
			//Vamos añadiendo la ruta, que se ira ampliando por la recursividad.
			strcpy(pathname2,pathname);
			strcat(pathname2,"/");
			strcat(pathname2,file->d_name);
			
			struct stat atributos;
			
			if ((lstat(pathname2,&atributos))<0){
				printf("No se han podido obtener los atributos del archivo %s, %d", pathname2,errno);
				perror("No se han podido obtener los atributos del archivo.");
				exit(-1);
			}
			
			//Si el archivo es directorio, se llama a la funcion.
			DIR* new_dir;
			if (S_ISDIR(atributos.st_mode)) Buscar(new_dir,pathname2,num_registros,tam);
			
			else if (S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
			
				printf("%s %ld\n", pathname2,atributos.st_ino);
				(*num_registros)++;
				(*tam)+=(int)atributos.st_size;
			
			}
		}
	}
	closedir(dir);
}


int main (int argc, char* argv[]){

	//Argumentos.
	
	char* nombre_dir;
	
	if (argc==1) nombre_dir=".";
	else if (argc==2) nombre_dir=argv[1];
	else{
		printf("Numero de argumentos incorrecto\n");
		exit(-1);
	}
	
	
	DIR* dir;
	int num_registros=0, tam=0;
	

	//Imprimir inodos.
	printf("Los inodos son:\n\n");
	Buscar(dir,nombre_dir, &num_registros, &tam);
	
	//Imprimir resto.
	printf("\nExisten %d archivos regulares con permiso x para grupo y otros.\n",num_registros);
	printf("El tamaño total ocupado por dichos archivos es %d bytes.\n",tam);
	

	return 0;
}
