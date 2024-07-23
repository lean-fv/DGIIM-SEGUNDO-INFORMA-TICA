/**
 * @file conjunto_letras.cpp
 * @brief Programa de prueba para clase LettersSet.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include "letters_set.h"
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {

    assert(argc==3);
    LettersSet set;

    string route=argv[1];
    string word=argv[2];

    ifstream entrada;
    entrada.open(route);

    //cout << "Rellenando el set desde el archivo de ruta [" << route << "]..." << endl << endl;

    entrada >> set;

    entrada.close();

    //cout << endl << "Mostrando el contenido de [" << route << "]:" << endl << endl;

    //cout << set << endl;

    //cout << "La puntuación de la palabra [" << word << "] es --> " << endl;

    cout << set.getScore(word) << endl;

    return 0;
}