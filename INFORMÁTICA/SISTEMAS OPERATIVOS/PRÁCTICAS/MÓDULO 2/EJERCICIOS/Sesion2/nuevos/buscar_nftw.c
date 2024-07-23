/*
Titulo:buscar.c

Fecha:	7/12/2022

Autor:	Leandro Jorge Fernández Vega

Versión: 1.0

Descripción: Programa que busca de forma recursiva en un directorio los ficheros regulares con permiso de ejecución para el grupo y para otros e imprime sus inodos. Después imprime el total de ficheros regulares con estos permisos y el espacio total que ocupan.

Opciones: Si no se introduce argumento, se toma el directorio actual. En caso contrario el introducido como argumento.

Uso: ./buscar [<directorio>]
*/


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <dirent.h>
#include <ftw.h>


//Variables globales.
static int num_registros=0, tam=0;


int Buscar(const char pathname[], const struct stat *statbuf, int typeflag, struct FTW *ftwbuf){
	
	if (S_ISREG(statbuf->st_mode) && (statbuf->st_mode & S_IXGRP) && (statbuf->st_mode & S_IXOTH)){
	
		printf("%s %ld\n", pathname,statbuf->st_ino);
		num_registros++;
		tam+=(int)statbuf->st_size;
	
	}
	
	return 0;
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
	
	

	//Imprimir inodos.
	printf("Los inodos son:\n\n");
	
	if ((nftw(nombre_dir,Buscar,10,0))<0){
		
		printf("Error en NFTW, %d",errno);
		perror("Error en NFTW.");
	}
	
	//Imprimir resto.
	printf("\nExisten %d archivos regulares con permiso x para grupo y otros.\n",num_registros);
	printf("El tamaño total ocupado por dichos archivos es %d bytes.\n",tam);
	

	return 0;
}
