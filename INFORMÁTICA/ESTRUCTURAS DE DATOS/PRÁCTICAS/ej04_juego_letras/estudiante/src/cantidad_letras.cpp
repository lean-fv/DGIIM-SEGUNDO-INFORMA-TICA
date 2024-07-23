/**
 * @file cantidad_letras.cpp
 * @brief Main de prueba de las funciones getOccurrences y getUsages.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#include <fstream>
#include <iostream>

#include "letters_set.h"
#include "dictionary.h"

int main(int argc, char **argv){

    string f_dic, f_letters;
    Dictionary dictionary;
    LettersSet set;

    f_dic=argv[1];
    f_letters=argv[2];

    // Relleno del diccionario

    ifstream entrada(f_dic);

    entrada >> dictionary;

    entrada.close();


    // Relleno del conjunto de letras

    entrada.open(f_letters);

    entrada >> set;

    entrada.close();

    // Cálculo de ocurrencias y usos y Muestra de resultados

    cout << "Letra\tUsos\tOcurrencias" << endl;

    for (LettersSet::LS_const_iterator i = set.cbegin(); i!=set.cend(); ++i){
        int occurrences=dictionary.getOccurrences(tolower((*i).first));
        int usages=dictionary.getTotalUsages(tolower((*i).first));

        cout << (*i).first << "\t" << usages << "\t" << occurrences << endl;
    }

    return 0;
}