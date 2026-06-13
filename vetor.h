#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
    int *data;
    unsigned int size;
    long long int trocas;
    long long int comparacoes;
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