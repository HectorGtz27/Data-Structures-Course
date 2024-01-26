// SituacionP.cpp
#define _CRT_SECURE_NO_WARNINGS

#include "SituacionP.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

//  Esta línea de código es parte de la implementación del constructor de la clase Registro y 
// se utiliza para configurar los valores iniciales de los miembros de datos cuando se crea un nuevo objeto Registro.
Registro::Registro(const std::string& f, const std::string& h, char p, const std::string& u)
    : fecha(f), hora(h), punto_entrada(p), ubi(u) {}

void Registro::ordenaMerge(std::vector<Registro>& registros, int inicio, int fin) {
    if (inicio < fin) {
        int mitad = (inicio + fin) / 2;
        ordenaMerge(registros, inicio, mitad); // "Conquer"
        ordenaMerge(registros, mitad + 1, fin); // "Conquer"
        merge(registros, inicio, mitad, fin); // "Combine"
    }
}

void Registro::merge(std::vector<Registro>& registros, int inicio, int mitad, int fin) {
    int n1 = mitad - inicio + 1;
    int n2 = fin - mitad;

    vector<Registro> L(n1);
    vector<Registro> R(n2);

    // Aqui se copian los datos a los vectores temporales L y R
    for (int i = 0; i < n1; i++) {
        L[i] = registros[inicio + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = registros[mitad + 1 + i];
    }

    // Aqui ya se ordenan los datos
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        // Primero, compara por UBI
        //L[i] puede utilizar . para acceder a los miembros de datos de la estructura Registro
        // porque L[i] es un objeto Registro
        if (L[i].ubi < R[j].ubi) { // Si la UBI de L es menor que la UBI de R
            registros[k] = L[i];
            i++;
        }
        else if (L[i].ubi > R[j].ubi) { // Si la UBI de L es mayor que la UBI de R
            registros[k] = R[j];
            j++;
        }
        else { // Si las UBI son iguales, compara por fecha en formato día/mes/año
            std::string fechaL = L[i].fecha;
            std::string fechaR = R[j].fecha;

            int diaL, mesL, anioL, diaR, mesR, anioR;

            // sscanf() es una función de la biblioteca estándar de C que se utiliza para leer datos de una cadena de caracteres.
            // fechaL.c_str() convierte el objeto string fechaL a una cadena de caracteres de C.
            sscanf(fechaL.c_str(), "%d/%d/%d", &diaL, &mesL, &anioL);
            sscanf(fechaR.c_str(), "%d/%d/%d", &diaR, &mesR, &anioR);

            if (anioL < anioR || (anioL == anioR && mesL < mesR) || (anioL == anioR && mesL == mesR && diaL < diaR)) {
                registros[k] = L[i];
                i++;
            }
            else {
                registros[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) { // Aqui se copian los elementos restantes de L
        registros[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) { // Aqui se copian los elementos restantes de R
        registros[k] = R[j];
        j++;
        k++;
    }
}




int Registro::busquedaBinaria(const std::vector<Registro>& registros, const std::string& serieABuscar) {
    int bajo = 0;
    int alto = registros.size() - 1;
    vector<int> resultados;

    while (bajo <= alto) {
        int central = (bajo + alto) / 2;
        const std::string& ubiCentral = registros[central].ubi; // Aqui se toma una UBI del registro que se encuentra en la posición central

        
        if (ubiCentral < serieABuscar) {
            bajo = central + 1;
        }
        else {
            alto = central - 1;
        }

    }

    // Encontrar todas las entradas que coinciden
    int indice = bajo;
    while (indice < registros.size()) {
        const std::string& ubi = registros[indice].ubi;
        // Aqui aunque se inserte 1 elemento lo va comparar igual con el tamaño de la serie a buscar
        if (ubi.substr(0, serieABuscar.size()) == serieABuscar) {
            resultados.push_back(indice);
            indice++;
        }
        else {
            break;
        }

    }

    // Imprimir las entradas encontradas
    if (!resultados.empty()) {
        cout << "Entradas encontradas para la serie " << serieABuscar << ":" << endl;
        for (int resultado : resultados) {
            cout << registros[resultado].ubi << " " << registros[resultado].fecha << " " << registros[resultado].hora << " " << registros[resultado].punto_entrada << endl;
        }
    }
    else {
        cout << "No se encontraron entradas para la serie " << serieABuscar << "." << endl;
    }

    return -1;
}