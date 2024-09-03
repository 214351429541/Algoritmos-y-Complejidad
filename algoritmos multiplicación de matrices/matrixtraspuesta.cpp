#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<vector<double>> leerMatriz(ifstream& archivo) {
    int filas, columnas;
    archivo.read(reinterpret_cast<char*>(&filas), sizeof(filas));
    archivo.read(reinterpret_cast<char*>(&columnas), sizeof(columnas));
    if (!archivo) {
        cerr << "Error al leer el tamaño de la matriz" << endl;
        exit(1);
    }
    
    vector<vector<double>> matriz(filas, vector<double>(columnas));
    for (int i = 0; i < filas; ++i) {
        archivo.read(reinterpret_cast<char*>(matriz[i].data()), columnas * sizeof(double));
        if (!archivo) {
            cerr << "Error al leer los datos de la matriz" << endl;
            exit(1);
        }
    }
    return matriz;
}

vector<vector<double>> transponerMatriz(const vector<vector<double>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<double>> transpuesta(columnas, vector<double>(filas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    return transpuesta;
}

vector<vector<double>> multiplicarMatricesOptimizado(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    vector<vector<double>> B_transpuesta = transponerMatriz(B);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B_transpuesta[j][k];
            }
        }
    }
    return C;
}

int main() {
    ifstream archivo("matrices.bin", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo matrices.bin" << endl;
        return 1;
    }

    vector<vector<vector<double>>> matrices;
    for (int i = 0; i < 10; ++i) {
        matrices.push_back(leerMatriz(archivo));
    }
    archivo.close();

    auto start = high_resolution_clock::now();

    vector<vector<double>> resultado = matrices[0];
    for (int i = 1; i < 10; ++i) {
        resultado = multiplicarMatricesOptimizado(resultado, matrices[i]);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Tiempo de ejecución para multiplicar las matrices: " << duration << " µs" << endl;

    return 0;
}
