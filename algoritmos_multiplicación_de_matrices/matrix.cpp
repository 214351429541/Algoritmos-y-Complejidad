#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo binario
vector<vector<double>> leerMatriz(ifstream& archivo) {
    int filas, columnas;
    archivo.read(reinterpret_cast<char*>(&filas), sizeof(filas)); // Lee el número de filas
    archivo.read(reinterpret_cast<char*>(&columnas), sizeof(columnas)); // Lee el número de columnas
    if (!archivo) {
        cerr << "Error al leer el tamaño de la matriz" << endl;
        exit(1); // Termina el programa si ocurre un error al leer el tamaño
    }
    
    vector<vector<double>> matriz(filas, vector<double>(columnas));
    for (int i = 0; i < filas; ++i) {
        archivo.read(reinterpret_cast<char*>(matriz[i].data()), columnas * sizeof(double)); // Lee los datos de la fila
        if (!archivo) {
            cerr << "Error al leer los datos de la matriz" << endl;
            exit(1); // Termina el programa si ocurre un error al leer los datos
        }
    }
    return matriz;
}

// Función para multiplicar dos matrices
vector<vector<double>> multiplicarMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size(); // Asume que las matrices son cuadradas
    vector<vector<double>> C(n, vector<double>(n, 0.0)); // Matriz resultado inicializada en cero

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j]; // Realiza la multiplicación de matrices
            }
        }
    }
    return C;
}

int main() {
    ifstream archivo("matrices.bin", ios::binary); // Abre el archivo en modo binario
    if (!archivo) {
        cerr << "No se pudo abrir el archivo matrices.bin" << endl;
        return 1; // Termina el programa si no se puede abrir el archivo
    }

    vector<vector<vector<double>>> matrices;
    for (int i = 0; i < 10; ++i) {
        matrices.push_back(leerMatriz(archivo)); // Lee 10 matrices del archivo
    }
    archivo.close();

    auto start = high_resolution_clock::now(); // Registra el tiempo de inicio

    vector<vector<double>> resultado = matrices[0]; // Inicializa el resultado con la primera matriz
    for (int i = 1; i < 10; ++i) {
        resultado = multiplicarMatrices(resultado, matrices[i]); // Multiplica las matrices
    }

    auto end = high_resolution_clock::now(); // Registra el tiempo de fin
    auto duration = duration_cast<microseconds>(end - start).count(); // Calcula la duración en microsegundos

    cout << "Tiempo de ejecución para multiplicar las 10 matrices: " << duration << " µs" << endl;

    return 0;
}
