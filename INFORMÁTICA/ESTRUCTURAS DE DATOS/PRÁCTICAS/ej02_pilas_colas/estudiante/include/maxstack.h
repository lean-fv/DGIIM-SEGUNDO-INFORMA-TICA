/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date October, 2022
 */

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
 * @brief T.D.A. MaxStack

  Una instancia del tipo de dato abstracto MaxStack nos permite almacenar enteros.

  El TDA Maxstack proporciona además distintas herramientas para el cálculo del máximo entero en una estructura basada en una pila con una cola subyacente.

 */
class MaxStack{

private:

    /**
     * @brief Cola sobre la que guardaremos parejas de enteros.
     */

    queue <element> cola;


public:

    //Constructores y destructor.

    /**
    * @brief Contructor sin argumentos: Contruye una MaxStack vacía.
    */

    MaxStack();

    /**
    * @brief Contructor de copia: Construye una MaxStack a partir de otra.
    * @param otra Objeto de tipo MaxStack.
    */

    MaxStack (const MaxStack& otra);

    /**
    * @brief Construye una MaxStack a partir de una cola.
    * @param otra Objeto de tipo queue.
    */

    MaxStack (const queue<element>& otra);

    // Métodos y Operaciones.

    /**
    * @brief Añade un elemento al tope de la pila.
    * @param n Elemento a añadir a la pila.
    * @post La pila se modifica.
    */

    void push(const int n);

    /**
    * @brief Elimina el tope de la pila.
    * @post La pila se modifica.
    */

    void pop();

    /**
    * @brief Devuelve el elemento en el tope de la pila.
    * @post Permite su modificación.
    */

    element& top();

    /**
    * @brief Acceso al elemento en el tope de la pila.
    * @post Método de consulta únicamente.
    */

    const element& top() const;

    /**
    * @brief Comprueba si la pila está vacía.
    */

    bool empty();

    /**
    * @brief Obtiene el número de elementos de la pila.
    */

    int size() const;
};

/**
* @brief Imprime un elemento completo de nuestra pila mediante la sobrecarga del operador de salida.
*/

ostream& operator<<(ostream& flujo, const element& element);