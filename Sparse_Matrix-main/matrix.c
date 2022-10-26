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
#include "matrix.h"
#include "matrix_aux.h"


typedef struct matrix Matrix;

//TAD para criação e manipulação de matrizes. Toda operação deve retornar 0 em caso de sucesso e != 0 em caso de erro.
int matrix_setelem(Matrix* m, int x, int y, float elem) {
	int i;
	struct matrix *aux_l, *aux_c, *before, *after, *new;

	if (elem == 0) return -1;

	new = create_node(x, y, elem);

	//primeiro a coluna... chegando na coluna do esqueleto que iremos adicionar o valor
	aux_c = m;
	aux_c = aux_c->right;
	for (i=1;i!=y;i++){
		aux_c = aux_c->right;
	}

	//caminhando na coluna para adicionar o valor no local correto
	before = aux_c;

	//caminhando nas linhas da coluna
	for (after = aux_c->below; after->line!=aux_c->line && after->line<x; after=after->below){
		before = after;
	}

	//se a coluna estiver vazia
	if (after->line == before->line){
		aux_c->below = new;
		new->below = aux_c;
	}
	else { //se entrar aqui significa que a coluna não está vazia
		//valor existe?
		if (after->line == x){
			after->info = elem;
		}
		//ultimo valor da coluna?
		else if (after->line < x){
			before->below = new;
			new->below = aux_c;
		}
		//adicionar em algum lugar no meio da coluna
		else {
			before->below = new;
			new->below = after;
		}
	}

	//segundo a linha... chegando na linha que iremos adicionar
	aux_l = m;
	aux_l = aux_l->below;
	for (i=1;i!=x;i++){
		aux_l = aux_l->below;
	}
	//caminhando na linha para adicionar o valor no local correto
	before = aux_l;

	after = aux_l->right;
	//caminhando nas colunas da linha
	for (after = aux_l->right; after->column!=aux_l->column && after->column<y; after=after->right){
		before = after;
	}
	//se a linha estiver vazia
	if (after->column == before->column){
		aux_l->right = new;
		new->right = aux_l;
	}
	else { //se entrar aqui significa que a linha não está vazia
		//valor existe?
		if (after->column == y){
			after->info = elem;
		}
		//ultimo valor da linha?
		else if (after->column < y){
			before->right = new;
			new->right = aux_l;
		}
		//adicionar em algum lugar no meio da linha
		else {
			before->right = new;
			new->right = after;
		}
	}
	return 0;
}


int matrix_getelem(const Matrix* m, int x, int y, float *elem) {
  Matrix* temp = m;
  int i, col=0;
  float e=0.0;


  for(i=0;i<y;i++) {
    temp = temp->right;
		col++;
  }

	if((col != y) || (elem == 0)) return -1;

	for (temp = temp->below; temp->line!=x && temp->line!=-1; temp = temp->below);

  if(temp->line == x){
    e = temp->info;
  }else {
		e = 0.0;
  }
	*elem = e;

  return 0;
}



int matrix_add(const Matrix* m, const Matrix* n, Matrix** r) {

  int i;
  int j;
  int lin = 0, col = 0, lin2=0, col2=0;
  float valm1, valm2, valm3;
  Matrix *aux;

	//contando quantidade de linhas
	for (aux = m->below; aux->line!=m->line; aux = aux->below){
		lin++;
	}

	//contando quantidade de colunas
	for (aux = m->right; aux->column!=m->column; aux = aux->right){
		col++;
	}

	//contando quantidade de linhas
	for (aux = n->below; aux->line!=n->line; aux = aux->below){
		lin2++;
	}

	//contando quantidade de colunas
	for (aux = n->right; aux->column!=n->column; aux = aux->right){
		col2++;
	}

	if(lin != lin2 || col != col2){
		printf("As matrizes são incompativeis para serem somadas\n");
	 	return -1;
	 }else{


		*r = create_node(-1, -1, 0);
		criar_esqueleto(lin, col, *r);
		printf("/-Adição-/\n");

  		for (i=1;i<=lin;i++){
    		for (j=1;j<=col;j++){
					matrix_getelem(m, i, j, &valm1);
					matrix_getelem(n, i, j, &valm2);
					valm3 = valm1 + valm2;
					matrix_setelem(*r, i, j, valm3);

   		 		}
			}
		}
	return 0;
}

int matrix_multiply(const Matrix* m, const Matrix* n, Matrix** r) {
	//adding m1 and m2 and place result in result.
  int i,j,k;
  int Mlin = 0, Mcol = 0, Nlin = 0, Ncol = 0;
  float valm1=0.0, valm2=0.0, valm3=0.0;
  const Matrix *aux; // *auxM, *auxN;

	//contando quantidade de linhas M
	for (aux = m->below; aux->line!=m->line; aux = aux->below){
		Mlin++;
	}

	//contando quantidade de colunas M
	for (aux = m->right; aux->column!=m->column; aux = aux->right){
		Mcol++;
	}

	//contando quantidade de linhas N
	for (aux = n->below; aux->line!=n->line; aux = aux->below){
		Nlin++;
	}

	//contando quantidade de colunas N
	for (aux = n->right; aux->column!=n->column; aux = aux->right){
		Ncol++;
	}

	if(Mlin != Ncol || Mcol != Nlin){
		printf("ERRO: As matrizes são incompativeis para serem multiplicadas!\n");
		return -1;
	} else {


		*r = create_node(-1, -1, 0);
		criar_esqueleto(Mlin,Ncol, *r);
		printf("/-Multiplicação-/\n");

 		 for (i=1;i<=Mlin;i++){      				//Percorre linha matrix M
    		for (j=1;j<=Ncol;j++){						//Percorre coluna matrin N
					 valm3 = 0.0;
					for(k=1;k<=Mlin;k++){						//Adiciona valores na Linha M
	 				matrix_getelem(m, i, k, &valm1);
					matrix_getelem(n, k, j, &valm2);

					valm3 = valm3+(valm1*valm2);

					}
					 matrix_setelem(*r, i, j, valm3);
   	 			}

			}
  	  }
	return 0;
}


int matrix_transpose( const Matrix* m, Matrix** r ){
  int i;
  int j;
  int lin = 0, col = 0;
  float valm1;
  struct matrix *aux;

	if(m==NULL) return -1;

	//contando quantidade de linhas
	for (aux = m->below; aux->line!=m->line; aux = aux->below){
		lin++;
	}

	//contando quantidade de colunas
	for (aux = m->right; aux->column!=m->column; aux = aux->right){
		col++;
	}

  *r = create_node(-1, -1, 0);
  criar_esqueleto(lin, col, *r);
	printf("/-Transposta-/\n");


  for (i=1;i<=lin;i++){
    for (j=1;j<=col;j++){
			matrix_getelem(m, i, j, &valm1);
			matrix_setelem(*r, j, i, valm1);

    	}
	}
	return 0;

}

int matrix_create(Matrix** m){
	int lin, col;
	int x, y;
	float elem;
	//int i;
	//struct matrix *aux_l, *aux_c, *before, *after, *new;
	//FILE *pArq;
	//int M,N,aux;

	if(m==NULL) return -1;

	*m = create_node(-1, -1, 0);

	//LENDO TAMANHO DA MATRIZ
	//fscanf(pArq, "%d %d\n", &lin, &col);
	printf("/-Input-/\n");
	scanf("%d %d\n", &lin, &col);
    criar_esqueleto(lin, col, *m);

	//lendo arquivo
	scanf("%d ", &x);
	while (x!=0){
		scanf("%d %f\n", &y, &elem);
    //Adicionando Elementos
    matrix_setelem(*m, x, y, elem);

		//fscanf(pArq, "%d ", &x);
		scanf("%d ", &x);
	}

	return 0;

};

int matrix_destroy(Matrix* m) {
    //resleasing all dynamic memory used by m.
    //Matrix* matrix = m;
    //Matrix* auxLine;
    //Matrix* prev;
	Matrix *head,*tmp;
	//int val;
    int i;
    //int j;
		int lin=0, col=0;
		struct matrix *aux;

		if(m==NULL) return -1;

		//contando quantidade de linhas
		for (aux = m->below; aux->line!=m->line; aux = aux->below){
			lin++;
		}

		//contando quantidade de colunas
		for (aux = m->right; aux->column!=m->column; aux = aux->right){
			col++;
		}
		head = m;
		tmp = head;

		for (i=0;i<=lin;i++){
			tmp = head->right;
			head = tmp;
			while(head->column != -1){
				head = tmp->right;
				free(tmp);
				tmp = head;
			}
			if(head->below != NULL){
					head = head->below;
			}
			free(tmp);
		}

		m=NULL;
    return 0;

}

int matrix_print( const Matrix* m){
	Matrix *aux, *aux2;
	int lin = 0, col = 0;
	int i, j;
	//float zero=0.0;

	if(m==NULL) return -1;

	//contando quantidade de linhas
	for (aux = m->below; aux->line!=m->line; aux = aux->below){
		lin++;
	}

	//contando quantidade de colunas
	for (aux = m->right; aux->column!=m->column; aux = aux->right){
		col++;
	}

	//imprime tamanho da matriz
	printf("\n%d %d\n", lin, col);

	aux = m->below;
	aux2 = aux->right;
	for (i=1; i<=lin; i++){
		for (j=1; j<=col; j++){
			if (aux2->column == j){
				//printf("%f\t", aux2->info);
				printf("%d %d %.1f\n", aux2->line, aux2->column, aux2->info);
				aux2 = aux2->right;
			} //else {
			//	printf("%f\t", zero);
			//}
		}
		//printf("\n");
		aux = aux->below;
		aux2 = aux->right;
	}

	printf("\n");

	return 0;
}