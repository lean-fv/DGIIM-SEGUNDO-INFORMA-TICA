/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

/*
 * struct que encapsula el concepto de cliente de un vendedor cualquiera.
 * @field x Coordenada x del cliente.
 * @field y Coordenada y del cliente.
 * @field id Identificador del cliente.
 */
struct cliente{
    double x;
    double y;
    int id;

    /*
     * Sobrecarga del operador <
     */

    bool operator < (cliente cliente) const{
        return id<cliente.id;
    }

    /*
     * Sobrecarga del operador ==
     */

    bool operator == (cliente cliente) const{
        return (id==cliente.id);
    }

    /*
     * Sobrecarga del operador !=
     */

    bool operator != (cliente cliente) const{
        return (id!=cliente.id);
    }
};

/*
 * Funcion que calcula la distancia euclidea entre dos clientes.
 * @param cliente1, cliente2 Clientes entre los que calcular distancia.
 */
double distancia(cliente cliente1, cliente cliente2) {

    return sqrt(pow(cliente1.x-cliente2.x,2) + pow(cliente1.y-cliente2.y,2));
}

/*
 * struct que encapsula el concepto de arista que une dos clientes.
 * @field cliente1, cliente2 Clientes unidos por la arista.
 * @field dist Distancia entre los clientes o modulo de la arista.
 */

struct arista{
    cliente cliente1;
    cliente cliente2;
    double dist ;

    /*
     * Sobrecarga del operador <
     */

    bool operator < (arista arista) const{
        return dist > arista.dist;
    }
};


/*
 * Funcion que genera un conjunto de componentes conexas con un elemento cada una.
 * @param cl Vector de clientes a partir del cual contruir el conjunto de conjuntos.
 */

set<set<cliente>> genera_Set (const vector<cliente>& cl){

    set<set<cliente>> set_clientes;

    for(int i=0; i<cl.size();i++) {
        set<cliente> c;
        c.insert(cl[i]);
        set_clientes.insert(c);
    }

    return set_clientes;
}

/*
 * Funcion que contruye un vector de aristas dado uno de candidatos.
 * @param cl Vector de clientes.
 */
vector<arista> conjunto_aristas(vector<cliente> cl) {
    vector<arista> aristas;

    for (int i = 0; i < cl.size(); i++) {
        for (int j = i + 1; j < cl.size(); j++) {
            if (i != j) {
                arista a;
                a.cliente1 = cl[i], a.cliente2 = cl[j];
                a.dist = distancia(cl[i], cl[j]);
                aristas.push_back(a);
            }
        }
    }

    return aristas;
}

/*
 * Funcion que devuelve la componente conexa donde esta un dterminado cliente.
 * @param conjunto Conjunto de conjuntos entre los que buscar la componente conexa.
 * @param cl Cliente que buscar entre los elementos de @conjunto.
 */

set<cliente> encuentra_Componente(set<set<cliente>> conjunto, cliente cl){
    set<cliente> componente;

    for (set<set<cliente>>::iterator i=conjunto.begin(); i!=conjunto.end(); ++i){
        set<cliente>::iterator posible=(*i).find(cl);
        if (posible!=(*i).end()) componente = *i;
    }
    return componente;

}

/*
 * Funcion quedetermina si dos conjuntos son iguales.
 * @param c1,c2 Sets a comparar.
 */

bool conjuntos_Iguales(set<cliente> c1, set<cliente> c2){

    bool iguales=false;
    if (c1.size()== c2.size()){
        iguales=true;
        for(set<cliente>::iterator i=c1.begin(); i!=c1.end() && iguales;++i) {
            set<cliente>::iterator j=c2.find(*i);
            if (j==c2.end()) iguales=false;
        }

    }

    return iguales;
}

/*
 * Funcion que comprueba si un cliente tiene dos aristas asociadas.
 * @param clientes Vector que almacena el numero de aristas que tiene asociadas cada cliente.
 * @arista Arista de la que obtener cada cliente.
 * @return true si ambos clientes que une una arista tienen 2 aristas.
 */

bool DosVisitas(vector<int> clientes, arista arista){

    bool visitado=false;

    if(clientes.at(arista.cliente1.id)==2 || clientes.at(arista.cliente2.id)==2) visitado = true;

    return visitado;

}

/*
 * Funcion que une dos sets.
 * @param c1,c2 Conjuntos a unir.
 */

set<cliente> Unir (const set<cliente>& c1, const set<cliente>& c2){

    set<cliente> unir(c1);
    for (set<cliente>::iterator i=c2.begin(); i!=c2.end(); ++i) unir.insert(*i);
    return unir;
}




/*
 * Heuristica del Problema del Viajante de Comercio que calcula la ruta mas optima para visitar a todos los clientes.
 * @param candidatos Vector de clientes a visitar.
 * @return Vector de clientes que representa la ruta mas optima a realizar.
 */
vector<arista> Alg_PVC3(vector<cliente> candidatos) {
    vector<arista> seleccionados;
    set<set<cliente>> conjunto = genera_Set(candidatos);
    vector<arista> grafo = conjunto_aristas(candidatos);

    sort(grafo.begin(),grafo.end()); // Ordenamos aristas

    //Vector que almacena cuantas aristas unen dos clientes.

    vector<int> repeticiones;
    for (int i=0; i<candidatos.size(); i++) repeticiones.push_back(0);

    //Ahora mismo tenemos todas las aristas ordenadas de menor a mayor

    arista next = grafo.back();
    grafo.pop_back();
   // seleccionados.push_back(next);

    while (!grafo.empty() && (seleccionados.size() < candidatos.size()-1)) {

        set<cliente> compu, compv;
        compu = encuentra_Componente(conjunto,next.cliente1);
        compv = encuentra_Componente(conjunto,next.cliente2);

        if(!conjuntos_Iguales(compu,compv) && !DosVisitas(repeticiones,next)){

            set<cliente> unir;
            unir = Unir(compu,compv);

            //Insertamos union
            conjunto.insert(unir);

            //Actualizamos repeticiones
            repeticiones.at(next.cliente1.id)++;
            repeticiones.at(next.cliente2.id)++;

            //Borramos
            conjunto.erase(compu);
            conjunto.erase(compv);

            // Añadimos a seleccionados el vertice
            seleccionados.push_back(next);
        }

        next=grafo.back();
        grafo.pop_back();
    }

    //Insertamos el camino al primer elemento.
    cliente inicio,final;
    int cont=0;
    arista ult;
    for (int i=0; i<repeticiones.size(); i++){

        if (repeticiones[i]==1){
            if(cont==0){
                inicio = candidatos[i];
                cont++;
            }
            else {
                final = candidatos[i];
            }
        }
    }
    ult.cliente1=inicio;
    ult.cliente2=final;
    seleccionados.push_back(ult);

    return seleccionados;
}


int main(int argc, char *argv[]){

    // Comprobación de argumentos.

    if(argc!=2) exit(-1);

    // Tomamos argumentos.

    string fichero=argv[1];

    // Leemos del fichero.

    ifstream entrada;

    entrada.open(fichero);

    int n_clientes, identif;
    double coord_x, coord_y;
    cliente c;

    entrada >> n_clientes;

    vector<cliente> clientes;

    // Rellenamos un vector con todos los clientes.

    //cout << "DATOS INICIALES: " << endl;

    while(!entrada.eof() && (identif!=n_clientes-1)) {
        entrada >> identif >> coord_x >> coord_y;
        c.id=identif;
        c.x=coord_x;
        c.y=coord_y;

        //cout << "CLIENTE " << identif << ": " << coord_x << " " << coord_y << endl;
        clientes.push_back(c);
    }

    /*
    cout << endl;

    // Llamamos a Algoritmo Heuristica 3 sobre el vector de clientes.

    vector<arista> ruta_final = Alg_PVC3(clientes);

    // Mostramos resultados.

    for (int i=0; i<n_clientes ; ++i) cout << "ARISTA QUE UNE:  " << ruta_final[i].cliente1.id  << " CON " << ruta_final[i].cliente2.id << " --> ";
    cout << "FIN RUTA" << endl;
     */

    std::chrono::high_resolution_clock::time_point t_antes, t_despues;
    std::chrono::duration<double> transcurrido;

    t_antes = std::chrono::high_resolution_clock::now();

    vector<arista> ruta_final = Alg_PVC3(clientes);

    t_despues = std::chrono::high_resolution_clock::now();
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);
    cout << n_clientes << " " << transcurrido.count() << endl;

    return 0;
}