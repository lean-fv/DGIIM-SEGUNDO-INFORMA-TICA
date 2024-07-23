/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date October, 2022
 */

#include <stack>
#include <maxqueue.h>
using namespace std;

// **************************************************************************************************************//
//                                                FUNCIONES PÚBLICAS                                             //
// **************************************************************************************************************//

MaxQueue::MaxQueue(){}

MaxQueue::MaxQueue(const MaxQueue& otra){pila=otra.pila;}

void MaxQueue::push(const int n){

    stack <element> aux;
    int dim = pila.size();

    element elem;
    elem.value=n;
    elem.maximum=n;

    for (int i=0; i<dim; i++){
        aux.push(pila.top());
        pila.pop();
    }

    aux.push(elem);

    for (int i=0; i<dim+1; i++){
        if (elem.value >= aux.top().maximum) aux.top().maximum=elem.value;
        pila.push(aux.top());
        aux.pop();
    }
}

void MaxQueue::pop(){pila.pop();}

element& MaxQueue::front(){return pila.top();}

const element& MaxQueue::front() const{return front();}

bool MaxQueue::empty(){return pila.empty();}

int MaxQueue::size() const{return pila.size();}


// **************************************************************************************************************//
//                                                OTRAS FUNCIONES                                                //
// **************************************************************************************************************//

ostream& operator<<(ostream& flujo, const element& elemento) {

    flujo << elemento.value << "," << elemento.maximum;

    return flujo;
}