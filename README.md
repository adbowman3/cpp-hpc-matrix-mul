# HPC Matrix Multiply

This project benchmarks a simple serial matrix multiplication in C++.

## Steps

- `main_serial.cpp` implements a basic NxN matrix multiply.
- Next: parallelize with OpenMP.

## Build & Run

```bash
g++ -o serial main_serial.cpp
./serial
