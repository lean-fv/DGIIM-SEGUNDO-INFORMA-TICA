/**
 * @file partida_letras.cpp
 * @brief Main de prueba de los métodos de la clase Solver.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#include <fstream>
#include <iostream>
#include "solver.h"
#include "letters_set.h"
#include "letters_bag.h"
#include "dictionary.h"
#include <string>
#include <vector>

using namespace std;

int main (int argc, char *argv[]){

    string f_dic, f_letters, mode;
    int num;

    Dictionary dic;
    LettersSet set;

    f_dic=argv[1];
    f_letters=argv[2];
    mode=argv[3];
    num=stoi(argv[4]);

    // Relleno de Diccionario

    ifstream entrada;

    entrada.open(f_dic);

    entrada >> dic;

    entrada.close();


    // Relleno de Letters Set

    entrada.open(f_letters);

    entrada >> set;

    entrada.close();


    // Creación de Bolsa de Letras para la extracción aletoria

    LettersBag Bag(set);
    vector<char> v = Bag.extractLetters(num);

    // Creación de Solver

    Solver solver(dic, set);

    // Modos de juego

    pair <vector<string>,int> p;
    if (mode == "L") p=solver.getSolutions(v, false);
    else p=solver.getSolutions(v, true);


    // Muestra de resultados
    cout << endl << "LETRAS DISPONIBLES:" << endl;
    for(int i=0; i<v.size(); ++i) cout << v[i] << " ";

    cout << endl << "SOLUCIONES:" << endl;
    int length = p.first.size();
    for (int i=0; i<length; ++i) cout << p.first[i] << endl;

    cout << "PUNTUACION:" << endl << p.second <<endl;

    return 0;
}