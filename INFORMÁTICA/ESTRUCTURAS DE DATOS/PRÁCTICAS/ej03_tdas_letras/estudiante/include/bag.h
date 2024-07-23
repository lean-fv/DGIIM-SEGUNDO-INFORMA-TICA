/*!
 * @file bag.h
 * @brief Cabecera para la clase Bag con definiciones incluidas mediante inline.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#ifndef __BAG_H__
#define __BAG_H__

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento.
 */

template <class T>

class Bag {
private:
    /**
     * @brief Objeto tipo vector formado por elementos T(template).
     */
    vector<T> v;

public:

    /**
     * @brief Constructor sin argumentos. Contruye un objeto Bag vacío.
     */

    inline Bag(){};

    /**
     * @brief Constructor de copia.Contruye un objeto Bag a partir de otro.
     * @param other Objeto Bag a partir del cual contruir.
     */

    inline Bag(const Bag<T>& other){v=other.v;}

    /**
     * @brief Añade un elemento a la bolsa.
     * @param element Dato de tipo T que añadir a la bolsa
     */

    inline void add(const T& element){v.push_back(element);}

    /**
     * @brief Extrae un elemento aleatorio de la bolsa, eliminándolo de la bolsa tras su extracción.
     * @returns Devuelve un dato de tipo T.
     * @pre La bolsa no puede estar vacía.
     * @post El elemento extraído se ha eliminado de la bolsa.
     */

    inline T get(){

        srand(time(NULL));
        int i = rand()%v.size();

        T element=v[i];

        v[i]=v.back();
        v.pop_back();

        return element;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa.
     * @post @v se modifica.
     */

    inline void clear() {v.clear();}

    /**
     * @brief Devuelve el número de elementos de la bolsa.
     */

    inline unsigned int size() const {return v.size();}

    /**
     * @brief Indica si la bolsa está vacía.
     * @return Valor booleano 1 si está vacía, 0 en caso contrario.
     */

    inline bool empty() {return v.empty();}

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param other Objeto tipo bolsa a asignar.
     * @post @v se modifica.
     */

    inline const Bag<T>& operator=(const Bag<T>& other) {
        if(this!=&other) v=other.v;

        return *this;
    }
};
#endif
