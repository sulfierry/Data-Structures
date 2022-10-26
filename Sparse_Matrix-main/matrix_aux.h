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



	struct matrix{
		struct matrix* right;
		struct matrix* below;
		int line;
		int column;
		float info;
	};
	typedef struct matrix Matrix;

	struct matrix* create_node(int x, int y, float elem);

	int criar_esqueleto(int lin, int col, Matrix* m);