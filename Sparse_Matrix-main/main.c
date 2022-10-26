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
#include "matrix.h"

int main( void ) {

/* Inicializacao da aplicacao ... */
	Matrix *A=NULL;
	Matrix *B=NULL;
	Matrix *C=NULL;


	if( !matrix_create( &A ) )
		matrix_print( A );
	else {
		fprintf( stderr, "Erro na alocacao de A como listas encadeadas.\n" );
		return 1;
	}


	if( !matrix_create( &B ) )
		matrix_print( B );
	else {
		fprintf( stderr, "Erro na alocacao de B como listas encadeadas.\n" );
		return 1;
	}

	if ( !matrix_add( A, B, &C ) ) {
	matrix_print( C );
	} 	else
		fprintf( stderr, "Erro na soma C=A+B.\n" );

	matrix_destroy( C );


	if ( !matrix_multiply( A, B, &C ) )
		matrix_print( C );
	else
	fprintf( stderr, "Erro na multiplicacao C=A*B.\n" );

	matrix_destroy( C );

	if ( !matrix_transpose( A, &C ) )
		matrix_print( C );
	else
		fprintf( stderr, "Erro na transposicao C=A^T.\n" );

	matrix_destroy( C );
	matrix_destroy( A );
	matrix_destroy( B );

	return 0;
}
