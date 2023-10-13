#!/bin/bash

# Compile and run Hash-main program
cd Hash-main
gcc -o hash_program main.c index.c -Wall
echo "Running Hash Program..."
./hash_program key_file_name txt_file_name
cd ..

# Compile and run Sparse_Matrix-main program
cd Sparse_Matrix-main
gcc -o sparse_program main.c matrix.c matrix_aux.c -Wall
echo "Running Sparse Matrix Program..."
./sparse_program
cd ..
