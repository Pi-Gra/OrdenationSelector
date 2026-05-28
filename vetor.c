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


    return v;

}

int vector_get(Vector *v, unsigned i)
{
     int valor = v->data[i];

     return valor;
}

void vector_insert(Vector *v, int value, unsigned i)
{
    if(v == NULL){
        printf("Falha ao inserir valor no vetor, vetor não existe");
        return;
    }

    v->data[i] = value;

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

