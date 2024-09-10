#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

void leerDataset(const string& nombreArchivo, vector<int>& lista) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo para leer: " << nombreArchivo << endl;
        return;
    }

    int numero;
    while (archivo >> numero) {
        lista.push_back(numero);
    }
    archivo.close();
}

int main() {
    vector<int> lista;

    string nombreArchivo = "dataset_100_1.txt";  // Cambia este nombre según el dataset que quieras leer
    leerDataset(nombreArchivo, lista);

    cout << "El vector sin ordenar: ";
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " ";
    }
    cout << "\n-----------------------------------------------";
    cout << endl;

    auto inicio = std::chrono::high_resolution_clock::now();
    sort(lista.begin(), lista.end());
    auto fin = std::chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "El vector ordenado: ";
    for (int i = 0; i < lista.size(); i++) {
        cout << lista[i] << " ";
    }
    cout << "\n-----------------------------------------------";
    cout << endl;

    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << std::endl;

    return 0;
}