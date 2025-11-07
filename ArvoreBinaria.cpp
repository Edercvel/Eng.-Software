#include <stdio.h>
#include <stdlib.h>

//Definição da estrutura Node, que representa um no da árvore binária
typedef struct node{
	int conteudo;
	struct node *esquerda, *direita;
}Node;

//Definição da estrutura ArvB, que representa a árvore binária (raiz e tamanho)
typedef struct{
	Node *raiz;// Ponteiro para a raiz da arvore
	int tam; // Tamanho da arvore (numero de nos) - nao usado no codigo atual
}ArvB;

//Protótipo da função inserirDireita para evitar erro de compilação quando chamada antes de ser definida
void inserirDireita(Node *node, int valor);

//Função para inserir um valor na árvore esquerda de um no
//Se o filho esquerdo for NULL, cria um novo no; caso contrário, insere recursivamente
void inserirEsquerda(Node *node, int valor){
	if(node->esquerda == NULL){
	//Aloca memoria para um novo no
	Node *novo = (Node*)malloc(sizeof(Node));
	novo->conteudo = valor;
	novo->direita = NULL;
	novo->esquerda = NULL;
	node->esquerda = novo;	
	}
	else{
		//Decide se insere na esquerda ou direita baseado no valor
		if(valor < node->esquerda->conteudo){
			inserirEsquerda(node->esquerda, valor);	
		}
		if(valor > node->esquerda->conteudo){
			inserirDireita(node->esquerda, valor);
		}			
	}	
}

//Função para inserir um valor na árvore direita de um no
//Similar a inserirEsquerda, mas para o lado direito
void inserirDireita(Node *node, int valor){
	if(node->direita == NULL){
	Node *novo = (Node*)malloc(sizeof(Node));
	novo->conteudo = valor;
	novo->direita = NULL;
	novo->esquerda = NULL;
	node->direita = novo;	
}
	else{
		//Decide se insere na direita ou esquerda baseado no valor
		if(valor > node->direita->conteudo){
			inserirDireita(node->direita, valor);	
		}
		if(valor < node->direita->conteudo){
			inserirEsquerda(node->direita, valor);
		}
	}	
}
//Função para inserir um valor na árvore (versão mais longa, não usada no principal)
//Verifica se a raiz é NULL e insere, ou chama as funções auxiliares
void inserir(ArvB *arv, int valor){
	if (arv ->raiz == NULL){
		//Cria a raiz se a árvore estiver vazia
		Node *novo = (Node*)malloc(sizeof(Node));
		novo->conteudo = valor;
		novo->direita = NULL;
		novo->esquerda = NULL;
		arv->raiz = novo;
	}else{
		//Insere na esquerda ou direita da raiz
		if(valor < arv->raiz->conteudo){
			inserirEsquerda(arv->raiz, valor);
		}
		if(valor > arv->raiz->conteudo){
			inserirDireita(arv->raiz, valor);
		}		
	}	
}
// Função recursiva para inserir um valor na árvore (versão curta e limpa)
//Retorna a raiz atualizada após a inserção
Node* inserirNovaVersao(Node *raiz, int valor){
	if(raiz == NULL){
		// Cria um novo no se a raiz for NULL
		Node *novo = (Node*)malloc(sizeof(Node));
		novo->conteudo = valor;
		novo->direita = NULL;
		novo->esquerda = NULL;
		return novo;
	}
	else{
		//Insere recursivamente na esquerda ou direita
		if (valor < raiz->conteudo){
			raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor);
		}
		if (valor > raiz->conteudo){
			raiz->direita = inserirNovaVersao(raiz->direita, valor);
		}
		return raiz;
	}
}
//Função para calcular o número de nós na árvore (tamanho)
//Retorna 0 se a raiz for NULL, senao 1 + tamanho das subárvores
int tamanho(Node *raiz){
	if (raiz == NULL){
		return 0;
	}
	else{
		return 1 + tamanho(raiz->esquerda) +  tamanho(raiz->direita);
	}
}
//Função para buscar um valor na árvore
//Retorna 1 se encontrado, -1 se não encontrado
int buscar(Node *raiz, int chave){
	if(raiz == NULL){
		return -1;
	}
	else {
		if(raiz->conteudo == chave){
			return 1;
		}
		if(chave < raiz->conteudo){
			return buscar(raiz->esquerda, chave);
		}
		else{
			return buscar(raiz->direita, chave);
		}
	}
}
//Função para imprimir a árvore em ordem (in-order traversal)
//Imprime os valores em ordem crescente
void imprimir(Node *raiz){
	if(raiz != NULL){
		imprimir(raiz->esquerda);
		printf ("%d ", raiz->conteudo);
		imprimir(raiz->direita);
		
	}	
}
//Função para remover um no da árvore
//Trata casos: folha, um filho, dois filhos (substitui pelo máximo da esquerda)
Node* remover(Node *raiz, int chave){
	if(raiz == NULL){
		printf ("Valor nao encontrado!\n");
		return NULL;
	}
	else{
		if(raiz->conteudo == chave){
			//Caso folha: remove diretamente
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				return NULL;
			}
			else{
				//Caso um filho: substitui pelo filho
				if(raiz->esquerda == NULL || raiz->direita == NULL){
					Node *aux;
					if(raiz->esquerda != NULL){
						aux = raiz->esquerda;
					}
					else{
						aux = raiz->direita;
					}
					free(raiz);
					return aux;
				}				
				else{
					//Caso dois filhos: encontra o máximo na esquerda e substitui
					Node *aux = raiz->esquerda;
					while(aux->direita != NULL){
						aux = aux->direita;
					}
					raiz->conteudo = aux->conteudo;
					aux->conteudo = chave;
					raiz->esquerda = remover(raiz->esquerda, chave);
					return raiz;	 
				}
			}	
		}
		else{
			//Busca recursivamente na esquerda ou direita
			if(chave < raiz->conteudo){
				raiz->esquerda = remover(raiz->esquerda, chave);
			}
			else{
				raiz->direita = remover(raiz->direita, chave);
				return raiz;
			}
		}
	}
}
//Função principal: menu interativo para operações na árvore
int main (){
	int op, valor;
	ArvB arv; // Declarada mas nao usada
	arv.raiz = NULL;
	
	Node *raiz = NULL;// Raiz da arvore usada no programa
	
	do{
		//Exibe o menu
		printf("\nMenu da Arvore Binaria\n");
		printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - buscar\n4 - remover\n");
		scanf("%d", &op);
		
		switch(op){
			case 0:
				//sai do menu 
				printf ("\nSaindo....\n");
				break;
			case 1: 
				//Insere um valor
				printf("Digite um valor: ");
				scanf("%d", &valor);
				raiz = inserirNovaVersao(raiz, valor);
			//	inserir(&arv, valor);
				break;
			case 2: 
				//Imprime a árvore e o tamanho
				printf("\nImpressao da Arvore Binaria:\n");
				imprimir(raiz);
				printf("\n");
				printf("Tamanho: %d\n", tamanho(raiz));
				break;
				case 3:
				//Busca um valor
				printf("Qual o valor deseja buscar?");
				scanf("%d", &valor);				
				printf("Resultado da busca: %d\n", buscar(raiz, valor));
				break;
			case 4:
				//Remove um valor
				printf ("Digite um valor a ser removido: \n");
				scanf("%d", &valor);
				raiz = remover(raiz, valor);
				break;										
			default:
				printf("\nOpcao invalida...\n");
	 	}
	}while (op != 0);
}
