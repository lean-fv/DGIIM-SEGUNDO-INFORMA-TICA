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
		
			int dyn_var= omp_get_dynamic();
			int nthreads_var= omp_get_max_threads();
			int thread_limit_var= omp_get_thread_limit();
			int modifier;
			omp_sched_t kind;
			omp_get_schedule(&kind,&modifier);

			printf("Dinamica (true 0, false 1): %d\n", dyn_var);
			printf("Nº threads: %d\n", nthreads_var);
			printf("Limite de threads: %d\n", thread_limit_var);
			printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
			printf("Chunk: %d\n", modifier);
		
		}
		suma = suma + a[i];
		//printf(" thread %d suma a[%d] suma=%d \n",omp_get_thread_num(),i,suma);
	} 

	printf("\nFuera de 'parallel for' suma=%d\n",suma);
	int dyn_var= omp_get_dynamic();
	int nthreads_var= omp_get_max_threads();
	int thread_limit_var= omp_get_thread_limit();
	int modifier;
	omp_sched_t kind;
	omp_get_schedule(&kind,&modifier);

	printf("Dinamica (true 0, false 1): %d\n", dyn_var);
	printf("Nº threads: %d\n", nthreads_var);
	printf("Limite de threads: %d\n", thread_limit_var);
	printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
	printf("Chunk: %d\n", modifier);
	
	return 0;

}

