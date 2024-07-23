//
// Autores: Leandro Jorge Fernández Vega, Elena Abreu Fernández, Antonio Cantillo Molina
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){

    // Comprobación de parámmetros.

    if(argc!=3) exit(-1);

    // Toma de parámetros.

    string fichero=argv[1];
    int n_clientes=stoi(argv[2]);

    // Rellenamos fichero que generamos.

    ofstream salida;

    salida.open(fichero);

    salida << n_clientes << endl;

    const int MIN=0, MAX=20;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(MIN,MAX);

    for(int i=0;i<n_clientes;++i){
        salida << i << " " << distr(eng) << " " << distr(eng) << endl;
    }

    salida.close();

    return 0;
}