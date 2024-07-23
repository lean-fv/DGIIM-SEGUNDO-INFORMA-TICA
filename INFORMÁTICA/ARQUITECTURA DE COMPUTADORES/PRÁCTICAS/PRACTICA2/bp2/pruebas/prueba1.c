#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif


int main (){

int n=1;

#pragma omp parallel for firstprivate(n) lastprivate(n)
	for (int i=0; i<5; i++) {
		n+=1;
		printf("Hebra %d  n= %d \n",omp_get_thread_num(), n);
	}
	
printf("n= %d \n", n);

return 0;
}
