#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


int main (int argc, char* argv[]){

	int n_hijos=5;
	int child_pid;
	int pids[5];
	
	for (int i=0; i<n_hijos; i++){
		
		if ( (child_pid=fork())<0){
			printf("Error en fork, proceso %d, %d\n",i+1,errno);
			perror("Error en fork\n");
		}
		else if (child_pid==0){
			if((i%2)==1) sleep(1);
			printf("Soy el hijo %d(%d)\n", getpid(),i);
			
			//Cada hijo debe salir del bucle.
			break;
		}
		else pids[i]=child_pid;
	
	
	}
	
	int restantes=n_hijos;
	
	//Solo se ejecutan si es el proceso padre.
	for (int i=1; i<n_hijos && child_pid!=0; i+=2){
		waitpid(pids[i],NULL,0);
		restantes--;
		printf("Acaba de finalizar mi hijo %d\nSolo me quedan %d hijos vivos\n",pids[i], restantes);
	}
	
	for (int i=0; i<n_hijos && child_pid!=0; i+=2){
		waitpid(pids[i],NULL,0);
		restantes--;
		printf("Acaba de finalizar mi hijo %d\nSolo me quedan %d hijos vivos\n",pids[i], restantes);
	}
	
	return 0;
}
