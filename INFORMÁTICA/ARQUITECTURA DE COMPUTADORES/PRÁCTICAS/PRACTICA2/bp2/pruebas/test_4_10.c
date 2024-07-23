#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif


int main (){

int suma, a[5], sumalocal;

for (int i=0; i<5; i++) a[i]=i;

#pragma omp parallel private(sumalocal)
{
	sumalocal =0;
	#pragma omp for
		for(int i=0; i<5; i++) sumalocal += a[i];
	#pragma omp barrier
	
	#pragma omp atomic //Tambien vale critical, pues toma una unica sentencia
		suma = suma + sumalocal;
	#pragma omp barrier
	
	#pragma omp single
	printf("La suma es =%d\n", suma);
}

	return 0;
}
