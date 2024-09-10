#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    int m = matrix.size(); 
    int n = matrix[0].size(); 

    for (int i = 0; i < m; ++i) {  
        for (int j = 0; j < n; ++j) {  
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> multiplicacionMatrices(const vector<vector<int>> A, const vector<vector<int>> B) {
    int m = A.size(); // filas A
    int n = A[0].size(); // columnas A, filas B
    int j = B[0].size(); // columnas B
    vector<vector<int>> result(m, vector<int>(j, 0));

    for (int i = 0; i < m; i++) { // por fila A
        for (int k = 0; k < j; k++) { //por columna B
            for (int b = 0; b < n; b++) { //por columna A
                result[i][k] += A[i][b] * B[b][k];
            }
        }
    }
    return result;
}

vector<vector<int>> leerMatriz(ifstream& file) {
    int filas, columnas;
    file >> filas >> columnas;
    vector<vector<int>> matrix(filas, vector<int>(columnas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

int main () {
    string filename;
    cout << "Ingrese el nombre del archivo de dataset: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return 1;
    }

    vector<vector<int>> matrixA = leerMatriz(file);
    vector<vector<int>> matrixB = leerMatriz(file);

    cout << "La matriz A es:" << endl;
    printMatrix(matrixA);
    cout << "\nLa matriz B es:" << endl;
    printMatrix(matrixB);

    auto inicio = std::chrono::high_resolution_clock::now();
    vector<vector<int>> resultado = multiplicacionMatrices(matrixA, matrixB);
    auto fin = std::chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "\nLa matriz resultado es:" << endl;   
    printMatrix(resultado);

    cout << "\nTiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}