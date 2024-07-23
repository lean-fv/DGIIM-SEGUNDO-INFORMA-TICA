#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<math.h>
#include<string.h>

int EsPrimo(int n){

	int es_primo=1;
	int k=sqrt(n);
	
	for (int i=2; i<=k && es_primo; i++) if (n%i==0) es_primo=0;
	
	return es_primo;

}

int main(int argc, char* argv[]){
	
	
	int inf=atoi(argv[1]);
	int sup=atoi(argv[2]);
	
	for (int i=inf; i<=sup; i++) 
		if (EsPrimo(i))
			if( (write(STDOUT_FILENO,&i,sizeof(int))) <0){
				printf("Error en write, %d\n",errno);
				perror("Error en write.\n");
			}

	return 0;
}
