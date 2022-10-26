/*
GA-024: Primeiro Trabalho Prático - Matrizes Esparsas

Professor: Antonio Tadeu A. Gomes

Aluno: Leon Sulfierry Corrêa Costa

O presente trabalho apresenta algumas funções a mais que foram utilizadas
para a manipulação do dados, sendo elas:

struct matrix* create_node(int x, int y, float elem);
int criar_esqueleto(int lin, int col, Matrix* m);
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix_aux.h"


typedef struct matrix Matrix;

struct matrix* create_node(int x, int y, float elem){
	struct matrix *node;

	node = (struct matrix*)malloc(sizeof(struct matrix));

	if (node == NULL)exit(-1);

	node->right = NULL;
	node->below = NULL;
	node->line = x;
	node->column = y;
	node->info = elem;
	return node;
};


int criar_esqueleto(int lin, int col, Matrix* m){

	Matrix *aux, *aux2;
	int i;

	if((lin<=0) || (col <=0) || (m == NULL))return -1;

	//CRIANDO ESQUELETO DA MATRIX
	//Criar colunas do esqueleto
	aux = m;

	for (i=1;i<=col;i++){
		aux2 = create_node(-1, i, 0);
		aux->right = aux2;
		aux = aux2;
		aux->below = aux;
	}
	aux->right = m;

	//Criar linhas do esqueleto
	aux = m;
	for (i=1;i<=lin;i++){
		aux2 = create_node(i, -1, 0);
		aux->below = aux2;
		aux = aux2;
		aux->right = aux;
	}
	aux->below = m;

	return 0;
}
