#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector{
    int *data;
    unsigned int tamanho;
    long long int movimentacoes;
    long long int comparacoes;
    long long int profundidade_recursao;
    size_t memoria_alocada;
    size_t pico_memoria_algoritmo;
} Vector;



/*Define as Funções do Vetor*/
Vector *vector_create(unsigned int tamanho);
int vector_get(Vector *v, unsigned i);
void vector_insert(Vector *v,int value, unsigned i);
void vector_swap(Vector *v, unsigned i, unsigned j);
void print_vector(Vector *v);
Vector *vector_copy(Vector *v);
void vector_destroy(Vector *v);

#endif