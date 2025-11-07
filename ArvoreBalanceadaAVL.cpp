#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int valor;
	struct node *esquerdo, *direito;
	int altura;
}Node;

/*
funçao que cria um novo nó x -> valor a se 
inserido no nó retorna o endereço que do nó
criado.
*/
Node* novoNode(int x){
	Node *novo =(Node*) malloc(sizeof(Node));
	
	if(novo){
		novo->valor = x;
		novo->esquerdo = NULL;
		novo->direito = NULL;
		novo->altura = 0;
	}
	else{
		printf("\nErro ao alocar no em novoNode!\n");
	}
	return novo;
}

/*
retorna o maior dentre dois valores
a, b -> altura de dois nós da árvore
*/
int maior(short a, short b){
	return (a > b)? a: b;
}

//retorna a altura de um nó ou -1 caso ele seja null
int alturaDoNode(Node *node){
	if(node == NULL){
		return -1;
	}
	else{
		return node->altura;
	}	
}

//calcula e retorna o fator de balanceamento de um nó
int fatorDeBalanceamento(Node *node){
	if(node){
		return (alturaDoNode(node->esquerdo) - alturaDoNode(node->direito));
	}
	else{
		return 0;
	}
}

//funcao para a rotaçao a esquerda
Node* rotacaoEsquerdo(Node *r){
	Node *y, *f;
	
	y = r->direito;
	f = y->esquerdo;
	
	y->esquerdo = r;
	r->direito = f;
	
	r->altura = maior(alturaDoNode(r->esquerdo), alturaDoNode(r->direito)) +1;
	y->altura = maior(alturaDoNode(y->esquerdo), alturaDoNode(y->direito)) +1;
	
	return y;
}

//funcao para a rotaçao a direita
Node* rotacaoDireito(Node *r){
	Node *y, *f;
	
	y = r->esquerdo;
	f = y->direito;
	
	y->direito = r;
	f->esquerdo = f;
	
	r->altura = maior(alturaDoNode(r->esquerdo), alturaDoNode(r->direito)) +1;
	y->altura = maior(alturaDoNode(y->esquerdo), alturaDoNode(y->direito)) +1;
	
	return y;
}

//funcao para rotacao direita e depois esquerda
Node* rotacaoDireitoEsquerdo(Node *r){
	r->direito = rotacaoDireito(r->direito);
	return rotacaoEsquerdo(r);
}

//funcao para rotacao esquerda e depois direita
Node* rotacaoEsquerdoDireito(Node *r){
	r->esquerdo = rotacaoEsquerdo(r->esquerdo);
	return rotacaoDireito(r);
}

/*
funcao para realizar o balanceamento das arvore apos uma isercao ou remocao 
recebe o no que esta desbalanceado e retonr a nova raiz apos o balanceamento
*/
Node* balancear(Node *raiz){
	int  fb = fatorDeBalanceamento(raiz);
	
	//rotacao a esquerda
	if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0){
		raiz = rotacaoEsquerdo(raiz);
	}
	//rotacao a direita
	else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0){
		raiz = rotacaoDireito(raiz);
	}
	//rotacao dupla a esquerda
	else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0){
		raiz = rotacaoEsquerdoDireito(raiz);
	}
	//rotacao dupla a direita
	if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0){
		raiz = rotacaoDireitoEsquerdo(raiz);
	}
	return raiz;
}
/*
insere um novo no na arvore
raiz -> raiz da arvore
x ->  valor a ser inserido
retorno: endereco do novo no ou nova raiz apos o balanceamento
*/
Node* inserir(Node *raiz, int x){
	if(raiz == NULL){  //arvore vazia
		return novoNode(x);
	}
	else{ //insecao sera a esquerda ou a direita
		if(x < raiz->valor){
			raiz->esquerdo = inserir(raiz->esquerdo, x);
		}
		else if(x > raiz->valor){
			raiz->direito = inserir(raiz->direito, x);
		}
		else{
			printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", x);
		}
		//recalcula a altura de todos os nos ente a raiz e o novo no inserido
		raiz->altura = maior(alturaDoNode(raiz->esquerdo), alturaDoNode(raiz->direito)) +1;
		//verifica a necessidade de rebalancear a arvore
		raiz = balancear(raiz);
		
		return raiz;
	}
}
/*
funcao para remover um no da arvore pode ser
necessario rebalancear a arvore e a raiz pode ser
alterada por isso precisamos retornar a raiz 
*/
Node* remover(Node *raiz, int chave){
	if(raiz == NULL){
		printf("Valor nao encontrado!\n");
		return NULL;
	}
	else{ //procura o no a remover
		if(raiz->valor == chave){
			//remove nos folha(nos sem filhos)
			if(raiz->esquerdo == NULL && raiz->direito == NULL){
				free(raiz);
				printf("Elemento folha removido: %d !\n", chave);
				return NULL;
			}
			else{
				//remove nos que possuem 2 filhos
				if(raiz->esquerdo != NULL && raiz->direito != NULL){
					Node *aux = raiz->esquerdo;
					while(aux->direito != NULL){
						aux = aux->direito;
					}
					raiz->valor = aux->valor;
					aux->valor = chave;
					printf("Elemento trocado: %d !\n", chave);
					raiz->esquerdo = remover(raiz->esquerdo, chave);
					return raiz;
				}
				else{
					//remove nos que possuem apenas 1 filho
					Node *aux;
					if(raiz->esquerdo != NULL){
						aux = raiz->esquerdo;
					}
					else{
						aux = raiz->direito;
						free(raiz);
						printf("Elemento com 1 filho removido: %d !\n", chave);
						return aux;
					}
				}
			}
		}
		else{
			if(chave < raiz->valor){
				raiz->esquerdo = remover(raiz->esquerdo, chave);
			}
			else{
				raiz->direito = remover(raiz->direito, chave);
			}
		}
		//recalcula a altura de todos os nos ente a rais e o novo no inserico
		raiz->altura = maior(alturaDoNode(raiz->esquerdo), alturaDoNode(raiz->direito)) +1;
		//verifica a necessidade de balancear a arvore
		raiz = balancear(raiz);
		
		return raiz;
	}
}
//funcao para imprimir a arvore
void imprimir(Node *raiz, int nivel){
	int i;
	if(raiz){
		imprimir(raiz->direito, nivel +1);
		printf("\n\n");
		for (i = 0; i < nivel; i++){
			printf("\t");
		}
		printf("%d", raiz->valor);
		imprimir(raiz->esquerdo, nivel +1);
	}
}

int main (){
	int opcao, valor;
	Node *raiz = NULL;
	
	do{
		//printf("-----MENU DA ARVORE AVL-----");
		printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 0:
				printf("Saindo!!!");
				break;
			case 1:
				printf("Digite o valor a ser inserido: ");
				scanf("%d", &valor);
				raiz = inserir(raiz, valor);
				break;
			case 2:
				printf("Digite o valor a ser removido: ");
				scanf("%d", &valor);
				raiz = remover(raiz, valor);
				break;
			case 3:
				imprimir(raiz, 1);
				break;
			default:
				printf("\nOpcao invalida!!\n");
		}
	}while(opcao != 0);
	return 0;	
}
