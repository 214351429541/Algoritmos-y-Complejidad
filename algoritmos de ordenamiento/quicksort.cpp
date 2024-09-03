#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;


int partition(vector<int>& arr, int low, int high) {
    // Seleccionar un pivote aleatorio
    int randomIndex = low + rand() % (high - low + 1);
    int pivot = arr[randomIndex];
    // Mover el pivote al final para usar el mismo esquema de partición
    swap(arr[randomIndex], arr[high]);

    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {  // Incrementar comparaciones
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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
    auto start = high_resolution_clock::now();

    quickSort(datos, 0, datos.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // Imprimir tiempo de ejecución, comparaciones e intercambios
    cout << "Tiempo de ejecución: " << duration.count() << " µs" << endl;

    return 0;
}
