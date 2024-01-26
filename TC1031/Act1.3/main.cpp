//main.cpp
// Hector Gutierrez
// Camila Rodriguez
// Julian Espinoza
// Cesar Silva

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SituacionP.h"
using namespace std;

int main() {
    // Leer el nombre del archivo
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> nombreArchivo;  

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    vector<Registro> registros;

    string fecha, hora, ubi;
    char puntoEntrada;

    // Aqui se lee el archivo y se guardan los registros en el vector
    // cada uno con su fecha, hora, punto de entrada y UBI
    while (archivo >> fecha >> hora >> puntoEntrada >> ubi) {
        Registro registro(fecha, hora, puntoEntrada, ubi);
        registros.push_back(registro);
    }

    archivo.close();

    //-----------------------------------------------------------

    // Ordenar los registros utilizando Merge Sort
    Registro::ordenaMerge(registros, 0, registros.size() - 1);

    // Mostrar los registros ordenados por UBI + Fecha
    cout << "Registros ordenados por UBI + Fecha:" << endl;
    for (const Registro& reg : registros) {
        cout << reg.ubi  << " " << reg.fecha << endl;
    }


    // Solicitar al usuario la serie a buscar (los primeros tres caracteres del UBI)
    cout << endl;
    string serieABuscar;
    cout << "Ingrese los primeros tres caracteres de la serie a buscar: ";
    cin >> serieABuscar;

    Registro registro;
    registro.busquedaBinaria(registros, serieABuscar);



    return 0;
}
