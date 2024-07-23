/**
 * @file ejercicio1_reto3.cpp
 * @brief  Programa de prueba de un método de borrado para listas de pilas, que eliminará aquellos topes con el elemento
 * especificado en todos los topes y dejará ordenadas las pilas según el valor de los mismos.
 * @param fichero Fichero para rellenar la lista de pilas.
 * ****Esta opción está deshabilitada debido a no haber podido encontrar un fallo en timepo de ejecución. En su lugar se rellena la lista de pilas manualmente.****
 * @param elemento Elemento a eliminar de los topes de las pilas que guardamos dentro de la lista.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace std;

// CRITERIO DE ORDENACIÓN

/**
 * @brief Criterio de ordenación entre pilas basado en el tope de cada una.
 * @param pila1, pila2 Pilas a comparar.
 * @return Valor booleano true si el tope de la primera pila es menor o igual que el de la segunda. False en caso contrario.
 */

bool criterion (stack<int> p1, stack<int> p2){return p1.top() <= p2.top();}

/**
 * @brief Función que elimina los topes de cada pila indicados.
 * @param L Lista de pilas de la que borrar los topes.
 * @param elemento Entero presente en el tope a eliminar.
 * @post L se modifica y las pilas se ordenan de menor a mayor según el tope tras el borrado.
 * @post Si a una pila le queda un solo elemento y debe borrarse, se elimina la propia pila.
 */

void Borrar(list<stack<int>>& L, int elem) {

    for (list<stack<int>>::iterator it=L.begin(); it!=L.end(); ++it) {

        if ((*it).top() == elem) {

            if ((*it).size() > 1) (*it).pop();
            else {
                it = L.erase(it);
                --it;
            }
        }
    }
    L.sort(criterion);
}

// SOBRECARGA DE OPERADOR DE ENTRADA

/**
 * @brief Sobrecarga del operador de entrada para listas de pilas.
 * @param flujo Flujo sobre el que hacer la entrada.
 * @param L Lista a rellenar.
 */

istream& operator>>(istream& flujo, list<stack<int>>& L){

    stack<int> pila;
    string numero;

    while(flujo) {
        flujo >> numero;
        if(numero!="x") pila.push(stoi(numero));
        else {
            L.push_back(pila);
            while(!pila.empty()) pila.pop();
        }
    }

    return flujo;
}


// SOBRECARGA DE OPERADORES DE SALIDA

/**
 * @brief Sobrecarga del operador de salida para pilas.
 * @param flujo Flujo sobre el que hacer la salida.
 * @param P Pila a mostrar.
 */

ostream& operator<<(ostream& flujo, const stack<int>& P){

    stack<int> aux(P);

    while (!aux.empty()){
        flujo << aux.top() << " ";
        aux.pop();
    }
    return flujo;
}

/**
 * @brief Sobrecarga del operador de salida para Listas de Pilas.
 * @param flujo Flujo sobre el que hacer la salida.
 * @param L Lista de Pilas a mostrar.
 */

ostream& operator<<(ostream& flujo, const list<stack<int>>& L) {

    for (list<stack<int>>::const_iterator it = L.cbegin(); it != L.cend(); ++it) flujo << (*it) << endl;

    return flujo;
}

// MAIN

int main(int argc, char * argv[]) {

    /*
    IMPORTANTE
    Hemos implementado una sobrecarga del operador de entrada >> para que leyera de un archivo "pilas.txt" que
    adjuntamos en la entrega. Sin embargo, nos da cierto error que no conseguimos comprender y para el cuál hemos
    empleado mucho tiempo en intentar buscar el error sin éxito. Finalmente, hemos optado por rellenar manualmente
    las pilas y lista de pilas. A pesar de ello, dejamos comentado todo el desarrollo que habíamos realizado en el
    main para probar el programa.
   */

    // Creación de lista de pilas

    list<stack<int>> L;

    /*
    Se considera que se introducen dos argumento, 1: Dirección donde se encuentra el fichero del que leer,
    2: Número que eliminar
    */

    //string fichero=argv[1];
    int elemento=stoi(argv[2]);

/*
    // Rellenamos la lista de pilas

    ifstream entrada;

    entrada.open(fichero);
    entrada >> L;
    entrada.close();
*/

    stack <int> p1, p2, p3, p4, p5, p6;
    p1.push(1);
    p1.push(9);
    p1.push(2);

    p2.push(0);
    p2.push(1);
    p2.push(2);

    p3.push(2);

    p4.push(7);
    p4.push(10);
    p4.push(9);
    p4.push(3);

    p5.push(2);
    p5.push(4);

    p6.push(2);
    p6.push(8);

    // Añadir las pilas a la lista.

    L.push_back(p1);
    L.push_back(p2);
    L.push_back(p3);
    L.push_back(p4);
    L.push_back(p5);
    L.push_back(p6);

    // Mostramos la lista de pilas antes de realizar ningún cambio.

    cout << "LISTA ACTUAL:" << endl << endl;
    cout << L << endl;

    // Borramos todos los top de las pilas de la lista que sean iguales a "elemento".

    Borrar(L,elemento);

    // Mostramos la lista de pilas tras la eliminación realizada en las pilas y consecuente ordenación según sus tops.

    cout << "LISTA MODIFICADA:" << endl << endl;
    cout << L << endl;

    return 0;
}