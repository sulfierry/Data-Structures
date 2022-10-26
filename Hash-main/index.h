/*
GA-024: Segundo Trabalho Prático - Arquivos Invertidos

Professor: Antonio Tadeu A. Gomes

Aluno: Leon Sulfierry Corrêa Costa

O presente trabalho apresenta algumas funções a mais que foram utilizadas
para a manipulação do dados, sendo elas:

static int hash(const char *chave){
Linhas* construir_indice(const char* palavra, char* txt_texto){
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define N 17       //Quantidade de caracters por palavras
#define M 101      //Tamanho da tabela HASH

typedef struct palavra Palavra;
typedef struct linhas Linhas;
typedef Palavra* Hash[M];
typedef struct index Index;

int index_createfrom( const char *key_file, const char *text_file, Index **idx );
int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences );
int index_put( Index *idx, const char *key );
int index_print( const Index *idx );
int index_free( Index *idx );
