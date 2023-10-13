# Data-Structures

# Hash-Based Index Program

## Overview

This program is a demonstration or test of the functionalities of a hash-based index. It allows the user to create an index, search for a keyword, print the index, insert a new keyword, and then print the updated index.

## Functionalities

1. **Parameter Verification**: Expects two command-line arguments: the name of the key file (`key_file_name`) and the name of the text file (`txt_file_name`). If it does not receive both arguments, it will print an error message and terminate.
2. **Index Creation**: Attempts to create an index from the provided key and text files using the `index_createfrom` function.
3. **Keyword Search**: Prompts the user to enter a keyword. It then tries to search for this keyword in the index. If found, the program will print the occurrences of the keyword; otherwise, it will report that there are no occurrences.
4. **Index Printing**: Pints the full index using the `index_print` function.
5. **New Keyword Insertion**: Prompts the user to enter a new keyword. It then attempts to insert this keyword into the index using the `index_put` function.
6. **Updated Index Printing**: Prints the updated index.
7. **Memory Release**: Releases the memory associated with the index using the `index_free` function.

## Usage

1. **Compilation**:
2. gcc -o program main.c index.c -Wall


2. **Execution**:
./program key_file_name txt_file_name

- `key_file_name`: Name of the file containing the keywords.
- `txt_file_name`: Name of the text file.

3. **Keyword Search**:
After running the program, it will prompt the user to enter a keyword. The program will then attempt to search for this keyword in the index. If found, it will print the occurrences of the keyword. Otherwise, it will report that there are no occurrences.

4. **Insert New Keyword**:
The program will also prompt the user to enter a new keyword and will attempt to insert it into the index.

5. **Viewing**:
The full index will be printed both before and after the insertion of the new keyword.


# Sparse Matrix Program

## Overview

This program demonstrates operations on sparse matrices using linked lists. It provides functionalities to create, add, multiply, transpose, and destroy matrices.

## Functionalities

1. **Matrix Initialization**:
   - The program initializes three matrices: `A`, `B`, and `C`.

2. **Matrix Creation**:
   - Creates matrices `A` and `B` using the `matrix_create` function.
   - If any error occurs during the creation, an error message is printed.

3. **Matrix Addition**:
   - Tries to add matrices `A` and `B` and store the result in matrix `C` using the `matrix_add` function.
   - If there's an error in the addition, it will print an error message.

4. **Matrix Multiplication**:
   - Tries to multiply matrices `A` and `B` and store the result in matrix `C` using the `matrix_multiply` function.
   - If there's an error in multiplication, an error message is printed.

5. **Matrix Transposition**:
   - Tries to transpose matrix `A` and store the result in matrix `C` using the `matrix_transpose` function.
   - If there's an error in transposition, an error message is printed.

6. **Memory Release**:
   - Destroys matrices `A`, `B`, and `C` using the `matrix_destroy` function to release the memory.

## Usage

1. **Compilation**:
gcc -o sparse_program main.c matrix.c matrix_aux.c -Wall


2. **Execution**:
./sparse_program


The program will print matrices after each operation, so you can verify the results. If any error occurs during operations, corresponding error messages will be displayed.

## The script `run_hash_sparse.sh` assume that:

1. You are in the root folder where both "Hash-main" and "Sparse_Matrix-main" directories are located.
2. You have GCC installed for compilation.
3. The command-line arguments for the input files will be provided by the user when running the script.

