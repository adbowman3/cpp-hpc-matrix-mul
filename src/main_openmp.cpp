#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "/usr/local/opt/libomp/include/omp.h"

void fillMatrix(std::vector<double>& mat, int rows, int cols);
void printMatrix(const std::string& name, const std::vector<double>& mat, int rows, int cols);
void multiplyMatricesOMP(const std::vector<double>& A, const std::vector<double>& B,
                      std::vector<double>& C, int rowA, int colA, int colB, int threads);

int main(int argc, char* argv[]) {

    if (argc != 5) {
        std::cout << "Usage: ./mm <rowA> <colA> <colB> <threads>\n";
        return 1;
    }

    int rowA = std::atoi(argv[1]);
    int colA = std::atoi(argv[2]);
    int colB = std::atoi(argv[3]);
    int threads = std::atoi(argv[4]);
    int rowB = colA;
    
    std::srand(123);
    
    std::vector<double> A(rowA * colA);
    std::vector<double> B(rowB * colB);
    std::vector<double> C(rowA * colB);

    fillMatrix(A, rowA, colA);
    fillMatrix(B, rowB, colB);

    if (rowA <= 10 && colA <= 10 && colB <= 10) {
        printMatrix("A", A, rowA, colA);
        printMatrix("B", B, rowB, colB);
    }

    auto start = std::chrono::high_resolution_clock::now();


    multiplyMatricesOMP(A, B, C, rowA, colA, colB, threads);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (rowA <= 10 && colA <= 10 && colB <= 10) {
        printMatrix("C", C, rowA, colB);
    }

    std::cout << "Time taken for matrix multiplication: " << duration.count() << " seconds\n";

    return 0;
}

void fillMatrix(std::vector<double>& mat, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        mat[i] = static_cast<double>(rand()) / RAND_MAX * 10.0;
    }
}

void printMatrix(const std::string& name, const std::vector<double>& mat, int rows, int cols) {
    std::cout << "Matrix " << name << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << mat[i * cols + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void multiplyMatricesOMP(const std::vector<double>& A, const std::vector<double>& B,
                      std::vector<double>& C, int rowA, int colA, int colB, int threads) {
    if (threads > 0) omp_set_num_threads(threads);
    #pragma omp parallel for collapse(2) schedule(static) default(none) \
        shared(A, B, C, rowA, colA, colB)
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
            double sum = 0.0;
            for (int k = 0; k < colA; ++k) {
                sum += A[i * colA + k] * B[k * colB + j];
            }
            C[i * colB + j] = sum;
        }
    }
}
