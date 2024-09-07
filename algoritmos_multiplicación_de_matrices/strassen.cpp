#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

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

// Función para sumar dos matrices
vector<vector<double>> sumarMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size(); // Asume que las matrices son cuadradas
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j]; // Suma elemento a elemento
        }
    }
    return C;
}

// Función para restar dos matrices
vector<vector<double>> restarMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size(); // Asume que las matrices son cuadradas
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j]; // Resta elemento a elemento
        }
    }
    return C;
}

// Función para multiplicar dos matrices usando el algoritmo de Strassen
vector<vector<double>> multiplicarMatricesStrassen(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size(); // Asume que las matrices son cuadradas
    if (n == 1) {
        return {{A[0][0] * B[0][0]}}; // Caso base: multiplicación de matrices 1x1
    }

    int k = n / 2; // División de la matriz en bloques
    vector<vector<double>> A11(k, vector<double>(k)), A12(k, vector<double>(k)), A21(k, vector<double>(k)), A22(k, vector<double>(k));
    vector<vector<double>> B11(k, vector<double>(k)), B12(k, vector<double>(k)), B21(k, vector<double>(k)), B22(k, vector<double>(k));

    // División de las matrices A y B en submatrices
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Cálculo de las 7 matrices intermedias usando Strassen
    auto M1 = multiplicarMatricesStrassen(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    auto M2 = multiplicarMatricesStrassen(sumarMatrices(A21, A22), B11);
    auto M3 = multiplicarMatricesStrassen(A11, restarMatrices(B12, B22));
    auto M4 = multiplicarMatricesStrassen(A22, restarMatrices(B21, B11));
    auto M5 = multiplicarMatricesStrassen(sumarMatrices(A11, A12), B22);
    auto M6 = multiplicarMatricesStrassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    auto M7 = multiplicarMatricesStrassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Combinación de las matrices intermedias para obtener el resultado final
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + k] = M3[i][j] + M5[i][j];
            C[i + k][j] = M2[i][j] + M4[i][j];
            C[i + k][j + k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
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
        resultado = multiplicarMatricesStrassen(resultado, matrices[i]); // Multiplica las matrices usando el algoritmo de Strassen
    }

    auto end = high_resolution_clock::now(); // Registra el tiempo de fin
    auto duration = duration_cast<microseconds>(end - start).count(); // Calcula la duración en microsegundos

    cout << "Tiempo de ejecución para multiplicar las 10 matrices: " << duration << " µs" << endl;

    return 0;
}

