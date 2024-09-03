#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    ifstream archivo("datos_parcialmente_ordenados.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<int> datos;
    string linea;
    while (getline(archivo, linea)) {
        datos.push_back(stoi(linea));
    }

    archivo.close();
    auto start = high_resolution_clock::now();

    // Ordenar el vector usando std::sort
    sort(datos.begin(), datos.end());

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // Imprimir tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " µs" << endl;

    return 0;
}
