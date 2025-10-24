#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

 
 /* Inserção em uma FILA
 	foi assistido aula 235, 236
 	FIFO - First-In, First-Out - Primeiro a Entrar, Primeiro a Sair 
 */
 
 //Definição do nó da fila
 typedef struct Node{
 	int valor;   //Valor inteiro armazenado no nó  
 	struct Node *proximo; //ponteiro para o nó
 }Node;
	
	//função para inserir na fila (enqueue) - sempre no final		
 void inserir_na_fila (Node **fila, int num){ //void pq nao tem retorno, nome da função, nos receberemos ponteiro para ponteiro, e o elemento que quero inserir 
 	Node *novo = (Node*)malloc(sizeof(Node)); //alocar memória para novo Nó
 	
	 if (novo){ //verifica se a alocação foi bem sucedida
 		novo->valor = num; //Define o valor do novo nó
 		novo->proximo = NULL;// o proximo é NULL pois será o ultimo
 		
 		if (*fila == NULL){	//se a fila estiver vazia
			*fila = novo; //o novo nó é o primeiro
		 }
 		
 		else{//caso contrario, percorre ate o final
 			Node *aux = *fila; //Aulixiar aponta para inicio
 			while (aux->proximo){ //Loop para percorer ate o ultimo nó 
				aux = aux->proximo; // eu estou fazendo esse ponteiro ir sempre para o proximo ponteiro, ate aux ser o ultimo.
 			}
 			aux->proximo = novo; //insere o novo nó no final.
 		}
	 }
	 else{ //caso o if seja falso, vou acrescentar um else
	 	printf ("\nErro ao alocar memoria.\n");
	 }
 }
 
 // Função para remover da fila (dequeue) - sempre do início
int remover_da_fila(Node **fila) {
    if (*fila == NULL) { // Verifica se a fila está vazia
        printf("\nFila vazia!\n");
        return -1; // Valor de erro
    }
    Node *temp = *fila;      // Salva o nó a ser removido
    int valor_removido = temp->valor; // Pega o valor
    *fila = temp->proximo;   // Atualiza o início da fila
    free(temp);              // Libera a memória
    return valor_removido;
}

// Função para imprimir a fila (para visualização e testes)
//recebe um ponteiro para o inicio da fila (não modifica a fila)
void imprimir_fila(Node *fila) {
	// condição verifica se a fila esta vazia(ponteiro NULL indica fila vazia)
    if (fila == NULL) {  
        printf("Fila vazia.\n"); //imprime msg de fila vazia
        return; //sai da funçao
    }
	//Inicializa um ponteiro auxiliar para percorrer a fila sem modificar o original
    Node *aux = fila;
    printf("Fila: ");// Imprime o cabeçalho da saída
    
    // Loop para percorrer todos os nós da fila
    while (aux != NULL) {
        printf("%d ", aux->valor);// Imprime o valor do nó atual
        aux = aux->proximo; // Move o auxiliar para o próximo nó
    }
    printf("\n");// Quebra de linha após imprimir todos os elementos
}
int main (){
	Node *fila = NULL; //inicializa a fila vazia
	
	// Testes de inserção
    inserir_na_fila(&fila, 10);
    inserir_na_fila(&fila, 20);
    inserir_na_fila(&fila, 30);
    imprimir_fila(fila); // Deve imprimir: 10 20 30
    
    // Testes de remoção
    printf("Removido: %d\n", remover_da_fila(&fila));
    imprimir_fila(fila); // Deve imprimir: 20 30
	return 0;
}
