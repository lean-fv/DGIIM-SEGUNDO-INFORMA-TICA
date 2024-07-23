#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv) {

	int i, n=20, a[n], suma=0;

	if(argc < 2) {
		fprintf(stderr,"\nFalta iteraciones\n");
		exit(-1);
	}
	
	n = atoi(argv[1]); if (n>20) n=20;
	
	for (i=0; i<n; i++)
		a[i] = i;
	#pragma omp parallel
	{ 
		int sumalocal=0;
		#pragma omp for schedule(static) 
		//shared(i) no es compatible con for, aunque las variables compartidas 
		//que no son dinamicas y estan dentro del for se privatizan.
		for (i=0; i<n; i++) { 
		
			sumalocal += a[i];
			printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",
			omp_get_thread_num(),i,a[i],sumalocal);
		}
		#pragma omp atomic
		suma += sumalocal;
	}
	printf("Fuera de 'parallel' suma=%d\n",suma); 

	return(0);
}
