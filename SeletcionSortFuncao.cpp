#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale.h>
#include <iostream>

void imprimeVetor(int vetor[]){
	int x;
	printf("\n");
	for (int x=0; x<5; x++){
		printf ("| %d |",vetor[x]);
}
}
void selectionSort(int vetor[5]){
	int i, j; //variaveis de controle para os loops
	int aux; //variavel usado para armazenar temporariamente um valor durante a troca dos valores
	int numeroMinimo=0; // variavel usada para armazenar o indice de menor valor encontrado durante a interaçao
	int contComparador=0; //variavel usada para contar quantas compracoes foram feitas
	int contTroca=0; //variavel usada para contar quantas trocas foram feitas
	
	//loop externo, esse loop percorre cada elemento do vetor, começando do indice 0 ate 4 (5 elementos)
	for (i = 0; i< 5 ; i++){ 
		numeroMinimo = i;  // inicialmente assumimos que o menor valor esta na posiçao atual 'i'.
		imprimeVetor(vetor);
		//loop interno, este loop começa a partir da proxima posiçao de i (ou seja, i +1) e vai ate o final do vetor.
		for (j = i+1; j < 5; j++){ 
			
			//condiçao 'if' verifica se o valor atual 'vetor[j]' é menor que o valor 'vetor[numeroMinimo]'. Se for, atualiza o 'numeroMinimo' para indice 'j'
			if (vetor[j]<vetor[numeroMinimo]){  
				numeroMinimo = j;
				contComparador ++;	
			}
		}
		
		//'if' verifica se o valor atual'vetor[i]' é diferente do menor encontrado 'vetor[numeroMinimo]'. Se forem diferentes, realiza a troca dos valores 
		//usando a variavel 'aux' para armazenar temporariamente o valor de vetor[i].
		if(vetor[i] != vetor[numeroMinimo]){ 		
			int aux = vetor[i];
				vetor[i] = vetor[numeroMinimo];
				vetor[numeroMinimo] = aux;
				contTroca ++;
		}
			
	}
	printf ("\nForam feitas %d compracoes", contComparador);
	printf ("\nForam feitas %d trocas", contTroca);
}

//O algoritmo abaixo é um metodo de ordenaçao por seleçao (selection sort), que funciona encontrando repetidamente o menor da parte nao
//ordenada do vetor e trocando-o com o primeiro elemento nao ordenado. Apos a execuçao, o vetor é impresso em ordem crescente e, em
//seguida, em ordem decrescente.

int main (){
	int vetor[]={3, 4, 5, 1, 2}; //declaraçao de vetores
	selectionSort(vetor);
	imprimeVetor(vetor);
	return 0;
}
