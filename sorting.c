#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "vetor.h"

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
        for(a=valor_inicial;a<size_vector;a++)
        {
            if(vector_get(v,a) <  vector_get(v, min_value_index))min_value_index = a;

        }

        min_value = vector_get(v, min_value_index);
        vector_insert(v, vector_get(v,valor_inicial), min_value_index);
        vector_insert(v, min_value, valor_inicial);
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

        for(a=0;a<max_value -1 ;a++){
            if(vector_get(v, a + 1) < vector_get(v, a)){
                swap = 1;
                temp1 = vector_get(v,a+1);
                temp2 = vector_get(v,a);
                vector_insert(v,temp1,a);
                vector_insert(v,temp2,a+1);

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
        if (v->data[i] <= v->data[j])
        {
            u->data[k] = v->data[i];
            i++;
        }
        else
        {
            u->data[k] = v->data[j];
            j++;
        }
        k++;
    }

    // sobra da esquerda
    while (i <= mid)
    {
        u->data[k] = v->data[i];
        i++;
        k++;
    }

    // sobra da direita
    while (j <= right)
    {
        u->data[k] = v->data[j];
        j++;
        k++;
    }

    // copia de volta
    for (i = left; i <= right; i++)
    {
        v->data[i] = u->data[i];
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
    Vector *u = malloc(sizeof(Vector));
    u->size = tamanho;
    u->data = calloc(tamanho, sizeof(int));

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

    free(u->data);
    free(u);

}


//Funcao auxiliar ao heapsort
void heapify(Vector *v, int n, int i){

    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    //Se o filho esquerdo for maior que a raiz
    if (esq < n && v->data[esq] > v->data[maior]){
        maior = esq;
    }

    //Se o filho direito for maior que a raiz
    if (dir < n && v->data[dir] > v->data[maior]){
        maior = dir;
    }

    //Se o maior não for a raiz, faz a troca e continua descendo
    if (maior != i){
        int temp = v->data[i];
        v->data[i] = v->data[maior];
        v->data[maior] = temp;

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
        int temp = v->data[0];
        v->data[0] = v->data[i];
        v->data[i] = temp;

        heapify(v, i , 0);
    }

    return;
}


