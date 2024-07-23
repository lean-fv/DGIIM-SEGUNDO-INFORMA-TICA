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
		
			int modifier;
			omp_sched_t kind;
		
			omp_get_schedule(&kind,&modifier);
			
			printf("REGION PARALELA ANTES DE MODIFICAR\n\n");
			
			printf("Dinamica (true 0, false 1): %d\n", omp_get_dynamic());
			printf("Nº threads: %d\n", omp_get_max_threads());
			printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
			printf("Chunk: %d\n", modifier);
			
			omp_set_dynamic(5);
			omp_set_num_threads(6);
			omp_set_schedule(3,2);
			omp_get_schedule(&kind,&modifier);
			
			printf("\nREGION PARALELA DESPUES DE MODIFICAR\n\n");
			
			printf("Dinamica (true 0, false 1): %d\n", omp_get_dynamic());
			printf("Nº threads: %d\n", omp_get_max_threads());
			printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
			printf("Chunk: %d\n", modifier);
		}
		suma = suma + a[i];
		//printf(" thread %d suma a[%d] suma=%d \n",omp_get_thread_num(),i,suma);
	} 
	
	
	int modifier;
	omp_sched_t kind;

	printf("\nFuera de 'parallel for' suma=%d\n",suma);
	
	omp_get_schedule(&kind,&modifier);
	
	printf("\nREGION SECUENCIAL ANTES DE MODIFICAR\n\n");
			
	printf("Dinamica (true 0, false 1): %d\n", omp_get_dynamic());
	printf("Nº threads: %d\n", omp_get_max_threads());
	printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
	printf("Chunk: %d\n", modifier);
	
	omp_set_dynamic(4);
	omp_set_num_threads(4);
	omp_set_schedule(2,1);
	omp_get_schedule(&kind,&modifier);
	
	printf("\nREGION SECUENCIAL DESPUES DE MODIFICAR\n\n");
	
	printf("Dinamica (true 0, false 1): %d\n", omp_get_dynamic());
	printf("Nº threads: %d\n", omp_get_max_threads());
	printf("Kind (static 1, dynamic 2, guided 3): %d\n", kind);
	printf("Chunk: %d\n", modifier);
	
	return 0;

}

