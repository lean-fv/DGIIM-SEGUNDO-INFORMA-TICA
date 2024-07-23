#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
	int i, n=16, chunk, a[n], suma=0;

	if(argc < 2)
	{
	fprintf(stderr,"\nFalta el tamaño de chunk\n");
	exit(-1);
	}

	chunk = atoi(argv[1]); 

	for (i=0; i<n; i++)
	a[i] = i;

	#pragma omp parallel for num_threads(3) firstprivate(suma) \
		lastprivate(suma) schedule(runtime)
	for (i=0; i<n; i++)
	{

		if(i==0){
			printf("Nº procesadores disponibles: %d\n", omp_get_num_procs());
			printf("Nº threads: %d\n", omp_get_num_threads());
			printf("En region paralela (true 1, false 0): %d\n", omp_in_parallel());
		}
		suma = suma + a[i];
		//printf(" thread %d suma a[%d] suma=%d \n",omp_get_thread_num(),i,suma);
	} 

	printf("\nFuera de 'parallel for' suma=%d\n",suma);
	printf("Nº procesadores disponibles: %d\n", omp_get_num_procs());
	printf("Nº threads: %d\n", omp_get_num_threads());
	printf("En region paralela (true 1, false 0): %d\n", omp_in_parallel());
	
	return 0;

}

