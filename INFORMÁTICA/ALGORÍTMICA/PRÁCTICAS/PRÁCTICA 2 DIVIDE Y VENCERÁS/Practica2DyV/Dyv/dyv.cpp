//
// Autores: Leandro Jorge Fernández Vega, Antonio Cantillo Molina y Elena Abreu Fernández
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <time.h>
#include <chrono>


using namespace std;


//Estructura que representa una vaca.

struct vaca{

    //Identificador
    int name;
    //Coordenada x
    double x;
    //Coordenada y
    double y;
};

//------------------------------------------------------------------------------------------------------------------

//Funcion que calcula la distancia euclidea entre dos puntos.

double distancia(vaca vaca_1, vaca vaca_2) {

    return sqrt(pow(vaca_1.x-vaca_2.x,2) + pow(vaca_1.y-vaca_2.y,2));
}

//------------------------------------------------------------------------------------------------------------------

static void insercion_lims(vaca T[], int inicial, int final)
{
    int i, j;
    vaca aux;
    for (i = inicial + 1; i < final; i++) {
        j = i;
        while ((T[j].x < T[j-1].x) && (j > 0)) {
            aux = T[j];
            T[j] = T[j-1];
            T[j-1] = aux;
            j--;
        };
    };
}

//------------------------------------------------------------------------------------------------------------------

inline static void insercion(vaca T[], int num_elem)
{
    insercion_lims(T, 0, num_elem);
}

//------------------------------------------------------------------------------------------------------------------

const int UMBRAL_QS = 50;

static void dividir_qs(vaca T[], int inicial, int final, int & pp)
{
    vaca pivote, aux;
    int k, l;

    pivote = T[inicial];
    k = inicial;
    l = final;
    do {
        k++;
    } while ((T[k].x <= pivote.x) && (k < final-1));
    do {
        l--;
    } while (T[l].x > pivote.x);
    while (k < l) {
        aux = T[k];
        T[k] = T[l];
        T[l] = aux;
        do k++; while (T[k].x <= pivote.x);
        do l--; while (T[l].x > pivote.x);
    };
    aux = T[inicial];
    T[inicial] = T[l];
    T[l] = aux;
    pp = l;
};

//------------------------------------------------------------------------------------------------------------------

static void quicksort_lims(vaca T[], int inicial, int final)
{
    int k;
    if (final - inicial < UMBRAL_QS) {
        insercion_lims(T, inicial, final);
    } else {
        dividir_qs(T, inicial, final, k);
        quicksort_lims(T, inicial, k);
        quicksort_lims(T, k + 1, final);
    };
}


//------------------------------------------------------------------------------------------------------------------

inline void quicksort(vaca T[], int num_elem)
{
    quicksort_lims(T, 0, num_elem);
}



//------------------------------------------------------------------------------------------------------------------

//Funcion que devuelve los identificadores de las vacas mas proximas entre si.

pair<int,int> AlgoritmoEspecifico(vaca vacas[],int inicio, int final){

    double min= distancia(vacas[inicio],vacas[inicio+1]);
    pair<int,int> salida(inicio, inicio+1);

    for(int i=inicio; i<final; i++){
        for(int j=i+1;j<final; j++){
            double posible_min=distancia(vacas[i],vacas[j]);
            if (posible_min < min){
                min= posible_min;
                salida.first=i;
                salida.second=j;
            }
        }
    }

    return salida;
}

//------------------------------------------------------------------------------------------------------------------

const int UMBRAL_VACAS=16;

// DYV IMPLEMENTACIÓN

pair<int,int> DyV_lims(vaca vacas[], int inicio, int final) {

    pair<int,int> output1, output2, output;

    if (final-inicio <= UMBRAL_VACAS) output=AlgoritmoEspecifico(vacas, inicio, final);

    else {
        int medio=(inicio+final)/2;
        output1=DyV_lims(vacas, inicio, medio);
        output2=DyV_lims(vacas,medio, final);

        if (distancia(vacas[output1.first],vacas[output1.second]) < distancia(vacas[output2.first],vacas[output2.second]))
            output=output1;
        else output=output2;

        double dist_min = distancia(vacas[output.first],vacas[output.second]);


        for (int i=inicio; i<medio; i++){
            //Pertenecer al rectangulo.
            if(abs(vacas[i].x - vacas[medio].x) < dist_min) {

                for (int j=medio; j<final; j++){
                    if(abs(vacas[j].x - vacas[medio].x) < dist_min){

                        double dist= distancia(vacas[i],vacas[j]);
                        //Comparamos cada punto de una mitad del rectangulo con cada uno de la otra.
                        if(dist < dist_min){
                            dist_min=dist;
                            output.first=i;
                            output.second=j;
                        }
                    }
                }
            }
        }
    }

    return output;
}

//------------------------------------------------------------------------------------------------------------------

// ALGORITMO DYV

pair<int,int> DyV(vaca vacas[], int n){

    quicksort(vacas,n); // Para ordenar por la coordenada x.

    return DyV_lims(vacas,0,n);
}

//-------------------------------------------------------------------------------------------------------------------

// MAIN

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Formato " << argv[0] << " <nombre_fichero>" << endl;
        return -1;
    }

    if (argc <= 0) {
        cerr << "Debes introducir un fichero del que tomar los datos." << endl;
        return -1;
    }


    // Tomamos fichero (Se considera que se introduce la ruta completa).

    string fichero=argv[1];

    // Abrimos el fichero y rellenamos con la información.

    ifstream entrada;
    entrada.open(fichero);

    int n_vacas;
    int id_vaca;

    entrada >> n_vacas;

    vaca *vacas= new vaca[n_vacas];

    while(!entrada.eof()) {
        entrada >> id_vaca;
        vacas[id_vaca].name=id_vaca;
        entrada >> vacas[id_vaca].x >> vacas[id_vaca].y;
    }

    entrada.close();

    // Mostramos el vector de vacas y los nombres de las vacas más afines.

    for(int i=0; i<n_vacas;i++) cout << "VACA " << i << ": " << vacas[i].x << " " << vacas[i].y << endl;

    pair<int,int>resultado_dyv = DyV(vacas,n_vacas);
    cout << endl << "VACAS MÁS AFINES: " << vacas[resultado_dyv.first].name << " " << vacas[resultado_dyv.second].name <<endl;

    /*

    // MEDIDA DE TIEMPOS

    chrono::high_resolution_clock::time_point t_antes, t_despues;
    chrono::duration<double> transcurrido;

    t_antes = chrono::high_resolution_clock::now();
    //sentencia o programa a medir
    //AlgoritmoEspecifico(vacas,0,n);
    DyV(vacas,n);
    t_despues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(t_despues - t_antes);
    cout << n << " " << transcurrido.count() << endl;

    */

    delete[] vacas;

    return 0;
}
