#ifndef ANALISE_H
#define ANALISE_H

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

typedef struct {
    int tamanho;
    int amplitude;
    double desvio_padrao;
    double percentual_desordem;
    //1 -> quase ordenado (ou 100% inverso); 0 -> nao quase ordenado
    int quase_ordenado;
    //1 -> quase inverso (ou 100% inverso); 0 -> nao quase inverso
    int quase_inverso;
    int numero_duplicatas;
    double densidade_duplicatas;
}CaracteristicasEntrada;

double calcula_media(Vector *v);

int amplitude(Vector *v);
double desvio_padrao(Vector *v);
double percentual_desordem(Vector *v);
double percentual_ordenacao_inversa (Vector *v);
int numero_duplicatas(Vector *v);
double densidade_duplicatas(Vector *v);

CaracteristicasEntrada analisar_propriedades(Vector *v);

#endif