/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date October, 2022
 */

#include <stack>
#include <queue>
#include <iostream>
using namespace std;

/**
 * @brief Pareja que consta de un entero y el máximo de la estructura en la que se almacena.
 */

struct element {

    /**
     * @brief Valor entero a almacenar.
     */
    int value; // Current value to store

    /**
     * @brief Máximo de todos los enteros de la estructura.
     */
    int maximum; // Current max value in the structure
};

/**
 * @brief T.D.A. MaxQueue

  Una instancia del tipo de dato abstracto MaxQueue nos permite almacenar enteros.

  El TDA MaxQueue proporciona además distintas herramientas para el cálculo del máximo entero en una estructura basada en una cola con una pila subyacente.

 */

class MaxQueue{

private:

    stack<element> pila;

public:

    /**
    * @brief Contructor sin argumentos: Contruye una MaxQueue vacía.
    */

    MaxQueue();


    /**
    * @brief Contructor de copia: Construye una MaxStack a partir de otra.
    * @param otra Objeto de tipo MaxQueue.
    */

    MaxQueue(const MaxQueue& otra);


    // Métodos y Operaciones.

    /**
    * @brief Añade un elemento al frente de la cola.
    * @param n Elemento a añadir a la cola.
    * @post La cola se modifica.
    */

    void push(const int n);

    /**
    * @brief Elimina el frente de la cola.
    * @post La cola se modifica.
    */

    void pop();

    /**
    * @brief Devuelve el elemento en el frente de la cola.
    * @post Permite su modificación.
    */

    element& front();

    /**
    * @brief Acceso al elemento en el frente de la cola.
    * @post Método de consulta únicamente.
    */

    const element& front() const;

    /**
    * @brief Comprueba si la cola está vacía.
    */

    bool empty();

    /**
    * @brief Obtiene el número de elementos de la cola.
    */

    int size() const;
};

/**
* @brief Imprime un elemento completo de nuestra cola mediante la sobrecarga del operador de salida.
*/

ostream& operator<<(ostream& flujo, const element& element);