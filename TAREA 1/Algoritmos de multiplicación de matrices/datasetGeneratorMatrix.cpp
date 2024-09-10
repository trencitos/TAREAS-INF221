#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una matriz aleatoria
vector<vector<int>> generate_random_matrix(int rows, int cols, int min_val, int max_val) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = min_val + rand() % (max_val - min_val + 1);
        }
    }
    return matrix;
}

// Función para generar un archivo con dos matrices aleatorias
void generate_matrix_dataset(const string& filename, int size, int min_val, int max_val) {
    vector<vector<int>> matrix_A = generate_random_matrix(size, size, min_val, max_val);
    vector<vector<int>> matrix_B = generate_random_matrix(size, size, min_val, max_val);

    ofstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    // Escribir la matriz A
    file << size << " " << size << endl;
    for (const auto& row : matrix_A) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }

    // Escribir la matriz B
    file << size << " " << size << endl;
    for (const auto& row : matrix_B) {
        for (const auto& value : row) {
            file << value << " ";
        }
        file << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int min_val = 1;
    int max_val = 1000;

    int size;
    cout << "Ingrese dimensión de las matrices: ";
    cin >> size;

    for (int i = 0; i < 2; ++i) {
        string filename = "dataset" + to_string(i) + ".txt";
        generate_matrix_dataset(filename, size, min_val, max_val);
    }

    return 0;
}
