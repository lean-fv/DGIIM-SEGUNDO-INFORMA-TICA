/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/
#include <iostream>
#include <vector>
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
 * Funcion que crea una matriz que almacena todas las distancias entre todos los clientes entre si.
 * La posicion [i][j] guarda la distancia entre el cliente i y el j
 * @param clientes Vector de clientes.
 * @return Matriz de todas las distancias.
 */
vector<vector<double>> matriz_dist(vector<cliente> clientes){
    vector<vector<double>> matriz(clientes.size(),vector<double>( clientes.size()));
    for(int i=0; i<clientes.size(); ++i){
        for(int j=0; j<clientes.size(); ++j){
            matriz[i][j] = distancia(clientes[i],clientes[j]);
        }
    }
    return matriz;
}

/*
 * Devuelve el minimo elemento de una fila.
 * @param fila Fila de la que se extrae el minimo.
 * @param id
 */

int min_fila(vector<double> fila, int id){

    int pos_min = 0;
    while((fila[pos_min]==0 || fila[pos_min]==-1) && pos_min <fila.size()) pos_min++;

    double minimo = fila[pos_min];
    for(int i = pos_min;i<fila.size();++i){
        if(fila[i] < minimo && i!=id && fila[i]!=-1){
            minimo = fila[i];
            pos_min = i;
        }
    }
    return pos_min;
}

/*
 * Funcion auxiliar que borra de la matriz las distancias relacionadas con los clientes que ya hayan sido seleccionados.
 * El borrado se realiza poniendo los elementos a borrar a -1.
 * @param matriz Matriz de la que borrar.
 * @param pos Fila y columna que borrar.
*/
void borrar_matriz(vector<vector<double>> &matriz, int pos){
    for(int i=0 ; i<matriz.size();i++) {
        matriz[pos][i]=-1;
        matriz[i][pos]=-1;
    }
}

/*
 * Heuristica del Problema del Viajante de Comercio que calcula la ruta mas optima para visitar a todos los clientes.
 * @param candidatos Vector de clientes a visitar.
 * @return Vector de clientes que representa la ruta mas optima a realizar.
 */

vector<cliente> Alg_PVC1(vector<cliente> candidatos){

    vector<cliente> seleccionados;
    vector<vector<double>> matriz = matriz_dist(candidatos);
    int n = candidatos.size();

    int i=0;

    while(seleccionados.size()<n){ //Hasta que se hayan visitado todos los clientes

        //Se selecciona el cliente mas cercano
        seleccionados.push_back(candidatos[i]);

        int siguiente = min_fila(matriz[i],i);
        borrar_matriz(matriz,i); //Se eliminan los clientes visitados porque no podemos visitar dos veces al mismo
        i=siguiente;
    }
    seleccionados.push_back(candidatos[0]);

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

    // Llamamos a Algoritmo Heuristica 1 sobre el vector de clientes.

    vector<cliente> ruta_final = Alg_PVC1(clientes);

    // Mostramos resultados.

    for (int i=0; i<n_clientes + 1; ++i){
        cout << "CLIENTE " << ruta_final[i].id <<  " --> ";

    }
    cout << "FIN RUTA" << endl;
    */

    //Analisis de eficiencia

    std::chrono::high_resolution_clock::time_point t_antes, t_despues;
    std::chrono::duration<double> transcurrido;

    t_antes = std::chrono::high_resolution_clock::now();

    vector<cliente> ruta_final = Alg_PVC1(clientes);

    t_despues = std::chrono::high_resolution_clock::now();
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);
    cout << n_clientes << " " << transcurrido.count() << endl;

    return 0;
}
