/**
 * @file palabras_longitud.cpp
 * @brief Programa de prueba para clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include "dictionary.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    // Procesamiento de argumentos.

    string route=argv[1];
    int length= stoi(argv[2]);

    // Creación y relleno del diccionario.

    Dictionary dic;

    ifstream entrada;

    entrada.open(route);

    //cout << "Rellenando el diccionario desde el archivo de ruta [" << route << "]..." << endl;

    entrada >> dic;

    entrada.close();

    //  Creación del vector donde almacenar las palabras de longitud "length".

    vector<string> aux = dic.WordsOflength(length);

    int words_of_length= aux.size();

    cout << "Palabras de longitud " << length << endl;

    for (int i=0; i< words_of_length; i++) cout << aux[i] << endl;

    return 0;
}