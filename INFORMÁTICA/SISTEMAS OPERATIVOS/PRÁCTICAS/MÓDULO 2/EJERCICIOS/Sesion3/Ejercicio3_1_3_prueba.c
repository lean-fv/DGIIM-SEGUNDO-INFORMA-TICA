#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


//Jerarquía de procesos tipo 1

int main (int argc, char* argv[]){

	int childpid;
	int i;
	int nprocs=5;
	
	
	for (i=1; i < nprocs; i++) {
		if ((childpid= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
	
		if (childpid){
		
			break;
		}
	


	}
		
	
	/*
	//Jerarquía de procesos tipo 2

	for (i=1; i < nprocs; i++) {
		if ((childpid= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}

	if (!childpid){
		
		break;
	}
	
	*/

	return 0;

}
