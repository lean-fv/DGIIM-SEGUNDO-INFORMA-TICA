/**
   @file seleccion.cpp
   @brief Ordenación por selección
   @date 2023-3-6
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <random>

using std::cout;
using std::cerr;
using std::endl;



/* ************************************************************ */ 
/*  Método de ordenación por selección  */

/**
   @brief Ordena un vector por el método de selección.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de selección.
*/
inline static 
void seleccion(double T[], int num_elem);



/**
   @brief Ordena parte de un vector por el método de selección.

   @param T: vector de elementos. Tiene un número de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de selección.
*/
static void seleccion_lims(double T[], int inicial, int final);



/**
   Implementación de las funciones
**/

void seleccion(double T[], int num_elem)
{
  seleccion_lims(T, 0, num_elem);
}

static void seleccion_lims(double T[], int inicial, int final)
{
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
	indice_menor = j;
	menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
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

  const int TAM_GRANDE = 2000;
  const int NUM_VECES = 100;

  if (n > TAM_GRANDE)
    {
      clock_t t_antes = clock();
      
      seleccion(T, n);
      
      clock_t t_despues = clock();
  
      cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC 
	   << endl;
    } else {
      double * U = new double[n];
      assert(U);

      for (int i = 0; i < n; i++)
	U[i] = T[i];
      
      clock_t t_antes_vacio = clock();
      for (int veces = 0; veces < NUM_VECES; veces++)
	{
	  for (int i = 0; i < n; i++)
	    U[i] = T[i];
	}
      clock_t t_despues_vacio = clock();

      clock_t t_antes = clock();
      for (int veces = 0; veces < NUM_VECES; veces++)
	{
	  for (int i = 0; i < n; i++)
	    U[i] = T[i];
	  seleccion(U, n);
	}
      clock_t t_despues = clock();
      cout << n << " \t  " 
	   << ((double) ((t_despues - t_antes) - 
			 (t_despues_vacio - t_antes_vacio))) / 
	(CLOCKS_PER_SEC * NUM_VECES)
	   << endl;

      delete [] U;
    }

  delete [] T;

  return 0;
};
