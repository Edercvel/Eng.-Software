#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

 
 /* Inser��o em uma FILA
 	foi assistido aula 235, 236
 	FIFO - First-In, First-Out - Primeiro a Entrar, Primeiro a Sair 
 */
 
 //Defini��o do n� da fila
 typedef struct Node{
 	int valor;   //Valor inteiro armazenado no n�  
 	struct Node *proximo; //ponteiro para o n�
 }Node;
	
	//fun��o para inserir na fila (enqueue) - sempre no final		
 void inserir_na_fila (Node **fila, int num){ //void pq nao tem retorno, nome da fun��o, nos receberemos ponteiro para ponteiro, e o elemento que quero inserir 
 	Node *novo = (Node*)malloc(sizeof(Node)); //alocar mem�ria para novo N�
 	
	 if (novo){ //verifica se a aloca��o foi bem sucedida
 		novo->valor = num; //Define o valor do novo n�
 		novo->proximo = NULL;// o proximo � NULL pois ser� o ultimo
 		
 		if (*fila == NULL){	//se a fila estiver vazia
			*fila = novo; //o novo n� � o primeiro
		 }
 		
 		else{//caso contrario, percorre ate o final
 			Node *aux = *fila; //Aulixiar aponta para inicio
 			while (aux->proximo){ //Loop para percorer ate o ultimo n� 
				aux = aux->proximo; // eu estou fazendo esse ponteiro ir sempre para o proximo ponteiro, ate aux ser o ultimo.
 			}
 			aux->proximo = novo; //insere o novo n� no final.
 		}
	 }
	 else{ //caso o if seja falso, vou acrescentar um else
	 	printf ("\nErro ao alocar memoria.\n");
	 }
 }
 
 // Fun��o para remover da fila (dequeue) - sempre do in�cio
int remover_da_fila(Node **fila) {
    if (*fila == NULL) { // Verifica se a fila est� vazia
        printf("\nFila vazia!\n");
        return -1; // Valor de erro
    }
    Node *temp = *fila;      // Salva o n� a ser removido
    int valor_removido = temp->valor; // Pega o valor
    *fila = temp->proximo;   // Atualiza o in�cio da fila
    free(temp);              // Libera a mem�ria
    return valor_removido;
}

// Fun��o para imprimir a fila (para visualiza��o e testes)
//recebe um ponteiro para o inicio da fila (n�o modifica a fila)
void imprimir_fila(Node *fila) {
	// condi��o verifica se a fila esta vazia(ponteiro NULL indica fila vazia)
    if (fila == NULL) {  
        printf("Fila vazia.\n"); //imprime msg de fila vazia
        return; //sai da fun�ao
    }
	//Inicializa um ponteiro auxiliar para percorrer a fila sem modificar o original
    Node *aux = fila;
    printf("Fila: ");// Imprime o cabe�alho da sa�da
    
    // Loop para percorrer todos os n�s da fila
    while (aux != NULL) {
        printf("%d ", aux->valor);// Imprime o valor do n� atual
        aux = aux->proximo; // Move o auxiliar para o pr�ximo n�
    }
    printf("\n");// Quebra de linha ap�s imprimir todos os elementos
}
int main (){
	Node *fila = NULL; //inicializa a fila vazia
	
	// Testes de inser��o
    inserir_na_fila(&fila, 10);
    inserir_na_fila(&fila, 20);
    inserir_na_fila(&fila, 30);
    imprimir_fila(fila); // Deve imprimir: 10 20 30
    
    // Testes de remo��o
    printf("Removido: %d\n", remover_da_fila(&fila));
    imprimir_fila(fila); // Deve imprimir: 20 30
	return 0;
}
