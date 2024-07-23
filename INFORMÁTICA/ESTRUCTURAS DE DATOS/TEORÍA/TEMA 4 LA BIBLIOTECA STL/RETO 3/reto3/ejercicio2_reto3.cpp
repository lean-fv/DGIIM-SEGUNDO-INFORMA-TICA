/**
 * @file ejercicio2_reto3.cpp
 * @brief Programa de prueba de un método de añadido y borrado de elementos a "pilas" que almacenamos en un vector.
 * Verdaderamente, no se trata de un vector de pilas, simplemente hacemos que se comporte como tal.
 * @param n_datos Número de datos totales que repartiremos entre el número de pilas que consideremos.
 * @param n_pilas Número de pilas que manejamos.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include <iostream>

using namespace std;

/**
 * @brief Método que añade un elemento "elem" a la pila de indice "index".
 * @param elem Elemento que añadir a la pila.
 * @param index Índice de la pila a la que queremos añadir el elemento.
 * @param data Vector dinámico de enteros a almacenar.
 * @param topes Vector dinámico que almacena los índices de @data que se corresponden con los topes simbólicos de cada pila.
 * @param bases Vector dinámico que almacena los índices de @data que se corresponden con las bases simbólicas de cada pila.
 * @param n_pilas Número de pilas totales que se desean utilizar.
 * @param n_datos Número de datos totales a almacenar
 */

void push(int elem, int index, int* data, int* topes, int* bases, int n_pilas, int n_datos) {

    if (index<=n_pilas-1 && (topes[index]+1 < bases[index+1])) data[topes[index]++]=elem;
    else if(index+1==n_pilas && (topes[index]+1 < n_datos)) data[topes[index]++]=elem;
    else {
        cout << index;
        cout << "ERROR: Invadiendo espacio no asignado" << endl;
        exit(-1);
    }
}

/**
 * @brief Método que elimina el top de la pila de indice "index".
 * @param index Índice de la pila de la que eliminar el top.
 * @param topes Vector dinámico que almacena el índice de @data que se corresponden con los topes simbólicos de cada pila.
 * @post Borrado lógico, no físico.
 */

void pop(int index, int* topes) {

    topes[index]--;
}


// MAIN

int main(int argc, char * argv[]) {

    /*
    Creamos vectores dinámicos de esta manera y no mediante la utilización de la clase Vector de la STL para poder
    establecer un total de datos en cada vector.
    */

    int *topes=nullptr;
    int *bases=nullptr;
    int *data=nullptr;

    int n_datos= stoi(argv[1]);
    int n_pilas = stoi(argv[2]);

    data=new int[n_datos]; // Suponemos que el tamaño no varía una vez establecido.
    topes=new int[n_pilas];
    bases=new int[n_pilas];

    // Establecemos unas bases para nuestras pilas que almacenaremos en data. Consideramos las pilas vacías, por tanto, no tienen tope aún.

    int factor = n_datos/n_pilas; // Proporcionamos a cada pila un espacio igualitario.
    for(int i=0; i<n_pilas; i++) {
        bases[i]=i*factor;
        topes[i]=i*factor;
    }

    // Añadimos elementos considerando que solo manejamos tres pilas.

    // Añadimos elementos a la pila 1.

    push(4, 0, data, topes, bases, n_pilas, n_datos);
    push(1, 0, data, topes, bases, n_pilas, n_datos);
    push(9,0, data, topes, bases, n_pilas, n_datos);

    // Añadimos elementos a la pila 2.

    push(2, 1, data, topes, bases, n_pilas, n_datos);
    push(5,1, data, topes, bases, n_pilas, n_datos);

    // Añadimos elementos a la pila 3.

    push(3, 2, data, topes, bases, n_pilas, n_datos);
    push(47, 2, data, topes, bases, n_pilas, n_datos);

    cout <<  "PILAS SIN MODIFICAR:" << endl;

    // Mostramos elementos de las pilas antes de editar su contenido.

    for(int i=0; i<n_pilas; i++) {
        cout << "PILA " << i << ":" << endl;
        for (int j = bases[i]; j<topes[i]; j++) {
            cout << data[j] <<" ";
        }
        cout << endl;
    }

    cout << endl;

    // Eliminamos elementos.

    pop(0, topes);
    pop(1, topes);
    pop(2, topes);

    // Mostramos elementos de las pilas tras editar su contenido.

    cout <<  "PILAS MODIFICADAS:" << endl;

    for(int i=0; i<n_pilas; i++) {
        cout << "PILA " << i << ":" << endl;
        for (int j = bases[i]; j<topes[i]; j++) {
            cout << data[j] <<" ";
        }
        cout<<endl;
    }

    // Liberamos memoria;

    delete []topes;
    delete []bases;
    delete []data;

    topes=nullptr;
    bases=nullptr;
    data=nullptr;

    return 0;
}