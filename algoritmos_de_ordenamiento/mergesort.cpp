#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Función para fusionar dos subarreglos ordenados
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Tamaño del primer subarreglo
    int n2 = right - mid;     // Tamaño del segundo subarreglo
    vector<int> L(n1), R(n2); // Vectores para los subarreglos temporales

    // Copia los datos del subarreglo izquierdo a L
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    // Copia los datos del subarreglo derecho a R
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0; // Índices para los subarreglos L y R
    int k = left;     // Índice para el arreglo original

    // Fusiona los subarreglos L y R en el arreglo original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes de L, si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia los elementos restantes de R, si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función para ordenar un arreglo usando Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return; // Caso base: el subarreglo tiene un solo elemento

    int mid = left + (right - left) / 2; // Encuentra el punto medio
    mergeSort(arr, left, mid);           // Ordena la primera mitad
    mergeSort(arr, mid + 1, right);      // Ordena la segunda mitad
    merge(arr, left, mid, right);        // Fusiona las dos mitades
}

int main() {
    ifstream archivo("datos_parcialmente_ordenados.txt"); // Abre el archivo de datos
    if (!archivo.is_open()) { // Verifica si el archivo se abrió correctamente
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<int> datos;  // Vector para almacenar los datos del archivo
    string linea;
    while (getline(archivo, linea)) { // Lee cada línea del archivo
        datos.push_back(stoi(linea)); // Convierte la línea a entero y la agrega al vector
    }

    archivo.close(); // Cierra el archivo

    auto start = high_resolution_clock::now(); // Marca el tiempo de inicio
    
    mergeSort(datos, 0, datos.size() - 1); // Ordena los datos usando Merge Sort
    
    auto stop = high_resolution_clock::now(); // Marca el tiempo de fin
    auto duration = duration_cast<microseconds>(stop - start); // Calcula la duración en microsegundos
    cout << "Tiempo de ejecución: " << duration.count() << " µs" << endl; // Muestra el tiempo de ejecución

    return 0;
}

