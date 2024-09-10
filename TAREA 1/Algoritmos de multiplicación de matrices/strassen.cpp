#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

/*
El siguiente algoritmo de Strassen fue sacado de:
https://www.geeksforgeeks.org/strassens-matrix-multiplication/
*/

// Función para sumar dos matrices
vector<vector<int>> suma(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función para restar dos matrices
vector<vector<int>> resta(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Multiplicación de matrices usando el algoritmo de Strassen
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) { // Caso base
        return {{A[0][0] * B[0][0]}};
    }

    if (n <= 64) {
        vector<vector<int>> C(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    int newSize = n / 2;
    vector<int> inner(newSize);
    vector<vector<int>> a11(newSize, inner), a12(newSize, inner), a21(newSize, inner), a22(newSize, inner);
    vector<vector<int>> b11(newSize, inner), b12(newSize, inner), b21(newSize, inner), b22(newSize, inner);

    // Dividir matrices A y B en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular las siete multiplicaciones de Strassen
    vector<vector<int>> M1 = strassen(suma(a11, a22), suma(b11, b22));
    vector<vector<int>> M2 = strassen(suma(a21, a22), b11);
    vector<vector<int>> M3 = strassen(a11, resta(b12, b22));
    vector<vector<int>> M4 = strassen(a22, resta(b21, b11));
    vector<vector<int>> M5 = strassen(suma(a11, a12), b22);
    vector<vector<int>> M6 = strassen(resta(a21, a11), suma(b11, b12));
    vector<vector<int>> M7 = strassen(resta(a12, a22), suma(b21, b22));

    // Calcular las submatrices del resultado
    vector<vector<int>> c11 = suma(resta(suma(M1, M4), M5), M7);
    vector<vector<int>> c12 = suma(M3, M5);
    vector<vector<int>> c21 = suma(M2, M4);
    vector<vector<int>> c22 = suma(resta(suma(M1, M3), M2), M6);

    // Combinar submatrices en la matriz resultado
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }

    return C;
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

// Función para imprimir una matriz
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

int main() {
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

    cout << "Matriz A:" << endl;
    printMatrix(matrixA);
    cout << "\nMatriz B:" << endl;
    printMatrix(matrixB);
    auto inicio = chrono::high_resolution_clock::now();
    vector<vector<int>> C = strassen(matrixA, matrixB);
    auto final = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = final - inicio;

    cout << "\nResultado" << endl;
    printMatrix(C);
    cout << "\nTiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}
