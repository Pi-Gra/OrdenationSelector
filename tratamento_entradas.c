#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int *gerar_entradas_aleatorias(unsigned int tamanho){
    if (tamanho == 0){
        return NULL;
    }

    int *vetor = (int *) calloc(tamanho, sizeof(int));

    if(vetor == NULL){
        return NULL;
    }

    for(int i = 0; i < tamanho; i++){
        vetor[i] = rand();
        }

    return vetor;
}

int *gerar_entradas_ordenadas(unsigned int tamanho){
    if(tamanho == 0){
        return NULL;
    }

    int *vetor = (int *)calloc(tamanho, sizeof(int));

    if (vetor == NULL){
        return NULL;
    }

    for(int i = 0; i < tamanho; i++){
        vetor[i] = i;
    }

    return vetor;
}

int *gerar_entradas_inversas(unsigned int tamanho){
    if(tamanho == 0){
        return NULL;
    }

    int *vetor = (int *)calloc(tamanho, sizeof(int));

    if (vetor == NULL){
        return NULL;
    }

    for(int i = 0; i < tamanho; i++){
        vetor[i] = tamanho - 1 - i;
    }

    return vetor;
}
