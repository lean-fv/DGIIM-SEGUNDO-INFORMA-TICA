#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main(){


	sigset_t new_mask;
	
	//Inicializar la mascara con todas las señales.
	sigfillset(&new_mask);
	
	//Eliminamos la que no queremos que bloquee el proceso.
	sigdelset(&new_mask, SIGUSR1);
	
	//Hacemos que le proceso bloquee todas las señales de la mascara (todas salvo SIGUSR1).
	sigsuspend (&new_mask);


	return 0;
}
