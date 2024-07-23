/**
 * @file solver.h
 * @brief  Fichero de cabecera para la clase Solver.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include <vector>
#include <string>

using namespace std;

    /**
    * @brief TDA Solver
    *
    * Clase que permite encontrar las mejores soluciones y resolver un juego parecido al Scrabble.
    */

class Solver{
private:

    /**
     * @brief Conjunto de letras a considerar junto con sus puntuaciones para poder jugar.
     */
    LettersSet letters_set;

    /**
     * @brief Diccionario en el que poder buscar las palabras.
     */
    Dictionary dict;

public:

    /**
     * @brief Contructor con parámetros.
     * @param dict Diccionario que utilizar para encontrar las palabras.
     * @param letters_set Conjunto de letras a considerar para encontrar la mejor solución.
     */
    Solver(const Dictionary& dict, const LettersSet& letters_set);


    /**
     * @brief Método que ofrece las mejores soluciones según las letras disponibles y el modo de juego.
     * @param available_letters Letras disponibles.
     * @param score_game Modo de juego. True es partida a puntuación, false a longitud.
     * @return Devuelve el vector con las mejores soluciones y la puntuación.
     */
    pair<vector<string>,int> getSolutions(const vector <char>&available_letters, bool score_game);


    /**
     * @brief Método que determina si es posible formar una palabra dado un conjunto de letras.
     * @param word Palabra a formar.
     * @param letters Conjunto de letras a emplear.
     * @return True si se puede formar la palabra, false en caso contrario.
     */
    bool possibleWord(string word, vector<char> letters);

};

#endif //P04_JUEGO_LETRAS_SOLVER_H