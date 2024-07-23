/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/
#include <iostream>
#include <vector>
#include <string>
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
};


/*
 * Funcion que calcula la distancia euclidea entre dos clientes.
 * @param cliente1, cliente2 Clientes entre los que calcular distancia.
 */
double distancia(cliente cliente1, cliente cliente2) {

    return sqrt(pow(cliente1.x-cliente2.x,2) + pow(cliente1.y-cliente2.y,2));
}


/*
 * Funcion que calcula la posicion más óptima en la que insertar el siguiente cliente a visitar.
 * @param ruta Vector de clientes que se han seleccionado.
 * @param siguiente Cliente a insertar.
 * @return Posicion mas optima donde meter @cliente.
*/
int pos_optima(vector<cliente> ruta, cliente siguiente){
    double min = INFINITY;
    int pos_optima = 0;
    for (int i = 1; i < ruta.size(); ++i) {

        double distancia_izq = distancia(siguiente, ruta[i-1]);
        double distancia_dcha = distancia(siguiente, ruta[i]);

        //Calculamos la distancia que ahorrariamos si incluimos el siguiente cliente entre i e i-1
        double distancia_ahorro = distancia(ruta[i-1], ruta[i]) - distancia_izq - distancia_dcha;
        double distancia_total = 0;

        for (int j = 0; j < ruta.size() - 1; j++) {
            distancia_total += distancia(ruta[j], ruta[j+1]);
        }
        distancia_total += distancia_ahorro;
        if (distancia_total <min) {
            min = distancia_total;
            pos_optima = i;
        }
    }
    return pos_optima;
}

/*
 * Funcion que devuelve la posicion del siguiente a insertar. Es decir, el mas cercano.
 * @param clientes Vector de clientes a visitar (candidatos).
 * @param actual Posicion del cliente recien insertado.
 */
int pos_min(vector<cliente> clientes, int actual){
    int pos=0;
    double min = distancia(clientes[pos],clientes[actual]);
    for(int i=1; i<clientes.size(); ++i){
        if(distancia(clientes[i],clientes[actual]) < min && i!=actual){
            pos = i;
        }
    }
    return pos;
}

/*
 * Heuristica del Problema del Viajante de Comercio que calcula la ruta mas optima para visitar a todos los clientes.
 * @param candidatos Vector de clientes a visitar.
 * @return Vector de clientes que representa la ruta mas optima a realizar.
 */
vector<cliente> Alg_PVC2(vector<cliente> candidatos) {

    vector<cliente> seleccionados;

    //Comenzamos en una ciudad aleatoria
    srand(time(NULL));
    int pos = rand() % candidatos.size();

    cliente cliente_seleccionado = candidatos[pos];

    int siguiente;
    int pos_insercion;
    seleccionados.push_back(cliente_seleccionado);

    while(candidatos.size()!=1){
        siguiente = pos_min(candidatos,pos);
        cliente_seleccionado=candidatos[siguiente];
        pos_insercion = pos_optima(seleccionados,cliente_seleccionado);
        seleccionados.insert(seleccionados.begin()+pos_insercion,cliente_seleccionado);
        pos=siguiente;
        candidatos.erase(candidatos.begin()+pos);
    }

    //Insertamos camino de vuelta al primero.
    cliente inicial = seleccionados[0];

    seleccionados.push_back(inicial);

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

    // Llamamos a Algoritmo Heuristica 2 sobre el vector de clientes.

    vector<cliente> ruta_final = Alg_PVC2(clientes);

    // Mostramos resultados.

    for (int i=0; i<=n_clientes; ++i) cout << "CLIENTE " << ruta_final[i].id <<  " --> ";
    cout << "FIN RUTA" << endl;

     */

    //Analisis de eficiencia
    std::chrono::high_resolution_clock::time_point t_antes, t_despues;
    std::chrono::duration<double> transcurrido;

    t_antes = std::chrono::high_resolution_clock::now();

    vector<cliente> ruta_final = Alg_PVC2(clientes);

    t_despues = std::chrono::high_resolution_clock::now();
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);
    cout << n_clientes << " " << transcurrido.count() << endl;

    return 0;
}