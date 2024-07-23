#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif


int main (){

	
	int i, n=6, ret=1;
	#pragma omp parallel reduction(+:ret) private(i) 
	//Si no privatizamos la i hay condicion de carrera
	
	for (i=omp_get_thread_num(); i<omp_get_max_threads(); i+=omp_get_num_threads()){
	
		ret+=i;
		printf("Hebra %i ret = %i\n", i,ret);
	}
	
	printf("Suma= %i\n",ret);
	return 0;
}
