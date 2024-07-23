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

// MAIN
int main(int argc, char *argv[]) {

    if (argc > 2) exit(-1);
    else {

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

        pair<int,int>resultado_esp = AlgoritmoEspecifico(vacas,0,n_vacas);
        cout << endl << "VACAS MÁS AFINES: " << vacas[resultado_esp.first].name << " " << vacas[resultado_esp.second].name <<endl;

        delete []vacas;
    }

    return 0;
}
