#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generarDataset(const string& nombreArchivo, int tamaño) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo para escribir: " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < tamaño; ++i) {
        archivo << rand() % 10000 << endl;
    }
    
    archivo.close();
    cout << "Dataset generado: " << nombreArchivo << endl;
}

int main() {
    vector<int> tamaños = {100, 1000, 10000};
    srand(static_cast<unsigned>(time(nullptr)));

    for (int tamaño : tamaños) {
        for (int i = 1; i <= 5; ++i) {
            string nombreArchivo = "dataset_" + to_string(tamaño) + "_" + to_string(i) + ".txt";
            generarDataset(nombreArchivo, tamaño);
        }
    }

    return 0;
}
