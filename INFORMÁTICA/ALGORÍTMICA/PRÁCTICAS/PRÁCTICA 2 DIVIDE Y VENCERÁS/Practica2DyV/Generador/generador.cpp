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

int main(int argc, char *argv[]) {

    if (argc > 3) exit(-1);
    else {
        const int MIN = 0, MAX = 5;
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(MIN, MAX);

        //srand(time(NULL));

        // Tomamos número de vacas y nombre del fichero del caso generado.

        int numero_vacas = stoi(argv[1]);
        string fichero = argv[2];

        // Relleno de fichero.

        ofstream salida;
        salida.open(fichero);

        salida << numero_vacas << endl;
        for (int i = 0; i < numero_vacas; i++) {
            //salida << i << " " << distr(eng) << " " << distr(eng) << endl;
            salida << i << " " << rand()%5 << " " << rand()%5 << endl;
        }

        // Cerramos fichero

        salida.close();
    }

    return 0;
}
