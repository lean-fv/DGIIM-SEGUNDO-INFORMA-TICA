//
// Autores: Leandro Jorge Fernández Vega, Elena Abreu Fernández, Antonio Cantillo Molina
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <fstream>
#include <chrono>
using namespace std;

/*
 * @brief struct que encapsula el concepto de cliente de un vendedor cualquiera.
 * @field x Coordenada x del cliente.
 * @field y Coordenada y del cliente.
 * @field id Identificador del cliente.
 * @field visitado Indicador de si el cliente se ha visitado o no.
 */

struct cliente{
    double x;
    double y;
    int id;
    bool visitado = false; //Restriccion Implícita
    double dist=0;
    double estimador=0;
    vector<cliente> ruta_local;

    /*
     * @brief Sobrecarga del operador de igualdad.
     */
    bool operator== (cliente c1) const{
        return (id==c1.id);
    }

    /*
     * @brief Sobrecarga del operador distinto.
     */
    bool operator!= (cliente c1) const{
        return (id!=c1.id);
    }

};

/*
 *  Functor de comparación para la ordenación de la priority_queue
 */

class comparador {
public:
    bool operator()(const cliente &c1, const cliente &c2) {
        return c1.estimador>c2.estimador;
    }
};

/*
 * @brief Clase que encapsula un entorno de trabajo para el Problema del Viajante de Comercio basada en Branch and Bound.
 */

class PVC_BB{
private:

    vector<cliente> clientes;

    vector<cliente> ruta_final;

    double cota_global;

    priority_queue<cliente, vector<cliente>,comparador> rutas;

    /*
     * @brief Metodo que calcula la distancia euclidea entre dos clientes.
     */

    double distancia(cliente cliente1, cliente cliente2){

        return sqrt(pow(abs(cliente1.x-cliente2.x),2) + pow(abs(cliente1.y-cliente2.y),2));
    }

    /*
   * @brief Metodo que devuelve la posicion del minimo en una fila determinada de una matriz de double.
   * @param matriz_dist Matriz de la que obtener la posicion del minimo de la fila.
   * @param pos Fila de la que obtener la posicion del minimo.
   */

    int DevuelveMinimoFila(const vector<vector<double>>& matriz_dist,int pos){
        double min=INFINITY;
        int pos_min = 0;
        for(int i=0;i<matriz_dist[pos].size();++i){
            if(matriz_dist[pos][i]<min && !clientes[i].visitado && i!=pos){
                min = matriz_dist[pos][i];
                pos_min = i;
            }
        }
        return pos_min;
    }


    /*
     * @brief Metodo que devuelve la posicion del minimo de una matriz de double.
     * @param matriz_dist Matriz de la que obtener la posicion del minimo.
     */

    int DevuelveMinimoGrafo(const vector<vector<double>>& matriz_dist){
        double min = INFINITY;
        int pos_min = 0;
        for(int i=0; i<matriz_dist.size();++i){
            if(matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)]<min){
                min = matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)];
                pos_min = i;
            }
        }
        return pos_min;
    };

public:

    /*
   * @brief Calcula la distancia de una ruta de clientes.
   * @param ruta Vector de clientes del aque calcular la distancia.
   */

    double DistanciaTotal(const vector<cliente>& ruta){
        double sol = 0;
        for(int i=0; i<ruta.size()-1; ++i){
            sol+= distancia(ruta[i],ruta[i+1]);
        }
        return sol;
    }


    /*
     * @brief Contructor con parametros.
     * @param clientes Vector de clientes del que calcular el mejor recorrido.
     */

    PVC_BB (const vector<cliente>& clientes){

        this->clientes=clientes;
        ruta_final=clientes;
        cota_global= DistanciaTotal(clientes) + distancia(clientes[0],clientes[clientes.size()-1]);
    }

    vector<vector<double>> CrearMatriz(const vector<cliente>& clientes){
        vector<vector<double>> matriz_dist= vector<vector<double>>(clientes.size(),vector<double>( clientes.size()));
        for(int i=0;i<clientes.size();++i){
            for(int j=0;j<clientes.size();++j){
                matriz_dist[i][j]= distancia(clientes[i],clientes[j]);
            }
        }
        return matriz_dist;
    }

    /*
     * @brief Devuelve el vector ruta solucion.
     */

    vector<cliente> getRutaFinal(){
        return this->ruta_final;
    }


    /*
     * @brief Devuelve la cota global de la ruta.
     */

    double getCotaGlobal(){return this->cota_global;}


    /*
     * @brief Primer estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
     * Selecciona el arco de menor peso y multiplica dicho peso por el numero de ciudades que quedan por visitar.
     * @param matriz_dist Matriz de distancias.
     * @param nodo Nodo del que tomamos los datos del momento.
     */


    double FuncionCota1(const vector<vector<double>>& matriz_dist,cliente nodo){

        double menor_peso = matriz_dist[DevuelveMinimoGrafo(matriz_dist)][DevuelveMinimoFila(matriz_dist,DevuelveMinimoGrafo(matriz_dist))];
        int quedan_por_visitar = clientes.size() - nodo.ruta_local.size();
        return (menor_peso*quedan_por_visitar)+nodo.dist;

    }


    /*
     * @brief Segundo estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
     * Selecciona el arco de menor peso al salir de todos los nodos restantes por visitar, y suma esto a la distancia
     * acumulada del camino ya recorrido.
     * @param matriz_dist Matriz de distancias.
     * @param nodo Nodo del que tomamos los datos del momento.
     */



    double FuncionCota2(const vector<vector<double>>& matriz_dist,cliente nodo){

        double dist_acumulada=nodo.dist;

        for (int i=0; i<matriz_dist.size();++i){
            if (!clientes[i].visitado && i!=nodo.id) {
                dist_acumulada+=matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)];
            }
        }
        return dist_acumulada;
    }


    /*
    * @brief Tercer estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
    * Selecciona el arco de menor peso al salir y entrar en cada nodo, dividiendo por 2.
    * @param matriz_dist Matriz de distancias.
    * @param nodo Nodo del que tomamos los datos del momento.
    */

    double FuncionCota3(const vector<vector<double>>& matriz_dist,cliente nodo){

        vector<vector<double>> m=matriz_dist;
        double aux=0;
        double d=0;
        double min1;

        if(nodo.ruta_local.size()==1) {
            min1=matriz_dist[nodo.ruta_local[0].id][DevuelveMinimoFila(matriz_dist,nodo.ruta_local[0].id)];
            m[nodo.ruta_local[0].id][DevuelveMinimoFila(matriz_dist,nodo.ruta_local[0].id)]=INFINITY;
            d=(min1 + m[nodo.ruta_local[0].id][DevuelveMinimoFila(m,nodo.ruta_local[0].id)])/2;
        }
        else{
            aux=matriz_dist[nodo.ruta_local[0].id][DevuelveMinimoFila(matriz_dist,nodo.ruta_local[0].id)];
            for(int i=0;i<nodo.ruta_local.size()-1;++i){
                d+=((aux+distancia(nodo.ruta_local[i],nodo.ruta_local[i+1]))/2);
                aux=distancia(nodo.ruta_local[i],nodo.ruta_local[i+1]);
            }

            d+=(aux+matriz_dist[nodo.ruta_local.back().id][DevuelveMinimoFila(matriz_dist,nodo.ruta_local.back().id)])/2;

            for (int i=0; i<matriz_dist.size();++i) {
                if(!clientes[i].visitado && i!=nodo.id) {
                    min1=matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)];
                    m[i][DevuelveMinimoFila(matriz_dist,i)] = INFINITY;
                    d+=(min1 + m[i][DevuelveMinimoFila(m,i)])/2;
                }
            }
        }

        return d;
    }


    /*
    * @brief Algoritmo basado en Branch and Bound para el Problema del Viajante de Comercio.
    * @param matriz_dist Matriz de distancias de los clientes.
    * @param Cota Funcion que determina la optimalidad de las soluciones que se van calculando.
    *        @param Matriz de double que se correspondera con la matriz de distancias.
    *        @param Cliente (nodo) del cual se comprobara la optimalidad de su ruta parcial.
    */

    void BB(const vector<vector<double>>& matriz_dist,double (PVC_BB::*Cota)(const vector<vector<double>>&,cliente)) {

        cliente raiz=clientes[0];
        raiz.ruta_local.push_back(clientes[0]);
        raiz.visitado=true;
        clientes[0].visitado=true;

        rutas.push(raiz);

        while (!rutas.empty()){

            cliente cliente_actual=rutas.top();

            rutas.pop();

            for(int i=0;i<clientes.size();++i){
                clientes[i].visitado=false;
            }

            for(int i=0;i<cliente_actual.ruta_local.size();++i){

                clientes[cliente_actual.ruta_local[i].id].visitado=true;

            }

              if (cliente_actual.ruta_local.size()==clientes.size()){
                cliente_actual.dist+= matriz_dist[cliente_actual.id][0]; //Volver al inicio


               if (cliente_actual.dist < cota_global) {
                   cota_global = cliente_actual.dist;
                   ruta_final = cliente_actual.ruta_local;
               }
            }
            else{
                for (int i=1; i<clientes.size();i++) {
                    if (!clientes[i].visitado && clientes[i] != cliente_actual) {
                        cliente hijo;
                        hijo.ruta_local = cliente_actual.ruta_local;
                        hijo.ruta_local.push_back(clientes[i]);
                        hijo.dist = cliente_actual.dist + matriz_dist[i][cliente_actual.id];
                        hijo.x = clientes[i].x;
                        hijo.y = clientes[i].y;
                        hijo.id = clientes[i].id;



                        hijo.estimador=(this->*Cota)(matriz_dist,hijo);

                        if (cota_global>hijo.estimador) {
                            rutas.push(hijo);
                        }
                    }
                }
            }
        }

    }
};

// FUNCIÓN MAIN

int main(int argc, char *argv[]){

    // Comprobación de argumentos.

    if (argc!=2) exit(-1);

    // Tomamos argumentos.

    string fichero=argv[1];

    // Tomamos datos del fichero de entrada y rellenamos el vector de clientes (Dato esencial para nuestro problema).

    ifstream entrada;

    entrada.open(fichero);

    int n_clientes, identif;
    double coord_x, coord_y;

    entrada >> n_clientes;

    vector<cliente> clientes(n_clientes);

    while (!entrada.eof()){
        entrada >> identif >> coord_x >> coord_y;
        clientes[identif].id=identif;
        clientes[identif].x=coord_x;
        clientes[identif].y=coord_y;
        clientes[identif].visitado=false;
    }

    // Como hemos modelizado el problema con una clase, creamos los objetos correspondientes e inicializamos los datos que necesitaremos.

    PVC_BB prueba = PVC_BB(clientes);
    vector<vector<double>> distancias=prueba.CrearMatriz(clientes);

    //double long_inicial= prueba.DistanciaTotal(prueba.getRutaFinal());

    double (PVC_BB::*c1)(const vector<vector<double>>&, cliente) = &PVC_BB::FuncionCota1;
    double (PVC_BB::*c2)(const vector<vector<double>>&, cliente) = &PVC_BB::FuncionCota2;
    double (PVC_BB::*c3)(const vector<vector<double>>&, cliente) = &PVC_BB::FuncionCota3;

    prueba.PVC_BB::BB(distancias, c1);
    //prueba.PVC_BB::BB(distancias, c2);
    //prueba.PVC_BB::BB(distancias, c3);


    //Medida de tiempos.
    /*

    std::chrono::high_resolution_clock::time_point t_antes, t_despues;
    std::chrono::duration<double> transcurrido;

    t_antes = std::chrono::high_resolution_clock::now();

    // Llamada a Backtracking con las diferentes funciones de cota. (Descomentar la línea según la cota que se desee utilizar).

    prueba.PVC_BB::BB(distancias, c1);
    //prueba.PVC_BB::BB(distancias, c2);
    //prueba.PVC_BB::BB(distancias, c3);

    t_despues = std::chrono::high_resolution_clock::now();
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);
    cout << n_clientes << " " << transcurrido.count() << endl;

     */


     // Muestra de resultados.

    vector<cliente> rutafinal=prueba.getRutaFinal();
    for (int i=0; i<rutafinal.size(); i++) cout << "CLIENTE " << rutafinal[i].id<< "--->" << "posicion: " << rutafinal[i].x
                                                << "," << rutafinal[i].y << endl;
    cout <<"FIN RUTA"<<endl;
    cout << "DISTANCIA TOTAL: " << prueba.getCotaGlobal()<<endl;

}