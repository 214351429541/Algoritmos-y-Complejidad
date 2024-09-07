#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Función para particionar el arreglo en base al pivote
int partition(vector<int>& arr, int low, int high) {
    // Seleccionar un pivote aleatorio
    int randomIndex = low + rand() % (high - low + 1);
    int pivot = arr[randomIndex];
    // Mover el pivote al final para usar el mismo esquema de partición
    swap(arr[randomIndex], arr[high]);

    int i = low - 1;  // Índice del elemento más pequeño
    for (int j = low; j <= high - 1; j++) {  // Recorre el arreglo
        if (arr[j] < pivot) {  // Si el elemento actual es menor que el pivote
            i++;
            swap(arr[i], arr[j]);  // Intercambiar los elementos
        }
    }
    swap(arr[i + 1], arr[high]);  // Colocar el pivote en su posición final
    return i + 1;  // Devolver el índice del pivote
}

// Función para ordenar el arreglo usando Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {  // Solo continúa si hay más de un elemento
        int pi = partition(arr, low, high);  // Obtener el índice del pivote
        quickSort(arr, low, pi - 1);  // Ordenar la sublista izquierda
        quickSort(arr, pi + 1, high);  // Ordenar la sublista derecha
    }
}

int main() {
    ifstream archivo("datos_parcialmente_ordenados.txt");  // Abre el archivo de datos
    if (!archivo.is_open()) {  // Verifica si el archivo se abrió correctamente
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

    quickSort(datos, 0, datos.size() - 1);  // Ordena los datos usando Quick Sort

    auto stop = high_resolution_clock::now();  // Marca el tiempo de fin
    auto duration = duration_cast<microseconds>(stop - start);  // Calcula la duración en microsegundos

    // Imprimir tiempo de ejecución
    cout << "Tiempo de ejecución: " << duration.count() << " µs" << endl;

    return 0;
}

