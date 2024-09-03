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

vector<vector<double>> sumarMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<double>> restarMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

vector<vector<double>> multiplicarMatricesStrassen(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;
    vector<vector<double>> A11(k, vector<double>(k)), A12(k, vector<double>(k)), A21(k, vector<double>(k)), A22(k, vector<double>(k));
    vector<vector<double>> B11(k, vector<double>(k)), B12(k, vector<double>(k)), B21(k, vector<double>(k)), B22(k, vector<double>(k));

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

    auto M1 = multiplicarMatricesStrassen(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    auto M2 = multiplicarMatricesStrassen(sumarMatrices(A21, A22), B11);
    auto M3 = multiplicarMatricesStrassen(A11, restarMatrices(B12, B22));
    auto M4 = multiplicarMatricesStrassen(A22, restarMatrices(B21, B11));
    auto M5 = multiplicarMatricesStrassen(sumarMatrices(A11, A12), B22);
    auto M6 = multiplicarMatricesStrassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    auto M7 = multiplicarMatricesStrassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

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
        resultado = multiplicarMatricesStrassen(resultado, matrices[i]);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Tiempo de ejecución para multiplicar las 10 matrices: " << duration << " µs" << endl;

    return 0;
}
