#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	
	if (argc>2){
	
		printf("Numero incorrecto de argumentos.\n");
		exit(-1);
	}
	
	int fdin, fdout;
	
	if (argc==2){
	
		if ( (fdin=open(argv[1],O_RDONLY)) <0 ){
		
			printf("Error en la apertura del fichero de entrada, %d\n", errno);
			perror("Error en la apertura del fichero de entrada.\n");
			exit(-1);
		}
	}
	
	else fdin=0;
	
		if ( (fdout=open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR)) <0){
	
		printf("Error en la apertura del fichero de salida, %d\n", errno);
		perror("Error en la apertura del fichero de salida.\n");
		exit(-1);
	}
	
	//Reservamos un espacio inicial.
	char reserva_espacio[100];
	int valor_reserva=100000;
	
	sprintf(reserva_espacio, "El total de bloques es: %d\n",valor_reserva);
	write(fdout, reserva_espacio, strlen(reserva_espacio));
	
	char titulo[100], buf_s[100];
	int i;
	
	for (i=0; read(fdin, buf_s,80)>0; i++){
		
		sprintf(titulo,"\n\n %s %d\n\n", "Bloque:",i);
		write(fdout,titulo,strlen(titulo));
		write(fdout,buf_s,strlen(buf_s));
		
		//No son necesarios ya que con lectura y escritura no se deja el puntero donde se realiza la ultima accion de este tipo.
		//lseek(fdin,0,SEEK_CUR);
		//lseek(fdout,0,SEEK_CUR);
		
	}
	
	char total_bloques[100];
	lseek(fdout,0,SEEK_SET);
	sprintf(total_bloques,"El numero de bloques es %d bloques.\n\n", i);
	write(fdout,total_bloques,strlen(total_bloques)); 
		
	close(fdin); close(fdout);
	
	return 0;
}
