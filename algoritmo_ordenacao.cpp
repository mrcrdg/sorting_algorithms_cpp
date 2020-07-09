#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void funcoes(int*lido, int*numeros,int*tam,bool leu);
void ler(int * tam);
void teste(int*numeros);

int* ler_arquivo(char *nome, int *tam) {	
    FILE *arquivo;
	const char s[2] = ",";
    char *token;
    char linha[256];
    char *result;
    int i=0,tamPadrao=5;
    int*numeros=(int *) malloc(tamPadrao * sizeof(int));	

    arquivo = fopen(nome,"r");

    if (arquivo == NULL)
    {
        printf ("Erro ao abir o arquivo!!\n");
        fclose(arquivo);
		ler(tam);		
    }
   
    while (!feof(arquivo))
   {
      result = fgets(linha, 256, arquivo);

      if (result)
          token = strtok(result, s);
          
      while( token != NULL )
      {
      	if (i >= tamPadrao) {
			tamPadrao *=2;
			numeros = (int*) realloc(numeros, tamPadrao * sizeof(int));
		}
		
        sscanf(token, "%d", &numeros[i]); 
        i++;
        token = strtok(NULL, s);
      }
  }
  
    numeros = (int*) realloc(numeros, tamPadrao * sizeof(int));
    *tam=i;
    fclose(arquivo);
    return numeros;
}

void escrever(int * numeros, int * tam){
	FILE * arq1;
	int i;
	
	arq1=fopen("Resultado.txt", "w+");
	if(arq1 == NULL){
		printf("Erro ao abir o arquivo!!\n");
		fclose(arq1);
		return;
	}else{
		for(i=0;i<*tam;i++){
			fprintf(arq1, "%i", numeros[i]);
			fprintf(arq1, "%s", ", ");

		}
	}
	fclose(arq1);
}

void bubble_sort (int * vetor, int *n) {
    int k, j, aux;
	
    for (k = 0; k < *n - 1; k++) {

        for (j = 0; j < *n - k - 1; j++) {

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    } 
}

void insertionSort(int * arr, int *n) { 
    int i, key, j; 
    for (i = 1; i < *n; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
       
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
	}
}

void selection (int *v, int *n) {
   for (int i = 0; i < *n-1; ++i) {
      int min = i;
      for (int j = i+1; j < *n; ++j)
         if (v[j] < v[min])  min = j;
      int x = v[i]; v[i] = v[min]; v[min] = x;
   }
}

int particiona(int *V, int inicio, int final){
	int esq, dir, pivo, aux;
	esq = inicio;
	dir = final;
	pivo = V[inicio];
	
	while(esq<dir){
		while(esq <= final && V[esq] <= pivo) esq++;
		while(dir >= 0 && V[dir] > pivo) dir--;
		if(esq<dir){
			aux = V[esq];
			V[esq] = V[dir];
			V[dir] = aux;
		}
	}
	V[inicio] = V[dir];
	V[dir] = pivo;
	return dir;
}

void quick_sort (int *V, int inicio, int fim) {
    int pivo;
	if(fim>inicio){
		pivo = particiona(V,inicio, fim);
		quick_sort(V,inicio, pivo-1);
		quick_sort(V, pivo+1, fim);
	}
}


void mergeSort(int *vetor, int posicaoInicio, int posicaoFim) {	
    int i, j, k, metadeTamanho, *vetorTemp;
    if(posicaoInicio == posicaoFim) return ;
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
 
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);
 
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));
 
    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { 
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }
        else {
            if (j == posicaoFim + 1) {
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
            else {
                if (vetor[i] < vetor[j]) {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                else {
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }
    }
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    
    free(vetorTemp);
}


void sair(int*numeros,int*tam,bool leu){
	system("cls");
	
	int i;
	printf("Deseja mesmo sair?\n\n1- Sim.\n2- Nao\n\n");
	scanf("%i",&i);
	
	
	switch(i){
		case 1:{
			exit(0);
			break;
		}
		case 2:{
			funcoes(numeros,numeros,tam,leu);
			break;
		}default:{
			printf("Nao encontrado.\n");
			system("pause");
			sair(numeros,tam,leu);
		}
	}
}

void ler(int * tam){
	char nome[30];
	*tam=5;
	int* result =(int *) malloc(*tam * sizeof(int)); 
	
	system("cls");
	printf("Digite o nome do arquivo: ");
	fflush(stdin);
	gets(nome);
	
	result=ler_arquivo(nome, tam);
	result =(int *) realloc(result, *tam * sizeof(int));
	result=ler_arquivo(nome, tam);
	funcoes(result, result, tam,true);
	
}
void teste(int*numeros,int * tam){
	int i;
	printf("\n\n");
	
	for(i=0;i<*tam;i++){
		printf("%i\t", numeros[i]);
	}
	
	printf("\n");
	system("pause");
}

void leu(bool leu,int*lido, int*numeros,int*tam){
	if(!leu){
		printf("\n\nEntre com um arquivo antes de continuar.\n\n");
		system("pause");
		funcoes(lido, numeros, tam,leu);
	}
}

void funcoes(int*lido, int*numeros,int*tam,bool possuiArq){
	int i;
	system("cls");
	clock_t t;
	char *tipo;
	
	printf("Escolha entre as opcoes:\n\n1- Entrar com arquivo.\n2- Bubble Sort.\n3- Insertion Sort.\n4- Selection Sort.\n5- Quick Sort.\n6- Merge Sort.\n7- Sair.\n8- Reler arquivo.\n\n");
	scanf("%i",&i);
	
	switch(i){
		case 1:{
			ler(tam);
			break;
		}
		case 2:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;
			t = clock();
 			bubble_sort (numeros, tam);
 			t = clock() - t;
			tipo="Bubble Sort";
			escrever(numeros,tam);
			break;
		}case 3:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;
			t = clock();
			insertionSort(numeros,tam);
			t = clock() - t;
			tipo="Insertion Sort";
			escrever(numeros,tam);
			break;
		}case 4:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;
			t = clock();
			selection(numeros,tam);
			t = clock() - t;
			tipo="Selection Sort";
			escrever(numeros,tam);
			break;
		}case 5:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;
			int size=*tam-1;
			t = clock();
			quick_sort(numeros,0,size);
			t = clock() - t;
			tipo="Quick Sort";
			escrever(numeros,tam);
			break;
		}case 6:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;
			int size=*tam-1;
			t = clock();
			mergeSort(numeros,0,size);
			t = clock() - t;
			tipo="Merge Sort";
			escrever(numeros,tam);
			break;
		}case 7:{
			sair(numeros,tam, possuiArq);			
			break;
		}case 8:{
			leu(possuiArq,lido, numeros, tam);
			numeros=lido;			
			break;
		}case 9:{
			leu(possuiArq,lido, numeros, tam);
			teste(numeros,tam);			
			break;
		}default:{
			printf("Nao encontrado.\n");
			system("pause");
		}
	}
	
		printf("Resultado: %s - %f segundos.\n",tipo, ((double)t/ CLOCKS_PER_SEC));
		system("pause");	
	
	funcoes(lido, numeros,tam, possuiArq);
}


int main(int argc, char** argv) {
	int*numeros=(int *) malloc(sizeof(int));
	int*tam=(int*)malloc(sizeof(int));
	int i;
	funcoes(numeros,numeros,tam,false);
	return 0;
}
