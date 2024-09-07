#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una matriz con valores aleatorios entre 0 y 1
vector<vector<double>> generarMatriz(int filas, int columnas) {
    vector<vector<double>> matriz(filas, vector<double>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = static_cast<double>(rand()) / RAND_MAX; // Genera un valor aleatorio entre 0 y 1
        }
    }
    return matriz;
}

// Función para guardar un vector de matrices en un archivo binario
void guardarMatricesEnArchivo(const vector<vector<vector<double>>>& matrices, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary); // Abre el archivo en modo binario
    if (!archivo) { // Verifica si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (const auto& matriz : matrices) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        archivo.write(reinterpret_cast<const char*>(&filas), sizeof(filas)); // Escribe el número de filas
        archivo.write(reinterpret_cast<const char*>(&columnas), sizeof(columnas)); // Escribe el número de columnas
        for (const auto& fila : matriz) {
            archivo.write(reinterpret_cast<const char*>(fila.data()), columnas * sizeof(double)); // Escribe los valores de la fila
        }
    }

    archivo.close(); // Cierra el archivo
}

int main() {
    srand(time(0)); // Inicializa la semilla para los números aleatorios

    int filas, columnas;
    cout << "Ingrese el número de filas: ";
    cin >> filas;
    cout << "Ingrese el número de columnas: ";
    cin >> columnas;

    vector<vector<vector<double>>> matrices;
    for (int i = 0; i < 10; ++i) { // Genera 10 matrices
        matrices.push_back(generarMatriz(filas, columnas));
    }

    guardarMatricesEnArchivo(matrices, "matrices.bin"); // Guarda las matrices en un archivo binario

    cout << "Matrices generadas y guardadas en matrices.bin" << endl;

    return 0;
}
