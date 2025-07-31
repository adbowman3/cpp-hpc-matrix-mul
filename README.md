# HPC Matrix Multiply

A minimal C++ matrix multiplication project that demonstrates:
- A clear serial baseline
- A parallelversion using OpenMP

## Steps

- `main.cpp` implements a basic NxN matrix multiply.
- Next:

## Build
### Serial
```bash
g++ -O3 src/main.cpp -o matmul_serial

### Parallel
'''bash
g++ -O3 -fopenmp src/main.cpp -o matmul_parallel

## Run
### Serial
./matmul_serial <# rows in matrix A> <# columns in matrix A> <# columns in matrix B>

### Parallel
./matmul_parallel <# rows in matrix A> <# columns in matrix A> <# columns in matrix B> [# thread]
