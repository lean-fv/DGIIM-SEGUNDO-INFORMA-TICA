#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif


int main (){

int n=0;
//El resultado depende del numero de hebras, pues el resultado final sera la 
//multiplicacion de los resultados de cada hebra, es decir, de las sumas que realiza 
//cada hebra.
#pragma omp parallel for reduction (*:n)
	for (int i=0; i<5; i++) {
		n+=1;
		printf("Hebra %d  n= %d \n",omp_get_thread_num(), n);
	}
	
printf("n= %d \n", n);

return 0;
}
