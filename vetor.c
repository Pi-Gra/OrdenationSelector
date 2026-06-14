#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>

Vector *vector_create(unsigned int tamanho)
{
    Vector *v = malloc(sizeof(Vector));

    if(v == NULL)return NULL;

    v->size = tamanho;
    v->data = calloc(tamanho, sizeof(int));

    if(v->data == NULL){
        free(v);
        return NULL;
    }

    v->movimentacoes = 0;
    v->comparacoes = 0;
    v->profundidade_recursao = 0;

    v->memoria_alocada = sizeof(Vector) + (tamanho * sizeof(int));

    v->pico_memoria_algoritmo = 0;

    return v;
}

int vector_get(Vector *v, unsigned i)
{
    if (v == NULL || i >= v->size){
        printf("Erro: indice %u fora dos limites do vetor", i);
    }

     int valor = v->data[i];

     return valor;
}

void vector_insert(Vector *v, int value, unsigned i)
{
    if(v == NULL){
        printf("Falha ao inserir valor no vetor, vetor não existe");
        return;
    }
    
    if (i >= v->size){
        printf("Erro: tentativa de insercao no indice %u fora do limite do vetor", i);
    }

    v->data[i] = value;
}   

void vector_swap(Vector *v, unsigned i, unsigned j){
    if (v == NULL){
        printf("Vetor vazio, falha ao realizar a troca");
        return;
    }

    int temp = vector_get(v, i);
    vector_insert(v, v->data[j], i);
    vector_insert(v, temp, j);
    v->movimentacoes++;

}

void print_vector(Vector *v){
    if (v == NULL){
        printf("Não foi possível imprimir o vetor");
        return;
    }

    for (int i = 0; i < v->size; i++){
        printf("%d ", vector_get(v, i));
    }

}

Vector *vector_copy(Vector *v){
    if (v == NULL){
        return v;
    }
    
    int tamanho = v->size;

    Vector *u = vector_create(tamanho);
    if (u == NULL){
        printf("Erro ao criar a copia do vetor");
        return v;
    }else{
        for(int i = 0; i < tamanho; i++){
            vector_insert(u, vector_get(v, i), i);
        }
    }

    return u;
}

void vector_destroy(Vector *v)
{
    if(v == NULL)
    {
        printf("Falha ao destruir o vetor, vetor inexistente.");
        return;
    }

    free(v->data);
    free(v);
    
}

