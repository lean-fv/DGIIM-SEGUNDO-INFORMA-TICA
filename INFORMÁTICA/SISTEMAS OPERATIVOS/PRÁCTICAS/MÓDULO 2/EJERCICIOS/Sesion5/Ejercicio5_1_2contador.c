
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

//Partimos de que hay 31 señales distintas.
const int TOTAL_SIGNALS=31;
static int contador[31]={0};

static void handler(int signum){

	contador[signum-1]++;
	printf("La señal %d se ha recibido %d veces\n",signum,contador[signum-1]);
}

int main(int argc, char* argv[]){

	//Lista de señales.
	int signals[TOTAL_SIGNALS];
	
	
	//Fijamos accion asociando el manejador, poniendo la mascara de señales bloqueadas a vacia y haciendo que ciertas llamadas se reinicien si son interrumpidas por un manejador.
	struct sigaction action;
	action.sa_handler=handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags=SA_RESTART;
	
	
	for (int i=0; i<TOTAL_SIGNALS; i++){
	
		//Ajustamos posicion para que la señal 1 este en la posicion 0,... etc.
		 signals[i]=i+1;
		 
		//SIGKILL y SIGSTOP no se manejan.
		if (signals[i]!=9 && signals[i]!=19){
		
			if ( (sigaction(signals[i], &action,NULL) <0) ){
				
				printf("Error en sigaction, %d\n",errno);
				perror("Error en sigaction\n");
				exit(-1);
			}
		}
		
		else printf("No se ha podido procesar la señal %d\n", signals[i]);
		
	}
	
	//Bucle para que no acabe el programa hasta que enviemos kill -9.
	for(;;){}


	return 0;
}
