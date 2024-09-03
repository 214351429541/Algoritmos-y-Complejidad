#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    auto start = high_resolution_clock::now();
    int i, j;
    long long numerocomparaciones = 0, intercambios = 0; 
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            numerocomparaciones++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                intercambios++;
            }
        }
        if (swapped == false)
            break;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Tiempo de ejecución: " << duration << " µs"  << endl;
}

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

    int n = datos.size();
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = datos[i]; 
    }

    
    bubbleSort(arr, n); 
    
   
    
    delete[] arr;  

    return 0;
}
