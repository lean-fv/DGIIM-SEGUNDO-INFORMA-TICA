/**
 * 
PI secuencial con integración numérica. 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
/**
 * @file  pi-off.c 
 * @brief PI secuencial con integración numérica, área de rectángulos
 * @author Mancia Anguita
 *  
 * **Compilación**
 * @code
 * srun -pac4 -Aac nvc -O2 -openmp -mp=gpu pi-ompoff.c -o pi-ompoff_GPU
 * srun -pac4 -Aac nvc -O2 -openmp -mp=multicore pi-ompoff.c -o pi-ompoff_CPU
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun –pac4 –Aac pi-ompoff_GPU 1000000    (1000000 intervalos de integración)
 * srun –pac4 –Aac pi-ompoff_CPU 1000000    (1000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/

int main(int argc, char **argv)
{
	 double t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;
	 register double width;
	 double sum;
	 register int intervals, i;

	 //Los procesos calculan PI en paralelo
	 if (argc<2) {printf("Falta número de intevalos");exit(-1);}
	 
	 intervals=atoi(argv[1]);
	 
	 if (intervals<1) {intervals=1E6; printf("Intervalos=%d",intervals);}
	 
	 width = 1.0 / intervals;
	 sum = 0;
	 t1 = omp_get_wtime();
	 
	 #pragma omp target enter data map(to: width, intervals, sum)
	 
	 t2 = omp_get_wtime();

	 #pragma omp target teams distribute parallel for reduction(+:sum)
	 for (i=0; i<intervals; i++) {
	 
		 register double x = (i + 0.5) * width;
		 sum += 4.0 / (1.0 + x * x);
	 }
	 
	 t3 = omp_get_wtime();

	 #pragma omp target exit data map(delete: intervals, width) map(from: sum)
	 
	 sum *= width;

	 t4 = omp_get_wtime();
	 
	 printf("Iteraciones:\t%d\t. PI:\t%f\t. Tiempo:\t%f\n", intervals,sum,t3-t1);
	 printf("Error:\t%f\n", fabs(M_PI-sum));
	 printf("(Target enter data): \t%f\n (Target teams distribute parallel for): \t%f\n (Target exit data): \t%f\n",t2-t1,t3-t2,t4-t3);
 
	return(0);
}
