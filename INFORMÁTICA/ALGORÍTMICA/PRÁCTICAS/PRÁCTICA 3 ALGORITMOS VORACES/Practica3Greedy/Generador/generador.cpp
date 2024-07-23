/*
 * @authors Elena Abreu, Antonio Cantillo, Leandro Jorge Fernández
*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    // Comprobación de argumentos

    if(argc != 4) exit(-1);

    // Tomamos argumentos

    string fichero=argv[1];
    int filas=stoi(argv[2]);
    int cols=stoi(argv[3]);

    ofstream salida;
    salida.open(fichero);

    // Rellenamos el fichero con los datos de la matriz

    salida << filas << " " << cols << endl;

    //Recorrer matriz y meter elem en salida
    const int TOPE_RANDOM=255;
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < cols; j++) {
            salida << rand() % TOPE_RANDOM << " ";
        }
        salida << endl;
    }

    // Cerramos el fichero y lo devolvemos.
    salida.close();

    return 0;
}