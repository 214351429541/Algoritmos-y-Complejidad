#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;

// Función para realizar el algoritmo de ordenamiento Bubble Sort
void bubbleSort(int arr[], int n) {
    auto start = high_resolution_clock::now();  // Inicia el cronómetro para medir el tiempo de ejecución
    int i, j;
    long long numerocomparaciones = 0, intercambios = 0;  // Variables para contar comparaciones e intercambios
    bool swapped;  // Variable que indica si hubo un intercambio en la pasada actual

    // Ciclo exterior que controla el número de pasadas
    for (i = 0; i < n - 1; i++) {
        swapped = false;  // Resetea la variable antes de cada pasada

        // Ciclo interior que compara elementos adyacentes
        for (j = 0; j < n - i - 1; j++) {
            numerocomparaciones++;  // Incrementa el contador de comparaciones

            // Si el elemento actual es mayor que el siguiente, se intercambian
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  // Intercambio
                swapped = true;  // Marca que se realizó un intercambio en esta pasada
                intercambios++;  // Incrementa el contador de intercambios
            }
        }

        // Si no hubo intercambios en la pasada actual, el arreglo ya está ordenado
        if (swapped == false)
            break;
    }

    auto end = high_resolution_clock::now();  // Detiene el cronómetro
    auto duration = duration_cast<microseconds>(end - start).count();  // Calcula la duración en microsegundos

    // Imprime el tiempo de ejecución en microsegundos
    cout << "Tiempo de ejecución: " << duration << " µs" << endl;
}

int main() {
    ifstream archivo("");  // Abre el archivo de datos para lectura

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) { 
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<int> datos;  // Vector para almacenar los datos del archivo
    string linea;

    // Lee cada línea del archivo y la convierte a entero, agregándola al vector
    while (getline(archivo, linea)) { 
        datos.push_back(stoi(linea));
    }

    archivo.close();  // Cierra el archivo

    int n = datos.size();  // Obtiene el número de elementos leídos
    int* arr = new int[n];  // Crea un arreglo dinámico para almacenar los datos

    // Copia los datos del vector al arreglo dinámico
    for (int i = 0; i < n; i++) {
        arr[i] = datos[i]; 
    }

    // Llama a la función de ordenamiento bubbleSort
    bubbleSort(arr, n); 

    // Libera la memoria del arreglo dinámico
    delete[] arr;  

    return 0;
}

