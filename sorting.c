#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "vetor.h"

const char *nome_algoritmo(int algoritmo){
    switch(algoritmo){
        case 0: return "Selection Sort"; break;
        case 1: return "Bubble Sort"; break;
        case 2: return "Merge Sort"; break;
        case 3: return "Heap Sort"; break;
        default: return "Desconhecido"; break;
    }
}

void selection_sort(Vector *v)
{

    if(v==NULL){
        printf("Erro ao ordenar o vetor. Vetor não existe ou é inválido");
        return;
    }

    int i,a;

    int valor_inicial = 0;
    int min_value,min_value_index;
    unsigned int size_vector = v->size;

    for(i=0;i<size_vector;i++){
        
        min_value_index = valor_inicial;
        
        for(a= valor_inicial + 1; a<size_vector; a++)
        {
            v->comparacoes++;

            if(vector_get(v,a) <  vector_get(v, min_value_index))min_value_index = a;

        }
        
        if(min_value_index != valor_inicial){

            vector_swap(v, min_value_index, valor_inicial);
        }

        valor_inicial++;
    }

}

void bubble_sort(Vector *v)
{
    
    if(v == NULL){
        printf("Erro ao ordenar o vetor. Vetor não existe ou é inválido");
        return;
    }

    int size_vector = v->size;
    int max_value = size_vector;
    int i,a,temp1,temp2;

    for(i=0;i<size_vector;i++){

        int swap = 0;

        for(a=0; a<max_value -1; a++){

            v->comparacoes++;

            if(vector_get(v, a + 1) < vector_get(v, a)){
                swap = 1;
                vector_swap(v, a, a+1);
            }
        }

        if(swap == 0)break;
        max_value--;
    }
}

void merge(Vector *v, Vector *u, int left, int mid, int right)
{
    int i = left;       // esquerda
    int j = mid + 1;    // direita
    int k = left;       // auxiliar

    // enquanto tiver elementos nos dois lados
    while (i <= mid && j <= right)
    {
        v->comparacoes++;

        if (vector_get(v, i) <= vector_get(v, j))
        {
           vector_insert(u, vector_get(v,i), k);
           v->trocas++;
            i++;
        }
        else
        {
            vector_insert(u, vector_get(v, j), k);
            v->trocas++;
            j++;
        }
        k++;
    }

    // sobra da esquerda
    while (i <= mid)
    {
        vector_insert(u, vector_get(v, i), k);
        v->trocas++;
        i++;
        k++;
    }

    // sobra da direita
    while (j <= right)
    {
        vector_insert(u, vector_get(v, j), k);
        v->trocas++;
        j++;
        k++;
    }

    // copia de volta
    for (i = left; i <= right; i++)
    {
        vector_insert(v, vector_get(u, i), i);
        v->trocas++;
    }
}

void merge_sort(Vector *v)
{

    if(v == NULL)
    {
        printf("Não foi possivel ordenar o vetor. Vetor não existe ou é inválido.");
        return;
    }

    int tamanho = v->size;

    //vetor auxiliar
    Vector *u = vector_create(tamanho);

    for(int size = 1; size <tamanho; size *= 2)
    {
        for(int left = 0;left<tamanho -1; left += 2* size)
        {
            int mid = left + size - 1;
            int right = left + 2*size - 1;

            if (mid >= tamanho)continue;

            if (right >= tamanho)right = tamanho -1;

            merge(v,u,left,mid,right);

        }
  
    }

    vector_destroy(u);
}


//Funcao auxiliar ao heapsort
void heapify(Vector *v, int n, int i){

    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    //Se o filho esquerdo for maior que a raiz
    if (esq < n){
        v->comparacoes++;
        if(vector_get(v, esq) > vector_get(v, maior)){
           maior = esq;
       }

    }

    //Se o filho direito for maior que a raiz
    if (dir < n){
        v->comparacoes++;
        if (vector_get(v, dir) > vector_get(v, maior)){
            maior = dir;
        }

    }

    //Se o maior não for a raiz, faz a troca e continua descendo
    if (maior != i){
        vector_swap(v, i, maior);
        heapify(v, n, maior);
    }

    return;
}

void heap_sort(Vector *v){

    if (v == NULL){ 
        printf("Não foi possível ordenar o vetor. Vetor não existe ou é inválido");
        return; 
    }

    int n = v->size;
    
    for (int i = (n/2)-1; i >= 0; i--){
        heapify(v, n, i);
    }

    for(int i = n-1; i > 0; i--){
        vector_swap(v, i, 0);

        heapify(v, i , 0);
    }

    return;
}


