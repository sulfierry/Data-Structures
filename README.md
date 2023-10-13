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

