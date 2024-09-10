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

vector<int> mergeSort (vector<int> vec) {
    int size = vec.size();
    int m = size/2;

    if (size <= 1) {
        return vec;
    } 

    vector<int> v1(vec.begin(), vec.begin() + m);
    vector<int> v2(vec.begin() + m, vec.end());

    v1 = mergeSort(v1);
    v2 = mergeSort(v2);
    vector<int> v(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    return v;
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
    lista = mergeSort(lista);
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