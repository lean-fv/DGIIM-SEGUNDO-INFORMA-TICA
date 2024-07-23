/**
   @file heapsort.cpp
   @brief Ordenación por montones
   @date 2023-3-6
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <random>
#include <chrono>

using namespace  std;
using namespace chrono;

using std::cerr;
using std::endl;





/* ************************************************************ */ 
/*  Método de ordenación por montones  */

/**
   @brief Ordena un vector por el método de montones.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenación por montones.
*/
inline static 
void heapsort(double T[], int num_elem);



/**
   @brief Reajusta parte de un vector para que sea un montón.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.
   @param k: índice del elemento que se toma com raíz
   
   Reajusta los elementos entre las posiciones k y num_elem - 1 
   de T para que cumpla la propiedad de un montón (APO), 
   considerando al elemento en la posición k como la raíz.
*/
static void reajustar(double T[], int num_elem, int k);




/**
   Implementación de las funciones
**/


static void heapsort(double T[], int num_elem)
{
  int i;
  for (i = num_elem/2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--)
    {
      double aux = T[0];
      T[0] = T[i];
      T[i] = aux;
      reajustar(T, i, 0);
    }
}
  

static void reajustar(double T[], int num_elem, int k)
{
  int j;
  double v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem/2) && !esAPO)
    {
      j = k + k + 1;
      if ((j < (num_elem - 1)) && (T[j] < T[j+1]))
	j++;
      if (v >= T[j]){
	esAPO = true;
      }else{
      T[k] = T[j];
      k = j;
      }
    }
  T[k] = v;
}
  

      
int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  if (n <= 0)
    {
      cerr << "El tamaño del vector debe ser positivo" << endl;
      return -1;
    }

  double * T = new double[n];
  assert(T);

    const int MIN=0, MAX=5000;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(MIN,MAX);

    for (int i = 0; i < n; i++)
    {
        T[i] = distr(eng);
        //cout << T[i] <<endl;
    };

    //Mejor caso: Vector ordenado.
    heapsort(T,n);

    //Peor caso: Vector ordenado a la inversa.
    double* aux= new double[n];
    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = T[i];
    }
    for (int i = 0; i < n; i++) {
        T[i] = aux[i];
    }


    high_resolution_clock::time_point t_antes, t_despues;
    duration<double> transcurrido;

    t_antes = high_resolution_clock::now();

    heapsort(T, n);

    t_despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(t_despues - t_antes);
    cout << n << " \t  "  << transcurrido.count() << endl;

    delete [] T;

  return 0;
};
