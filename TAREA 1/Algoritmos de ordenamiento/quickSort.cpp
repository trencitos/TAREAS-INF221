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

void quickSort(vector<int>& vec, int inicio, int final) {
    if (inicio < final) {
        int pivote = vec[final];

        int i = inicio - 1;
        int j = inicio;

        while (j < final) {
            if (vec[j] < pivote) { 
                i++;
                swap(vec[i], vec[j]);
            }
            j++;
        }

        swap(vec[i + 1], vec[final]);
        
        int n = i + 1;
        quickSort(vec, inicio, n - 1);
        quickSort(vec, n + 1, final);
    }
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
    quickSort(lista, 0, lista.size() - 1);
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