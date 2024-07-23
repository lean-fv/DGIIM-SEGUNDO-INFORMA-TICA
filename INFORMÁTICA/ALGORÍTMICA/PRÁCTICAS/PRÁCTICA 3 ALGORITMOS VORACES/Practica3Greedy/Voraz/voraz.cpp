/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

/*
 * Autores: Leandro Jorge Fernández Vega, Elena Abreu Fernández, Antonio Cantillo Molina.
 */

using namespace std;

/*
 * struct que encapsula el concepto de color a nivel de imagen.
 * @field pixel Entero que representa el valor de pixel.
 * @field reps Cantidad de veces que esta el color presente en la imagen.
 * @field cod Codigo asignado a cada pixel tras realizar una codificacion.
 */
struct color{
    int pixel;
    int reps;
    string cod;
};

/*
 * Funcion que convierte un entero decimal a hexadecimal.
 * @param n Numero a convertir.
 * @return Numero hexdeciaml en forma de cadena de caracteres.
 */
string Hexadecimal(int n) {
    stringstream stream;
    stream << hex << n;
    return stream.str();
}

/*
 * Criterio de ordenacion para el algoritmo sort. Servira para ordenar un vector tipo pair<int,int>.
 * @param p1,p2 Parejas a comparar.
*/
bool ordenaReps (const pair<int,int>& p1, const pair<int,int>& p2){

    return p1.second > p2.second;
}


/*
 * Prepara el conjunto de candidatos a utilizar en el algoritmo voraz.
 * @param matriz Matriz de pixeles que representa una imagen.
 * @param f Numero de filas de la matriz.
 * @param c Numero de columnas de la matriz.
 * @return El conjunto de candidatos como vector, ordenado por repeticiones de cada color.
*/
vector<pair<int,int>> Prepara_Candidatos(vector<vector<int>> matriz,int f, int c){

    map<int,int> candidatos;

    for (int i=0; i < f; i++) {
        for (int j = 0; j < c; j++) {

            if(!candidatos.insert(pair<int,int>(matriz[i][j],1)).second){
                candidatos[matriz[i][j]]++;
            }
            //Almacenamos todos los colores presentes en la imagen junto con las veces que se repiten, será nuestro
            //conjunto de candidatos
        }
    }
    //Ordenamos los candidatos de más a menos repeticiones en la imagen

    vector<pair<int,int>> candidatos_ord (candidatos.begin(),candidatos.end());
    sort(candidatos_ord.begin(),candidatos_ord.end(), ordenaReps);

    return candidatos_ord;
}

/*
 * Algoritmo voraz que proporciona una codificacion para una imagen con el objetivo de reducir su tamaño de almacenamiento.
 * @param matriz Matriz de pixeles que representa una imagen.
 * @param f Numero de filas de la matriz.
 * @param c Numero de columnas de la matriz.
 * @return Objeto tipo pair que almacena un vector con la codificacion y el nuevo tamaño segun esta codificacion.
*/
pair<vector<color>,int> Voraz(vector<vector<int>> matriz,int f, int c) {

    //Obtenemos el conjunto de candidatos con las especificaciones necesarias.
    vector <pair<int,int>> candidatos_ord= Prepara_Candidatos(matriz,f,c);

    //Una vez ordenado, procedemos a asignar la codificación correspondiente: asignamos los números que ocupen menos
    //bytes a los píxeles que más se repitan

    //Calculamos el tamaño de nuestra nueva codificación
    vector<color> seleccionados;
    int tamanio=0;
    for(int i=0; i<candidatos_ord.size(); ++i) {
        color seleccionado;
        seleccionado.pixel = candidatos_ord[i].first;
        seleccionado.cod=Hexadecimal(i);
        seleccionado.reps=candidatos_ord[i].second;

        seleccionados.push_back(seleccionado);
        tamanio += (seleccionados[i].cod.length()*seleccionados[i].reps); //Función objetivo
    }

    return pair<vector<color>,int>(seleccionados,tamanio);
}


int main(int argc, char *argv[]) {

    // Comprobación de argumentos

    if(argc!=2) exit(-1);

    // Leemos argumentos

    string fichero=argv[1];

    // Leemos fichero

    ifstream entrada;

    entrada.open(fichero);

    // Tomamos el dato de filas y columnas de la matriz que consideraremos.

    int f,c;
    entrada >> f >> c;

    // Rellenamos la matriz con los datos del fichero

    vector<vector<int>> matriz(f,vector<int>(c));

    for (int i = 0; i < f; i++){
        for (int j = 0; j < c; j++) {
            entrada >> matriz[i][j];
        }
    }

    // Aplicamos el algoritmo voraz a la matriz que hemos rellenado.

    pair<vector<color>,int> result= Voraz(matriz,f,c);

    // Calculamos tamaño de la matriz inicial.

    int tam_inic = 0;
    for(int j=0; j<result.first.size(); ++j){
        tam_inic += (to_string(result.first[j].pixel).length() * result.first[j].reps);
    }

    // Mostramos resultados.

    cout <<"CODIFICACION:" << endl;

    for(int i=0; i< result.first.size(); ++i){
        cout << result.first[i].pixel << setw(4) << result.first[i].reps << setw(4) << result.first[i].cod << endl;
    }

    cout << "TAMAÑO INICIAL: " << tam_inic << endl;
    cout << "TAMAÑO: " << result.second << endl;

    return 0;
}
