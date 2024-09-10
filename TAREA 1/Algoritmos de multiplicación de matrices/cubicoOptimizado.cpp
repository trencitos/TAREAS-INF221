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

vector<vector<int>> transponer_B(vector<vector<int>> matrix) {
    int m = matrix.size(); //transponer B: pasar de columna a fila
    int n = matrix[0].size();
    vector<vector<int>> bt(n, vector<int> (m));

    for (int i = 0; i < m; i++) { //fila
        for (int j = 0; j < n; j++) { //columna
            bt[j][i] = matrix[i][j];
        }
    }

    return bt;
}

vector<vector<int>> multiplicacionMatrices(const vector<vector<int>> A, const vector<vector<int>> B) {
    vector<vector<int>> BT = transponer_B(B);
    int n = A.size();
    int m = A[0].size();
    int j = BT.size();
    vector<vector<int>> resultado(n, vector<int> (j, 0));

    for (int i = 0; i < n; i++) { // fila A
        for (int k = 0; k < j; k++) { // fila B
            for (int x = 0; x < m; x++) { // columna A
                resultado[i][k] += A[i][x] * BT[k][x];
            }
        }
    }

    return resultado;
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