#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif


int main (){

int sum=0;

#pragma omp parallel

{
	
	int p=0;
	#pragma omp for 
	for (int i=0; i<5; i++) {
		//#pragma omp atomic No es necesario porque p es privada.
		p+=i;
		printf("Hebra %d Iteracion %d p= %d \n",omp_get_thread_num(), i,p);
	}
	
	#pragma omp atomic
		sum+=p;
}	
printf("Suma= %i \n", sum);

return 0;
}
