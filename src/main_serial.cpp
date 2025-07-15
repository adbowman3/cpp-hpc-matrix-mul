#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()

using std::vector;
using std::string;
using std::cout;
using std::atoi;

void fillMatrix(vector<double>& mat, int rows, int cols);
void printMatrix(const string& name, const vector<double>& mat, int rows, int cols);
void multiplyMatrices(const vector<double>& A, const vector<double>& B,
                      vector<double>& C, int rowA, int colA, int colB);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./serial <rowA> <colA> <colB>\n";
        return 1;
    }

    int rowA = atoi(argv[1]);
    int colA = atoi(argv[2]);
    int colB = atoi(argv[3]);
    int rowB = colA;

    vector<double> A(rowA * colA);
    vector<double> B(rowB * colB);
    vector<double> C(rowA * colB, 0.0);

    fillMatrix(A, rowA, colA);
    fillMatrix(B, rowB, colB);

    printMatrix("A", A, rowA, colA);
    printMatrix("B", B, rowB, colB);

    multiplyMatrices(A, B, C, rowA, colA, colB);

    printMatrix("C", C, rowA, colB);

    return 0;
}

void fillMatrix(vector<double>& mat, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        mat[i] = static_cast<double>(rand()) / RAND_MAX * 10.0;
    }
}

void printMatrix(const string& name, const vector<double>& mat, int rows, int cols) {
    cout << "Matrix " << name << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << mat[i * cols + j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void multiplyMatrices(const vector<double>& A, const vector<double>& B,
                      vector<double>& C, int rowA, int colA, int colB) {
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
            for (int k = 0; k < colA; ++k) {
                C[i * colB + j] += A[i * colA + k] * B[k * colB + j];
            }
        }
    }
}
