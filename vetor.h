#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
    int *data;
    unsigned int size;
} Vector;


/*Define as Funções do Vetor*/
Vector *vector_create(unsigned int size);
void vector_push(Vector *v, int value);
int vector_get(Vector *v, unsigned i);
void vector_destroy(Vector *v);

#endif