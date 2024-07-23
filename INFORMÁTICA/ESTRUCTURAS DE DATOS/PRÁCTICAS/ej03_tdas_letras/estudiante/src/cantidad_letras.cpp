/**
 * @file cantidad_letras.cpp
 * @brief Programa de prueba para clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include "dictionary.h"
#include "letters_set.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    // Procesamiento de argumentos.

    string route_words=argv[1];
    string route_letters=argv[2];

    // Creación y relleno del diccionario.

    Dictionary dic;

    ifstream entrada;

    entrada.open(route_words);

    //cout << "Rellenando el diccionario desde el archivo de ruta [" << route_words << "]..." << endl;

    entrada >> dic;

    entrada.close();

    //  Creación y relleno del LetterSet.

    LettersSet set;

    entrada.open(route_letters);

    entrada >> set;

    entrada.close();

    // Salida de resultados: Mostramos las letras con sus ocurrencias en las palabras del diccionario
    // y su frecuencia relativa.

    // cout << "FORMATO: <letra> <N_ocurrencias> <Total Letras> <Frec_relativa>" << endl;
    cout << "Letra\tFAbs.\tFrel." << endl;

    int total_letters = dic.getTotalLetters();
    int contador=0;

    for(LettersSet::LS_const_iterator i=set.cbegin(); i!=set.cend(); ++i) {
        int occurrences = dic.getOccurrences(tolower((*i).first));
        cout << (*i).first << "\t" << occurrences << "\t" << 1.0*occurrences/total_letters << endl;
    }

    return 0;
}
