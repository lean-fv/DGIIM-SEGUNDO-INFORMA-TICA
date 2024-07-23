/*!
 * @file dictionary.h
 * @brief Cabecera para la clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */


#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;


/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */

class Dictionary {
private:

    /**
     * @brief Objeto tipo set que almacenará las palabras admitidas en el juego a modo de diccionario.
     */

    set <string> words;

public:

    /**
     * @brief Constructor sin argumentos. Construye un diccionario vacío.
     */

    Dictionary();

    /**
     * @brief Constructor de copia. Construye un diccionario a partir de otro.
     * @param other Objeto tipo Dictionary a partir del cual construir.
     */

    Dictionary(const Dictionary& other);

    /**
     * @brief Método que comprueba si una palabra existe en el diccionario.
     * @param val Palabra a comprobar si está en el diccionario.
     * @return Devuelve true si la palabra existe en el diccionario, false en caso contrario.
     */

    bool exists(const string& val) const;

    /**
     * @brief Método que inserta una nueva palabra al diccionario.
     * @param val Palabra a insertar.
     * @return Valor booleano true si se ha insertado, false en caso contrario.
     * @post words se modifica.
     */

    bool insert(const string& val);

    /**
     * @brief Método que elimina una palabra del diccionario.
     * @param val Palabra a eliminar.
     * @return Devuelve true si la palabra ha sido borrada con exito del diccionario, false en caso contrario.
     * @post words se modifica.
     */

    bool erase(const string& val);

    /**
     * @brief Método que elimina todas las palabras del diccionario.
     * @post words se modifica.
     */

    void clear();

    /**
     * @brief Indica si el diccinoario está vacío.
     * @return Valor booleano true si está vacío, false en caso contrario.
     */

    bool empty() const;

    /**
     * @brief Método que devuelve el tamaño del diccionario.
     * @return Tamaño del diccionario.
     */

    unsigned int size() const;

    /**
     * @brief Método que indica el número de apariciones de una letra.
     * @param c Letra de la contar su número de apariciones.
     * @return Número de apariciones de @c.
     */

    int getOccurrences(const char c);

    /**
     * @brief Método que cuenta el número total de letras de un diccionario.
     * @return Número de letras totales.
     */

    int getTotalLetters();

    /**
     * @brief Método que devuelve todas las palabras de una longitud determinada contenidas en el diccionario.
     * @param length Longitud de las palabras
     * @return Vector que contiene todas las palabras de longitud @length del diccionario.
     */

    vector<string> WordsOflength(int length);

    /**
     * @brief Sobrecarga del operador de salida para objetos tipo Dictionary.
     * @param os Flujo sobre el que hacer la salida.
     * @param dic Objeto tipo Dictionary que mostrar.
     */

    friend ostream& operator<<(ostream& os, const Dictionary& dic);

    /**
      * @brief Sobrecarga del operador de entrada para objetos tipo Dictionary.
      * @param is Flujo sobre el que hacer la entrada.
      * @param dic Objeto tipo Dictionary que rellenar.
      */

    friend istream& operator>>(istream& is, Dictionary& dic);


    /**
     * @brief TDA Dic_iterator
     *
     * Iterador que nos permite recorrer un objeto tipo Diccionario.
     */

    class Dic_iterator{
    private:

        /**
         * @brief Iterador tipo para sets.
         */
        set<string>::iterator it;

    public:

        /**
         * Constructor sin argumentos que contruye interador nulo.
         */
        Dic_iterator();

        /**
         * @brief Contructor con argumentos que construye un iterador a partir de otro.
         */

        Dic_iterator(const set<string>::iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores de objetos Diccionario.
         */

        const Dic_iterator& operator=(const Dic_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores de objetos Diccionario.
         */

        const Dic_iterator& operator=(const set<string>::iterator& other);

        /**
         * @brief Operador de indirección sobrecargado para iteradores de objetos Diccionario.
         */

        string operator*() const;

        /**
         * @brief Operador ++ sobrecargado para iteradores de objetos Diccionario.
         */

        Dic_iterator& operator++();

        /**
         * @brief Operador -- sobrecargado para iteradores de objetos Diccionario.
         */

        Dic_iterator& operator--();

        /**
         * @brief Operador != sobrecargado para iteradores de objetos Diccionario.
         * @param other Iterador de objetos Diccionario.
         * @return Valor booleano 1  si nuestro iterador apunta a distinta misma dirección que @other.
         */

        bool operator!=(const Dic_iterator& other) const;

        /**
         * @brief Operador == sobrecargado para iteradores de objetos Diccionario.
         * @param other Iterador de objetos Diccionario.
         * @return Valor booleano 1 si nuestro iterador apunta a la misma dirección que @other.
         */

        bool operator==(const Dic_iterator& other) const;

        /**
         * @brief Destructor.
         */

        ~Dic_iterator();
    };

    /**
     * @brief Devuelve un iterador a la primera posición del objeto Diccionario.
     */

    const Dic_iterator begin();

    /**
     * @brief Devuelve un iterador a la siguiente a la última posición del objeto Diccionario.
     */

    const Dic_iterator end();


    /**
     * @brief TDA Dic_const_iterator
     *
     * Iterador constante que nos permite recorrer un objeto tipo Diccionario.
     */

    class Dic_const_iterator{
    private:

        /**
         * @brief Iterador constante para sets.
         */
        set<string>::const_iterator it;

    public:

        /**
         * Constructor sin argumentos que contruye interador constante nulo.
         */
        Dic_const_iterator();

        /**
         * @brief Contructor con argumentos que construye un iterador constante a partir de otro.
         */

        Dic_const_iterator(const set<string>::const_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores constantes de objetos Diccionario.
         */

        const Dic_const_iterator& operator=(const Dic_const_iterator& other);

        /**
         * @brief Operador de asignación sobrecargado para iteradores constantes de objetos Diccionario.
         */

        const Dic_const_iterator& operator=(const set<string>::const_iterator& other);

        /**
         * @brief Operador de indirección sobrecargado para iteradores de objetos Diccionario.
         */

        const string operator*() const;

        /**
         * @brief Operador ++ sobrecargado para iteradores constantes de objetos Diccionario.
         */

        Dic_const_iterator& operator++();

        /**
         * @brief Operador -- sobrecargado para iteradores constantes de objetos Diccionario.
         */

        Dic_const_iterator& operator--();

        /**
         * @brief Operador != sobrecargado para iteradores constantes de objetos Diccionario.
         * @param other Iterador constante de objetos Diccionario.
         * @return Valor booleano 1  si nuestro iterador apunta a distinta misma dirección que @other.
         */

        bool operator!=(const Dic_const_iterator& other) const;

        /**
         * @brief Operador == sobrecargado para iteradores constantes de objetos Diccionario.
         * @param other Iterador constante de objetos Diccionario.
         * @return Valor booleano 1 si nuestro iterador apunta a la misma dirección que @other.
         */

        bool operator==(const Dic_const_iterator& other) const;

        /**
         * @brief Destructor.
         */

        ~Dic_const_iterator();

    };

    /**
     * @brief Devuelve un iterador constante a la primera posición del objeto Diccionario.
     */

    const Dic_const_iterator cbegin() const;

    /**
     * @brief Devuelve un iterador constante a la siguiente a la última posición del objeto Diccionario.
     */

    const Dic_const_iterator cend() const;
};

ostream& operator<<(ostream& os, const Dictionary& dic);
istream& operator>>(istream& is, Dictionary& dic);

#endif
