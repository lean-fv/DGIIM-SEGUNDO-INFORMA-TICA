//
// Autores: Leandro Jorge Fernández Vega, Elena Abreu Fernández, Antonio Cantillo Molina
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
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


    /*
     * @brief Sobrecarga del operador de igualdad.
     */
    bool operator== (cliente c1) const{

        return (id==c1.id);
    }
};

/*
 * @brief Clase que encapsula un entorno de trabajo para el Problema del Viajante de Comercio basada en Backtracking.
 */

class PVC_BT{
private:

    /*
     * @brief Valor que nos permite determinar que distancia total tiene nuestra ruta solucion.
     */
    double cota_global;

    /*
     * @brief Ruta de clientes solucion.
     */
    vector<cliente> rutafinal;

    /*
     * @brief Vector que nos permite ir aniadiendo clientes para obtener posibles soluciones.
     */
    vector<cliente> ruta_actual;

    /*
     * @brief Vector de clientes.
     */

    vector<cliente> clientes;



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
            if(matriz_dist[pos][i]<min && !clientes[i].visitado){ //osquiero chochetes
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
     * @brief Contructor con parametros.
     * @param clientes Vector de clientes del que calcular el mejor recorrido.
     */

    PVC_BT (const vector<cliente>& clientes){

        cota_global=DistanciaTotal(clientes) + distancia(clientes[0],clientes[clientes.size()-1]);;
        this->clientes=clientes;
        rutafinal=clientes;
    }



    /*
     * @brief Metodo que crea una matriz de distacias a partir de un vector de clientes.
     * @param clientes Vector de clientes del que calcular calcular las distancias de todos los clientes con todos.
     */

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
        return this->rutafinal;
    }


    /*
     * @brief Devuelve la cota global de la ruta.
     */
    double getCotaGlobal(){return this->cota_global;}


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
     * @brief Primer estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
     * Selecciona el arco de menor peso y multiplica dicho peso por el numero de ciudades que quedan por visitar.
     * @param matriz_dist Matriz de distancias.
     * @param dist_acumulada Distancia del recorrido ya hecho en la exploracion del grafo.
     */

    double FuncionCota1(const vector<vector<double>>& matriz_dist,double dist_acumulada){

        double menor_peso = matriz_dist[DevuelveMinimoGrafo(matriz_dist)][DevuelveMinimoFila(matriz_dist,DevuelveMinimoGrafo(matriz_dist))];
        int quedan_por_visitar = clientes.size() - ruta_actual.size();
        return (menor_peso*quedan_por_visitar)+dist_acumulada;
    }


    /*
     * @brief Segundo estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
     * Selecciona el arco de menor peso al salir de todos los nodos restantes por visitar, y suma esto a la distancia
     * acumulada del camino ya recorrido.
     * @param matriz_dist Matriz de distancias.
     * @param dist_acumulada Distancia del recorrido ya hecho en la exploracion del grafo.
     */

    double FuncionCota2(const vector<vector<double>>& matriz_dist,double dist_acumulada){

        for (int i=0; i<matriz_dist.size();++i){
            if (!clientes[i].visitado) dist_acumulada+=matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)];
        }
        return dist_acumulada;
    }


    /*
    * @brief Tercer estimador para determinar la validez de las posibles soluciones a lo largo de su construccion.
    * Selecciona el arco de menor peso al salir y entrar en cada nodo, dividiendo por 2.
    * @param matriz_dist Matriz de distancias.
    * @param dist_acumulada Distancia del recorrido ya hecho en la exploracion del grafo.
    */

    double FuncionCota3(const vector<vector<double>>& matriz_dist,double dist_acumulada){
        vector<vector<double>> m=matriz_dist;
        double aux=0;
        double dist=0;
        double min1;

        if(ruta_actual.size()==0) dist=dist_acumulada;
        else if (ruta_actual.size()==1) {
            aux=distancia(ruta_actual[0], ruta_actual[1]);
            dist=(matriz_dist[ruta_actual[0].id][DevuelveMinimoFila(matriz_dist,ruta_actual[0].id)] + aux)/2;
        }
        else{
            min1=matriz_dist[ruta_actual[0].id][DevuelveMinimoFila(matriz_dist,ruta_actual[0].id)];
            m[ruta_actual[0].id][DevuelveMinimoFila(matriz_dist,ruta_actual[0].id)]=INFINITY;
            dist=(min1 + m[ruta_actual[0].id][DevuelveMinimoFila(m,ruta_actual[0].id)])/2;

            for(int i=1;i<ruta_actual.size()-1;++i){
                dist+=((aux+distancia(ruta_actual[i],ruta_actual[i+1]))/2);
                aux=distancia(ruta_actual[i],ruta_actual[i+1]);
            }

            dist+=(aux+matriz_dist[ruta_actual.back().id][DevuelveMinimoFila(matriz_dist,ruta_actual.back().id)])/2;


            for (int i=0; i<matriz_dist.size();++i) {
                if(!clientes[i].visitado) {
                    min1=matriz_dist[i][DevuelveMinimoFila(matriz_dist,i)];
                    m[i][DevuelveMinimoFila(matriz_dist,i)] = INFINITY;
                    dist+=(min1 + m[i][DevuelveMinimoFila(m,i)])/2;
                }
            }
        }

        return dist;
    }



    /*
     * @brief Algoritmo basado en Backtracking para el Problema del Viajante de Comercio.
     * @param pos_actual E-nodo sobre el que se trabaja. Es decir, posible cliente que incluir en la ruta solucion.
     * @param dist_actual Longitud de la ruta que se esta construyendo.
     * @param matriz_dist Matriz de distancias de los clientes.
     * @param Cota Funcion que determina la optimalidad de las soluciones que se van calculando.
     *        @param Matriz de double que se correspondera con la matriz de distancias.
     *        @param Variable double que se correspondera con la distancia acumulada.
     */

    void BT (int pos_actual, double dist_actual, const vector<vector<double>>& matriz_dist, double (PVC_BT::*Cota)(const vector<vector<double>>&,double)){


        if(dist_actual > ((this->*Cota)(matriz_dist,dist_actual))) return;

        if(ruta_actual.size()==clientes.size()){
            dist_actual+=matriz_dist[ruta_actual.back().id][ruta_actual.front().id];

            if(dist_actual<cota_global){
                cota_global=dist_actual;
                rutafinal=ruta_actual;
            }
            return;
        }


        for(int sig=0; sig<rutafinal.size();++sig){
            if(!rutafinal[sig].visitado){

                rutafinal[sig].visitado = true;
                clientes[rutafinal[sig].id].visitado=true;
                ruta_actual.push_back(clientes[rutafinal[sig].id]);

                BT(sig, DistanciaTotal(ruta_actual),matriz_dist,Cota);

                (find(rutafinal.begin(), rutafinal.end(),ruta_actual.back()))->visitado=false;
                clientes[ruta_actual.back().id].visitado=false;
                ruta_actual.pop_back();
            }
        }

    }
};

int main(int argc, char *argv[]) {

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

    PVC_BT prueba = PVC_BT(clientes);
    vector<vector<double>> distancias=prueba.CrearMatriz(clientes);

    double long_inicial= prueba.DistanciaTotal(prueba.getRutaFinal());

    double (PVC_BT::*c1)(const vector<vector<double>>&, double) = &PVC_BT::FuncionCota1;
    double (PVC_BT::*c2)(const vector<vector<double>>&, double) = &PVC_BT::FuncionCota2;
    double (PVC_BT::*c3)(const vector<vector<double>>&, double) = &PVC_BT::FuncionCota3;

    prueba.PVC_BT::BT(0, long_inicial, distancias, c1);
    //prueba.PVC_BT::BT(0, long_inicial, distancias, c2);
    //prueba.PVC_BT::BT(0, long_inicial, distancias, c3);

    //Medida de tiempos.

    /*

    std::chrono::high_resolution_clock::time_point t_antes, t_despues;
    std::chrono::duration<double> transcurrido;

    t_antes = std::chrono::high_resolution_clock::now();

    // Llamada a Backtracking con las diferentes funciones de cota. (Descomentar la línea según la cota que se desee utilizar).

    //prueba.PVC_BT::BT(0, long_inicial, distancias, c1);
    //prueba.PVC_BT::BT(0, long_inicial, distancias, c2);
    prueba.PVC_BT::BT(0, long_inicial, distancias, c3);

    t_despues = std::chrono::high_resolution_clock::now();
    transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);
    cout << n_clientes << " " << transcurrido.count() << endl;


     */

    // Muestra de resultados.

    vector<cliente> rutafinal=prueba.getRutaFinal();
    for (int i=0; i<rutafinal.size(); i++) cout << "CLIENTE " << rutafinal[i].id<< "--->" << "posicion: " << rutafinal[i].x
                                                << "," << rutafinal[i].y << endl;
    cout <<"FIN RUTA"<<endl;
    cout << "DISTANCIA TOTAL: " << prueba.getCotaGlobal();



    return 0;
}