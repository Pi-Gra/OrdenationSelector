#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "vetor.h"

void selection_sort(Vector *v)
{

    if(v==NULL){
        printf("Erro ao ordenar o vetor, vetor não existe ou nulo");
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