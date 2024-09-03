#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Genera una matriz con valores aleatorios entre 0 y 1
vector<vector<double>> generarMatriz(int filas, int columnas) {
    vector<vector<double>> matriz(filas, vector<double>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
    return matriz;
}

// Guarda un vector de matrices en un archivo binario
void guardarMatricesEnArchivo(const vector<vector<vector<double>>>& matrices, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (const auto& matriz : matrices) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        archivo.write(reinterpret_cast<const char*>(&filas), sizeof(filas));
        archivo.write(reinterpret_cast<const char*>(&columnas), sizeof(columnas));
        for (const auto& fila : matriz) {
            archivo.write(reinterpret_cast<const char*>(fila.data()), columnas * sizeof(double));
        }
    }

    archivo.close();
}

int main() {
    srand(time(0)); // Inicializa la semilla para los números aleatorios

    int filas, columnas;
    cout << "Ingrese el número de filas: ";
    cin >> filas;
    cout << "Ingrese el número de columnas: ";
    cin >> columnas;

    vector<vector<vector<double>>> matrices;
    for (int i = 0; i < 10; ++i) {
        matrices.push_back(generarMatriz(filas, columnas));
    }

    guardarMatricesEnArchivo(matrices, "matrices.bin");

    cout << "Matrices generadas y guardadas en matrices.bin" << endl;

    return 0;
}
