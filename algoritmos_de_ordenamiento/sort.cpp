#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    ifstream archivo("datos_parcialmente_ordenados.txt"); // Abre el archivo de datos
    if (!archivo.is_open()) { // Verifica si el archivo se abrió correctamente
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<int> datos;  // Vector para almacenar los datos del archivo
    string linea;
    while (getline(archivo, linea)) {  // Lee cada línea del archivo
        datos.push_back(stoi(linea));  // Convierte la línea a entero y la agrega al vector
    }

    archivo.close();  // Cierra el archivo

    auto start = high_resolution_clock::now();  // Marca el tiempo de inicio

    // Ordenar el vector usando std::sort
    sort(datos.begin(), datos.end());  // Ordena el vector de forma ascendente

    auto stop = high_resolution_clock::now();  // Marca el tiempo de fin
    auto duration = duration_cast<microseconds>(stop - start);  // Calcula la duración en microsegundos

    // Imprimir tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " µs" << endl;

    return 0;
}
