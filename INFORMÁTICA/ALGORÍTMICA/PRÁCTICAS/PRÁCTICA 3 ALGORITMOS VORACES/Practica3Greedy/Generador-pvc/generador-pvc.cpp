/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/
#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {

    // Comprobación de argumentos

    if (argc != 3) exit(-1);

    // Tomamos argumentos

    string fichero = argv[1];
    int n_clientes = stoi(argv[2]);

    ofstream salida;
    salida.open(fichero);

    // Rellenamos el fichero con los datos de los clientes

    salida << n_clientes << endl;

    // Generar clientes con sus identificadores y coordenadas x e y.


    const int MIN=0, MAX=10;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(MIN,MAX);


    for (int i = 0; i < n_clientes; i++) {
        salida << i << " " << distr(eng) << " " << distr(eng) << endl;
    }

    // Cerramos el fichero y lo devolvemos.
    salida.close();

    return 0;
}