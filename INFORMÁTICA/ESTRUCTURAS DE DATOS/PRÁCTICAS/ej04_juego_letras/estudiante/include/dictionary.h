/**
 * @file dictionary.h
 * @brief  Fichero de cabecera para la clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

    /**
    * @brief TDA Dictionary
    *
    * Class that will enable to arrange a virtual dictionary thanks to an underlying tree.
    */

class Dictionary {
private:

    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */

    struct char_info {

        /**
         * @brief Letter of the alphabet.
         */

        char character;

        /**
         * @brief Bool variable that indicates if a word finishes.
         */

        bool valid_word;


        /**
         * Default constructor
         */

        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */

        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        /**
         * @brief Operator== overcharge.
         *
         * @param rhs char_info struct to compare.
         */

        inline bool operator==(const char_info &rhs) {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        /**
         * @brief Operator!= overcharge.
         *
         * @param rhs char_info struct to compare.
         */

        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        /**
         * @brief Operator* overcharge.
         *
         * @return The character field of the struct.
         */
        inline bool operator*() { return this->character; }

        /**
         * @brief Operator<< overcharge.
         *
         * @param os Output flow.
         * @param other char_info struct to show.
         */
        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    /**
     * @brief Tree that will host the dictionary.
     */

    tree<char_info> words;

    /**
     * @brief Total number of words in the dictionary.
     */

    int total_words;

    /**
     * @brief A node of the tree, which contains a char_info element.
     */

    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Método que devuelve el número de ocurrencias de una letra en un subárbol.
     * @param curr_node Nodo del que se comienza a contar, es decir, la raíz del subárbol.
     * @param c Letra de la que hay que contar su número de apariciones.
     * @return Número de veces que aparece la letra.
     */

    int getOccurrences(node curr_node, char c);

    /**
     * @brief Método de devuelve cuántas veces se utiliza una letra en en un subárbol.
     * @param curr_node Nodo desde el que empezar a contar, es decir, la raíz del subárbol.
     * @param c Letra de la que hay que determinar su número de usos.
     * @return Número de veces la letra.
     */

    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío.
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */

    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada.
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */

    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */

    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Método que devuelve el número de ocurrencias de una letra en todas las palabras del diccionario, es decir, el número de nodos con esa letra.
     * @param c Letra de la cual contar su número de apariciones.
     * @return Número de veces que aparece la letra en nuestro árbol diccionario.
     */

    int getOccurrences(const char c);

    /**
     * @brief Método que devuelve el número de veces que se utiliza una letra.
     * @param c Letra de la cual contar su número de veces utilizada.
     * @return Número de veces que se utiliza la letra en todas las palabras.
     */

    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    /**
    * @brief TDA iterator
    *
    * Iterador que nos permite recorrer las palabras del diccionario que se forman en el árbol por orden alfabético.
    */

    class iterator {
    private:

        /**
        * @brief String que representa la palabra actual que estamos visitando si encuentra que uno de los nodos está marcado como final de palabra.
        */

        std::string curr_word;

        /**
        * @brief Iterador constante en preorden para árboles binarios LCRS a partir del cual se contruye el de tipo diccionario.
        */

        tree<char_info>::const_preorder_iterator iter;

    public:

        /**
        * @brief Contructor sin parámetros que crea un iterador nulo.
        */

        iterator();

        /**
        * @brief Constructor de copia.
        */

        iterator(tree<char_info>::const_preorder_iterator iter);

        /**
        * @brief Constructor de copia.
        */

        iterator(const iterator& iter);

        /**
        * @brief Sobrecarga del operador de indirección para objetos tipo diccionario.
        * @return La palabra almacenada como resultado del recorrido del iterador.
        */

        std::string operator*();

        /**
        * @brief Sobrecarga del operador de incremento para objetos de tipo diccionario.
        * @return Devuelve el siguiente nodo en el que termina una palabra válida.
        */

        iterator &operator++();

        /**
        * @brief Sobrecarga del operador == para objetos de tipo diccionario.
        * @return Devuelve balor booleano true si son iguales.
        */

        bool operator==(const iterator &other);

        /**
        * @brief Sobrecarga del operador != para objetos de tipo diccionario.
        * @return Devuelve balor booleano true si son distintos.
        */

        bool operator!=(const iterator &other);

    };

    /**
    * @brief Devuelve un iterador a la primera posición del objeto Diccionario.
    */

    iterator begin() const;

    /**
    * @brief Devuelve un iterador a la última posición del objeto Diccionario
    */

    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    /**
    * @brief TDA possible_words_iterator
    * Iterador que nos permite recorrer las palabras del diccionario que se forman en el árbol por orden alfabético y de manera más eficiente que TDA iterator.
     *
    */

    class possible_words_iterator {
    public:

        /**
        * @brief Contructor sin parámetros para possible_words_iterator.
        */

        possible_words_iterator();

        /**
        * @brief Contructor con parámetros para possible_words_iterator.
        * @param current_node Nodo al que apunta el iterador.
        * @param available_letters Vector que contiene las letras válidas para determinar cómo recorrer el árbol de manera eficiente.
        */

        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
        * @brief Constructor de copia para possible_words_iterator.
        * @param other Iterador possible_words_iterator del que copiar los datos.
        */

        possible_words_iterator(const possible_words_iterator &other);

        /**
        * @brief Sobrecarga del operador de asignación.
        * @param other Iterador possible_words_iterator del que copiar los datos.
        */

        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
        * @brief Sobrecarga del operador de igualdad
        * @param other Iterador possible_words_iterator con el que comparar.
        */

        bool operator==(const possible_words_iterator &other) const;

        /**
        * @brief Sobrecarga del operador de desigualdad.
        * @param other Iterador possible_words_iterator con el que comparar.
        */

        bool operator!=(const possible_words_iterator &other) const;


        /**
        * @brief Sobrecarga del operador de incremento para iterar de forma eficiente el diccionario, de palabra válida
        * en palabra válida, teniendo en cuenta las letras en available_letters.
        */

        possible_words_iterator &operator++(); // Hacer función aux. que recibe un nodo como argumento y devuelve un valor booleano.
                                               // Va de nodo válido en nodo válido de modo que si no hay nodos válido por debajo de x letra,
                                               // sabremos que no puede haber palabras con x letra y pasamos a su hermano. Por ejemplo:
                                               // a--->m-->e    Iría el iterador desde la a hasta la e o la o pq la m no es válida.
                                               //      '-->o    Si la o no se encuentra en las letras válidas, entonces todo lo que cuelgue de
                                               //               el no podrá ser palabra válida y pasamos al siguiente. En caso de que ni la e
                                               //               ni la o no se encuentren en las letras válidas, ninguna palabra empezará por am
                                               //               y por tanto, se pasa al hermano de la m.


        /**
        * @brief Sobrecarga del operador de indirección.
        * @return Palabra válida.
        */

        std::string operator*() const;

    private:

        /**
        * @brief Conjunto con repeticiones que almacenará las letras válidas que determinan cómo se recorrerá el árbol diccionario.
        */

        multiset<char> available_letters;

        /**
        * @brief Nivel del nodo actual al que apunta el iterador possible_words_iterator.
        */

        int level;

        /**
        * @brief Nodo actual al que apunta el iterador possible_words_iterator.
        */

        node current_node;

        /**
        * @brief Palabra válida formada hasta el momento.
        */

        string current_word;


        /**
         * @brief Comprueba si un nodo es válido, es decir, si es no nulo y si el carácter que tiene como etiqueta se encuentra en available_letters.
         * @param curr_node
         * @return true si el nodo es válido, false si no lo es.
         */

        bool validNode(node curr_node);

        /**
         * @brief Avanza de nodo en el árbol Diccionario según la casuítica que se tenga.
         * @post current_node,current_word, available_letters y level se modifican.
         */

        void nextNode();
    };

    /**
    * @brief Devuelve un iterador possible_words_iterator a la primera posición del Diccionario
    */

    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
    * @brief Devuelve un iterador possible_words_iterator a la última posición del Diccionario.
    */

    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP
