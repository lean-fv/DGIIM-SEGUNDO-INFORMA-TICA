/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */

/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date October, 2022
 */

#include <queue>
#include <maxstack.h>
using namespace std;

// **************************************************************************************************************//
//                                                FUNCIONES PÚBLICAS                                             //
// **************************************************************************************************************//

MaxStack::MaxStack(){}

MaxStack::MaxStack (const MaxStack& otra){cola=otra.cola;}

MaxStack::MaxStack (const queue<element>& otra){cola=otra;}

void MaxStack::push(const int n){

    queue <element> aux;

    int dim = cola.size();
    element elem;

    elem.value=n;
    elem.maximum=n;

    if(size() != 0) if (top().maximum >= elem.maximum) elem.maximum = top().maximum;

    aux.push(elem);

    if (cola.size() >= 1) {
        for (int i = 0; i < dim; i++) {
            aux.push(top());
            cola.pop();
        }
    }
    
    cola=aux;
}

void MaxStack::pop(){cola.pop();}

element& MaxStack::top(){return cola.front();}

const element& MaxStack::top() const{return top();}

bool MaxStack::empty(){return cola.empty();}

int MaxStack::size() const {return cola.size();}


// **************************************************************************************************************//
//                                                OTRAS FUNCIONES                                                //
// **************************************************************************************************************//

ostream& operator<<(ostream& flujo, const element& elemento) {

    flujo << elemento.value << "," << elemento.maximum;

    return flujo;
}