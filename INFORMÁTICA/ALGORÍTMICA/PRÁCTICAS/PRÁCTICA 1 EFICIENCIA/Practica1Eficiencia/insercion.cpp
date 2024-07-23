/**
   @file insercion.cpp
   @brief Ordenación por inserción
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

using std::cout;
using std::cin;
using std::cerr;
using std::endl;



/* ************************************************************ */ 
/*  Método de ordenación por inserción  */

/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static 
void insercion(double T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserción.
*/
static void insercion_lims(double T[], int inicial, int final);



/**
   Implementación de las funciones
**/

inline static void insercion(double T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(double T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


inline static
void heapsort(double T[], int num_elem);
static void reajustar(double T[], int num_elem, int k);


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

    insercion(T, n);

    t_despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(t_despues - t_antes);
    cout << n << " \t  "  << transcurrido.count() << endl;

    delete [] T;

  return 0;
};
