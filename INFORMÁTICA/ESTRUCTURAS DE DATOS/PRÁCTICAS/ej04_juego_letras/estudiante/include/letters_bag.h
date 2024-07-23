/*!
 * @file letters_bag.h
 * @brief Cabecera para la clase LettersBag con definiciones.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include <vector>
#include "letters_set.h"
#include "bag.h"

using namespace std;

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es un vector de chars.
 */

class LettersBag{
private:
    /**
     * @brief Objeto tipo Bag de caracteres para almacenar las "fichas" de nuestro Scrabble.
     */
    Bag<char> letters;

public:

    /**
     * @brief Contructor sin argumentos. Contruye un objeto LettersBag vacío.
     */

    LettersBag();

    /**
     * @brief Contructor con argumentos. Construye un objeto tipo Bag a partir de uno tipo LettersSet.
     * @param letterSet Objeto tipo LettersSet a partir del cual contruir el de tipo Bag.
     */

    LettersBag(const LettersSet & letterSet);

    /**
     * @brief Método para introducir una nueva letra en la bolsa.
     * @post letters se modifica.
     */

    void insertLetter(const char & I);

    /**
     * @brief Método que extrae una letra aleatoria de la bolsa y la elimina de ella posteriormente.
     * @return Devuelve una letra aleatoria.
     * @post letters se modifica.
     */

    char extractLetter();

    /**
     * @brief Método que extrae un conjunto de letras de la bolsa, eliminando dicho conjunto posteriormente.
     * @param num Número de letras a extraer.
     * @return Devuelve un vector de letras aleatoria.
     * @post letters se modifica.
     */

    vector<char> extractLetters(int num);

    /**
     * @brief Método que elimina todos los elementos de la bolsa.
     * @post letters se modifica.
     */

    void clear();

    /**
     * @brief Método que devuelve el tamaño de la bolsa.
     * @return Tamaño de la bolsa
     */

    unsigned int size() const;

    /**
     * @brief Sobrecarga del operador de asgnación para objetos tipo Bag<char>.
     * @post letters se modifica.
     */

    LettersBag& operator=(const LettersBag& other);
};
#endif
