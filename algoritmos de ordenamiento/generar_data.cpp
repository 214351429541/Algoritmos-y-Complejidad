#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void guardarDatosTexto(const vector<int>& datos, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const auto& dato : datos) {
            archivo << dato << "\n";
        }
        archivo.close();
    }
}

vector<int> generarDatosAleatorios(int size) {
    vector<int> datos(size);
    for (int i = 0; i < size; i++) {
        datos[i] = rand() % size;
    }
    return datos;
}

vector<int> generarDatosSemiOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);
    sort(datos.begin(), datos.begin() + size / 2); 
    return datos;
}

vector<int> generarDatosParcialmenteOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);
    sort(datos.begin(), datos.begin() + size * 0.75);  
    return datos;
}

vector<int> generarDatosCompletamenteOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);
    sort(datos.begin(), datos.end());  
    return datos;
}

int main() {
    srand(time(0));  
    int size;
    cout << "Ingrese el tamaño del vector: ";
    cin >> size;
    vector<int> datosAleatorios = generarDatosAleatorios(size);
    vector<int> datosSemiOrdenados = generarDatosSemiOrdenados(size);
    vector<int> datosParcialmenteOrdenados = generarDatosParcialmenteOrdenados(size);
    vector<int> datosCompletamenteOrdenados = generarDatosCompletamenteOrdenados(size);
    guardarDatosTexto(datosAleatorios, "datos_aleatorios.txt");
    guardarDatosTexto(datosSemiOrdenados, "datos_semi_ordenados.txt");
    guardarDatosTexto(datosParcialmenteOrdenados, "datos_parcialmente_ordenados.txt");
    guardarDatosTexto(datosCompletamenteOrdenados, "datos_completamente_ordenados.txt");

    cout << "Datasets generados y guardados en archivos de texto.\n";

    return 0;
}
