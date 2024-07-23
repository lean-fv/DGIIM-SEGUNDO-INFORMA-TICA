/**
 * @file bolsa_letras.cpp
 * @brief Programa de prueba para clase LettersBag.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "letters_bag.h"
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) {

    // Procesamiento de los argumentos.
    assert(argc==2);
    LettersSet set;

    string route=argv[1];

    // Relleno de un objeto LettersSet.

    ifstream entrada;
    entrada.open(route);

    //cout << "Rellenando el set desde el archivo de ruta [" << route << "]..." << endl;

    entrada >> set;

    entrada.close();

    // Creamos un objeto de la clase LettersBag a partir de un LetterSet.

    LettersBag bag(set);

    // Mostramos las letras de bag aleatoria.

    //cout << endl << "Mostrando contenido de la bolsa..." << endl;

    while (bag.size()!=0) cout << bag.extractLetter() << endl;

    return 0;
}



