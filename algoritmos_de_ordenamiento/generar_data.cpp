#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Función para guardar los datos en un archivo de texto
void guardarDatosTexto(const vector<int>& datos, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);  // Abre el archivo en modo escritura
    if (archivo.is_open()) {  // Verifica si el archivo se abrió correctamente
        for (const auto& dato : datos) {  // Recorre todos los datos
            archivo << dato << "\n";  // Escribe cada dato en una nueva línea
        }
        archivo.close();  // Cierra el archivo después de escribir
    }
}

// Función para generar datos aleatorios
vector<int> generarDatosAleatorios(int size) {
    vector<int> datos(size);  // Crea un vector de enteros con el tamaño especificado
    for (int i = 0; i < size; i++) {  // Llena el vector con números aleatorios
        datos[i] = rand() % size;  // Genera un número aleatorio entre 0 y size-1
    }
    return datos;  // Devuelve el vector con datos aleatorios
}

// Función para generar datos semiordenados
vector<int> generarDatosSemiOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);  // Genera datos aleatorios
    sort(datos.begin(), datos.begin() + size / 2);  // Ordena la primera mitad del vector
    return datos;  // Devuelve el vector parcialmente ordenado
}

// Función para generar datos parcialmente ordenados
vector<int> generarDatosParcialmenteOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);  // Genera datos aleatorios
    sort(datos.begin(), datos.begin() + size * 0.75);  // Ordena el 75% del vector
    return datos;  // Devuelve el vector parcialmente ordenado
}

// Función para generar datos completamente ordenados
vector<int> generarDatosCompletamenteOrdenados(int size) {
    vector<int> datos = generarDatosAleatorios(size);  // Genera datos aleatorios
    sort(datos.begin(), datos.end());  // Ordena todo el vector
    return datos;  // Devuelve el vector completamente ordenado
}

int main() {
    srand(time(0));  // Inicializa la semilla para la generación de números aleatorios
    int size;
    cout << "Ingrese el tamaño del vector: ";  // Solicita al usuario el tamaño del vector
    cin >> size;  // Lee el tamaño del vector ingresado por el usuario

    // Genera distintos tipos de datasets
    vector<int> datosAleatorios = generarDatosAleatorios(size);
    vector<int> datosSemiOrdenados = generarDatosSemiOrdenados(size);
    vector<int> datosParcialmenteOrdenados = generarDatosParcialmenteOrdenados(size);
    vector<int> datosCompletamenteOrdenados = generarDatosCompletamenteOrdenados(size);

    // Guarda los datos generados en archivos de texto
    guardarDatosTexto(datosAleatorios, "datos_aleatorios.txt");
    guardarDatosTexto(datosSemiOrdenados, "datos_semi_ordenados.txt");
    guardarDatosTexto(datosParcialmenteOrdenados, "datos_parcialmente_ordenados.txt");
    guardarDatosTexto(datosCompletamenteOrdenados, "datos_completamente_ordenados.txt");

    cout << "Datasets generados y guardados en archivos de texto.\n";  // Mensaje de confirmación

    return 0;
}

