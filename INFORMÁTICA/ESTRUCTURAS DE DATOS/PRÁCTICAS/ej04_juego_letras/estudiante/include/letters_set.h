/*!
 * @file letters_set.h
 * @brief Cabecera para la clase LettersSet
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <map>
#include <string>
#include <iostream>
using namespace std;


/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo {

    /**
     * @brief Número de repeticiones de la letra en la palabra.
     */
    int repetitions;

    /**
     * @brief Puntuación de la letra.
     */
    int score;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

class LettersSet {

private:

    /**
     * @brief Objeto tipo map que asocia cada letra (clave) con su información tipo LettersInfo (alor de clave).
     */
    map<char, LetterInfo> letters;

public:

    /**
     * @brief Contructor sin argumentos. Contruye un objeto LettersSet vacío.
     */
    LettersSet();

    /**
     * @brief Contructor de copia. Contruye un objeto LettersSet a partir de otro.
     * @param other Objeto LettersSet a partir del cual contruir.
     */
    LettersSet(const LettersSet & other);

    /**
     * @brief Inserta un elemento en el Letterset letters que hemos definido.
     * @param val El par a insertar.
     * @return Devuelve un booleano que indica si se ha podido insertar el par.
     */

    bool insert(const pair<char, LetterInfo> & val);

    /**
     * @brief Elimina el elemento con una letra determinada (clave).
     * @param key Clave del elemento a eliminar.
     * @post @letters se modifica.
     */
    bool erase(const char& key);

    /**
     * @brief Limpia el contenido del objeto tipo LettersSet.
     * @post @letters queda vacío.
     */

    void clear();

    /**
     * @brief Determina si el objeto tipo LetterSet está vacío.
     */

    bool empty() const;

    /**
     * @brief Devuelve el tamaño del Letterset.
     * @return Número de elementos en el objeto Letterset
     */

    int size() const;

    /**
     * @brief Calcula la puntuación de una palabra.
     * @return Puntuación total de la palabra.
     */

    int getScore(string word);

    /**
     * @brief Operador de asignación para objetos de tipo LettersSet.
     * @param cl Objeto tipo LettersSet a asignar.
     * @post @map toma el valor de @cl.
     */

    LettersSet& operator= (const LettersSet& cl);

    /**
     * @brief Operador de indexación para objetos de tipo LettersSet.
     * Es decir, dada la clave devuelve el número de repticiones y la puntación de dicha letra.
     * @param val Letra (clave) de la que queremos obtener su valor de clave.
     * @return Devuelve una estructura LetterInfo.
     */

    LetterInfo& operator[] (const char & val);



    /**
     * @brief TDA LS_iterator
     *
     * Iterador que nos permite recorrer un objeto tipo LettersSet.
     */

    class LS_iterator{
    private:

        /**
         * @brief Iterador tipo para mapas.
         */
       map<char,LetterInfo>::iterator it;

    public:

        /**
         * Constructor sin argumentos que contruye interador nulo.
         */
        LS_iterator();

        /**
         * @brief Contructor con argumentos que construye un iterador a partir de otro.
         */

        LS_iterator(const map<char,LetterInfo>::iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores de objetos LettersSet.
         */

        const LS_iterator& operator=(const LS_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores de objetos LettersSet.
         */

        const LS_iterator& operator=(const map<char,LetterInfo>::iterator& other);

        /**
         * @brief Operador de indirección sobrecargado para iteradores de objetos LettersSet.
         */

          pair<char,LetterInfo> operator*() const;

        /**
         * @brief Operador ++ sobrecargado para iteradores de objetos LettersSet.
         */

        LS_iterator& operator++();

        /**
         * @brief Operador -- sobrecargado para iteradores de objetos LettersSet.
         */

        LS_iterator& operator--();

        /**
         * @brief Operador != sobrecargado para iteradores de objetos LettersSet.
         * @param other Iterador de objetos LettersSet.
         * @return Valor booleano 1  si nuestro iterador apunta a distinta misma dirección que @other.
         */

        bool operator!=(const LS_iterator& other) const;

        /**
         * @brief Operador == sobrecargado para iteradores de objetos LettersSet.
         * @param other Iterador de objetos LettersSet.
         * @return Valor booleano 1 si nuestro iterador apunta a la misma dirección que @other.
         */

        bool operator==(const LS_iterator& other) const;

        /**
         * @brief Destructor.
         */

        ~LS_iterator();
    };

    /**
     * @brief Devuelve un iterador a la primera posición del objeto LettersSet.
     */

    const LS_iterator begin();

    /**
     * @brief Devuelve un iterador a la siguiente a la última posición del objeto LettersSet.
     */

    const LS_iterator end();


    /**
     * @brief TDA LS_const_iterator
     *
     * Iterador constante que nos permite recorrer un objeto tipo LettersSet.
     */

    class LS_const_iterator{
    private:

        /**
         * @brief Iterador constante para mapas.
         */
        map<char,LetterInfo>::const_iterator it;

    public:

        /**
         * Constructor sin argumentos que contruye interador constante nulo.
         */
        LS_const_iterator();

        /**
         * @brief Contructor con argumentos que construye un iterador constante a partir de otro.
         */

        LS_const_iterator(const map<char,LetterInfo>::const_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores constantes de objetos LettersSet.
         */

        const LS_const_iterator& operator=(const LS_const_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores constantes de objetos LettersSet.
         */

        const LS_const_iterator& operator=(const map<char,LetterInfo>::const_iterator& other);

        /**
         * @brief Operador de indirección sobrecargado para iteradores de objetos LettersSet.
         */

        const pair<char,LetterInfo> operator*() const;

        /**
         * @brief Operador ++ sobrecargado para iteradores constantes de objetos LettersSet.
         */

        LS_const_iterator& operator++();

        /**
         * @brief Operador -- sobrecargado para iteradores constantes de objetos LettersSet.
         */

        LS_const_iterator& operator--();

        /**
         * @brief Operador != sobrecargado para iteradores constantes de objetos LettersSet.
         * @param other Iterador constante de objetos LettersSet.
         * @return Valor booleano 1  si nuestro iterador apunta a distinta misma dirección que @other.
         */

        bool operator!=(const LS_const_iterator& other) const;

        /**
         * @brief Operador == sobrecargado para iteradores constantes de objetos LettersSet.
         * @param other Iterador constante de objetos LettersSet.
         * @return Valor booleano 1 si nuestro iterador apunta a la misma dirección que @other.
         */

        bool operator==(const LS_const_iterator& other) const;

        /**
         * @brief Destructor.
         */

        ~LS_const_iterator();

    };

    /**
     * @brief Devuelve un iterador constante a la primera posición del objeto LettersSet.
     */

    const LS_const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador constante a la siguiente a la última posición del objeto LettersSet.
     */

    const LS_const_iterator cend() const;

    /**
    * @brief Operador de salida para objetos de tipo LettersSet.
    */

     friend ostream& operator<< (ostream& os, LettersSet& cl);

    /**
     * @brief Operador de entrada para objetos de tipo LettersSet.
     */

     friend istream& operator>> (istream& is, LettersSet& cl);

};

ostream& operator<< (ostream& os, const LettersSet& cl);

istream& operator>> (istream& is, LettersSet& cl);

#endif