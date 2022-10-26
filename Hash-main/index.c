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

struct linhas {
	int linha;
	struct linhas* proximo;
};

struct palavra {
	char palavra_chave[N];
	int num_ocorrencia;
	struct palavra* proximo;
	struct linhas* nlin;
};

struct index {
	char nome_index[N];
	int num_palavras;
	Hash tabela;
};

// Funcao HASH que converte a palavra no indice da tabela
static int hash(const char *chave){
	int soma = 0;
	float alpha = 0.1, beta = 13.0;
	for(int ini = 0; chave[ini] != '\0' && ini < N; ini++){
		soma += ((int) (chave[ini])*(alpha*ini))/beta;
	}
	return soma % M;
}

Linhas* construir_indice(const char* palavra, char* txt_texto){
	char linhas[1000];
	char *result;

	int c_linha = 0;

	int i;

	int verificador = 0;

	int dif;

	Linhas *lista_indice = NULL;
	Linhas *aux, *aux2;

	FILE *pTexto;

	pTexto = fopen(txt_texto, "rt");

	if(pTexto ==NULL){
		printf("Impossivel abrir o arquivo %s\n", txt_texto);
		exit(-1);
	}

	while (fgets(linhas, 1000, pTexto) != NULL){

		c_linha++;
		verificador = 0;

		for(i = 0; i < strlen(linhas); i++){
			linhas[i] = tolower(linhas[i]);
		}

		if(linhas[strlen(linhas) - 1] == '\n'){
			linhas[strlen(linhas) - 1] = '\0';
		}


		result = strstr(linhas, palavra);

		if(result){
			//Significa que encontrou a palavra em algum lugar na linha
			dif = strlen(linhas) - strlen(result);

			if(dif == 0){
				//Significa que a palavra esta no começo da linha
				//Entao iremos verificar so o que vem depois
				if (!isalpha(linhas[strlen(palavra)])){
					//Significa que apos a palavra nao temos um caracter alfabetico
					verificador = 1;
				}
			} else {
				//Temos que verificar antes e depois
				if (!isalpha(linhas[dif + strlen(palavra)]) && !isalpha(linhas[dif - 1])){
					verificador = 1;
				}
			}
		}

		if (verificador == 1){
			if (lista_indice == NULL){
				//Significa que e o primeiro que estou adicionando
				lista_indice = (Linhas*)malloc(sizeof(Linhas));
				lista_indice->proximo = NULL;
				lista_indice->linha = c_linha;
				aux2 = lista_indice;
			} else {
				aux = (Linhas*)malloc(sizeof(Linhas));
				aux->proximo = NULL;
				aux->linha = c_linha;
				aux2->proximo = aux;
				aux2 = aux2->proximo;
			}
		}
	}
	fclose(pTexto);
	return lista_indice;
}

int index_put(Index *idx, const char *key){
	char palavra_chave[N];

	int id;
	int verificador = 0;
	int contador = 0;

	Palavra *new_t;
	Palavra *aux;

	Linhas *lista_indice;
	Linhas *aux_l, *aux_l_excluir;

	//pTexto = fopen(idx->nome_index, "rt");
	strcpy(palavra_chave, key);

	id = hash(palavra_chave);

	//Inicialiando uma nova palavra para adicionar na tabela
	new_t = (Palavra*)malloc(sizeof(Palavra));
	if (new_t == NULL)
		return 1;
	strcpy(new_t->palavra_chave, palavra_chave);
	new_t->num_ocorrencia = 0;
	new_t->proximo = NULL;
	new_t->nlin = NULL;

	if (idx->tabela[id] == NULL){
		//significa que nao possui palavra neste endereco
		idx->tabela[id] = new_t;
		verificador = 1;
	} else {
		//Ja possui palavra neste endereco, entao temos que adicionar no final da fila ou se a palavra ja existir nao adiciona
		for(aux = idx->tabela[id]; aux->proximo != NULL; aux = aux->proximo){
			if (strcmp(aux->palavra_chave, new_t->palavra_chave) == 0){
				break;
			}
		}
		if (strcmp(aux->palavra_chave, new_t->palavra_chave) != 0){
			aux->proximo = new_t;
			verificador = 1;
		} else {
			free(new_t);
		}
	}

	lista_indice = construir_indice(palavra_chave, idx->nome_index);

	for (aux_l = lista_indice; aux_l != NULL; aux_l = aux_l->proximo){
		contador++;
	}


	if (verificador){
		//Significa que a palavra foi adicionada como nova
		new_t->nlin = lista_indice;
		new_t->num_ocorrencia = contador;
		idx->num_palavras++;
	} else {
		//Sifnifica que a palavra ja existe no Index e iremos apenas atualizar a lista de indices
		for (aux_l = aux->nlin; aux_l != NULL; aux_l = aux_l_excluir){
			aux_l_excluir = aux_l->proximo;
			free(aux_l);
		}
		aux->nlin = lista_indice;
		aux->num_ocorrencia = contador;
	}
	return 0;
}

int index_get( const Index *idx, const char *key, int **occurrences, int *num_occurrences ){
	char palavra_chave[N];

	Palavra *aux;
	Linhas *aux_l;

	int i;
	int id;
	int *vec;

	strcpy(palavra_chave, key);
	id = hash(palavra_chave);

	for (aux = idx->tabela[id]; aux!=NULL && strcmp(palavra_chave, aux->palavra_chave)!=0; aux = aux->proximo);

	if (aux == NULL){
		//Nao encontramos a palavra
		return 1;
	} else {
		//Encontramos a palavra
		*num_occurrences = aux->num_ocorrencia;
		if (aux->num_ocorrencia != 0){
			//siginifica que a palavra esta no indice e tem ocorrencias
			vec = (int*)malloc(aux->num_ocorrencia*sizeof(int));
			aux_l = aux->nlin;
			for (i=0;i<aux->num_ocorrencia;i++){
				vec[i] = aux_l->linha;
				aux_l = aux_l->proximo;
			}
			*occurrences = vec;
		}
	}
	return 0;
}

int index_createfrom( const char *key_file, const char *text_file, Index **idx ){

	Index *novo_idx;
	char palavra[N];
	int i;

	FILE *pArq;

	//Criando novo index
	novo_idx = (Index*)malloc(sizeof(Index));
	for (i=0;i<M;i++){
		novo_idx->tabela[i] = NULL;
	}
	strcpy(novo_idx->nome_index, text_file);
	novo_idx->num_palavras = 0;

	//Adicinando palavras chaves
	pArq = fopen(key_file, "rt");

	if(pArq ==NULL){
		printf("Impossivel abrir o arquivo %s\n", key_file);
		return -1;
	}

	//substituindo quebra linha por terminador
	while(fgets(palavra, N, pArq) != NULL && palavra[0] != '\n'){
		if(palavra[strlen(palavra) - 1] == '\n'){
			palavra[strlen(palavra) - 1] = '\0';
		}
		//convertendo para minusculo
		for(i = 0; i < strlen(palavra); i++){
			palavra[i] = tolower(palavra[i]);
		}

		//Adicionando palavra chave na estrutura INDEX
		index_put(novo_idx, palavra);

	}

	*idx = novo_idx;
	fclose(pArq);
	return 0;
}

int index_print( const Index *idx ){
	const Index *novo_idx = idx;

	Palavra *imprimir = NULL;
	Palavra *actual, *before, *aux;
	Palavra *tabela;

	Linhas *aux_l;//, *aux_l_excluir;

	int i;

	//Precisamos criar um vetor com todas as palavras existente na tabela
	//Depois temos que ordenar estas palavras, assim criei um Fila temporária para armazenar as palavras e depois armazenar.

	for (i=0; i<M; i++){
		tabela = novo_idx->tabela[i];
		while (tabela != NULL){
			//Se possuir palavra nesta posicao da tabela, iremos alocar um novo local para esta palavra e adicionar na fila
			aux = (Palavra*)malloc(sizeof(Palavra));
			strcpy(aux->palavra_chave, tabela->palavra_chave);
			aux->num_ocorrencia = tabela->num_ocorrencia;
			aux->nlin = tabela->nlin;
			aux->proximo = NULL;

			if (imprimir == NULL){
				//Significa que a fila esta vazia, então iremos inicializar
				imprimir = aux;
			} else {
				//Significa que ja temos palavras na fila de impressao, entao precisamos adicionar ordenado na fila
				//Iremos percorrer a fila ate chegar na posicao que iremos adicionar.
				for(actual = imprimir, before = NULL; actual!=NULL && strcmp(aux->palavra_chave, actual->palavra_chave)>0; actual = actual->proximo){
					before = actual;
				}
				if (before == NULL){
					//Significa que o valor que estamos adicionando sera o primeiro da fila
					aux->proximo = imprimir;
					imprimir = aux;
				} else {
					//Significa que o valor que estamos adicionando eh entre before e actual (devido a maneira que construimos o for para percorrer)
					before->proximo = aux;
					aux->proximo = actual;
				}
			}
			//Vai para proxima palavra na mesma posicao, caso for nulo significa que so tem uma palavra e o WHILE termina
			tabela = tabela->proximo;
		}
	}

	if (imprimir == NULL){
		return 1;
	}

	printf("\n");

	before = imprimir;

	for (; imprimir!=NULL; imprimir = imprimir->proximo){
		printf("%s: ", imprimir->palavra_chave);
		for (aux_l = imprimir->nlin; aux_l != NULL; aux_l = aux_l->proximo){
			printf("%d, ", aux_l->linha);
		}
		printf("\n");
	}

	actual = before;

	for (; actual!=NULL; actual = before){
		before = actual->proximo;
		free(actual);
	}

	return 0;
}

int index_free( Index *idx ){
	Palavra *tabela;

	Palavra *aux_p, *aux_p_excluir;
	Linhas *aux_l, *aux_l_excluir;

	int i;

	for (i=0; i<M; i++){
		tabela = idx->tabela[i];
		if (tabela != NULL){
			for (aux_p = tabela; aux_p != NULL; aux_p = aux_p_excluir){
				for (aux_l = aux_p->nlin; aux_l != NULL; aux_l = aux_l_excluir){
					aux_l_excluir = aux_l->proximo;
					free(aux_l);
				}
				aux_p_excluir = aux_p->proximo;
				free(aux_p);
			}
		}
	}

	free(idx);

	return 0;
}