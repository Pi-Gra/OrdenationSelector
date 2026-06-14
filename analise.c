#include <stdio.h>
#include <stdlib.h>
#include "analise.h"
#include "vetor.h"
#include <math.h>

//===================== estruturas e funcoes auxiliares da tabela hash =====================

typedef struct NoHash{
    int valor;
    int frequencia;
    struct NoHash *proximo;
}NoHash;

typedef struct {
    NoHash **gavetas;
    int tamanho;
}TabelaHash;

//funcao hash metodo divisao
static int funcao_hash(int chave, int tamanho_tabela){
    return abs(chave) % tamanho_tabela;
}

//inicializa a tabela e zera o vetor de ponteiros
static TabelaHash *criar_tabela(int tamanho){
    TabelaHash *tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho;
    tabela->gavetas = (NoHash**)calloc(tamanho, sizeof(NoHash*));
    return tabela;
}


//insere na lista e atualiza a frequencia de um elemento
//retorna 1 se o elemento for unico e 0 se há repeticao (duplicata)
static int inserir_hash(TabelaHash *tabela, int valor){
    int indice = funcao_hash(valor, tabela->tamanho);
    NoHash* atual = tabela->gavetas[indice];

    while (atual != NULL){
        if(atual->valor == valor){
            atual->frequencia++;
            return 0;
        }
        atual = atual->proximo;
    }

    NoHash *novo = (NoHash*)malloc(sizeof(NoHash));
    novo->valor = valor;
    novo->frequencia = 1;
    novo->proximo = tabela->gavetas[indice];
    tabela->gavetas[indice] = novo;

    return 1;
}

//libera a memoria alocada para a tabela hash
static void liberar_tabela(TabelaHash *tabela){
    for(int i = 0; i < tabela->tamanho; i++){
        NoHash *atual = tabela->gavetas[i];
        while(atual != NULL){
            NoHash *aux = atual;
            atual = atual->proximo;
            free(aux);
        }
    }
    free(tabela->gavetas);
    free(tabela);
}


// ============================= funcoes de metricas =========================

double calcula_media(Vector *v){
    if (v == NULL){
        return -1.0;
    }

    long long int soma_total = 0;

    for (int i = 0; i < v->tamanho; i++){
        soma_total += v->data[i];
    }

    double media = (double)soma_total/v->tamanho;

    return media;
}

int amplitude(Vector *v){
    if (v == NULL){
        return -1;
    }

    int menor = v->data[0];
    int maior = v->data[0];

    for(int i = 1; i < v->tamanho; i++){
        if(v->data[i] > maior){
            maior = v->data[i];
        }
        if(v->data[i] < menor){
            menor = v->data[i];
        }
    }

    return maior - menor;
}

double desvio_padrao(Vector *v){
    if(v == NULL){
        return 0.0;
    }

    int n = v->tamanho;

    double media = calcula_media(v);
    double soma_quadrados = 0;

    for(int i = 0; i < v->tamanho; i++){
        double diferenca = v->data[i] - media;
        soma_quadrados += diferenca*diferenca;
    }

    double desvio_padrao = sqrt(soma_quadrados/(n-1));
    
    return desvio_padrao;
}

//ideia: contar quantas vezes v[i] > v[i+1] (inversao)
double percentual_desordem(Vector *v){
    if (v == NULL){
        return -1.0;
    }

    int inversoes = 0;

    for(int i = 0; i < (v->tamanho - 1); i++){
        if(v->data[i] > v->data[i+1]){
            inversoes++;
        }
    }

    double percentual_desordem = ((double)inversoes/(v->tamanho - 1)) * 100.0;

    return percentual_desordem;
}

int numero_duplicatas(Vector *v){
    if (v == NULL){
        return 0;
    }

    TabelaHash *tabela = criar_tabela(v->tamanho);

    int valores_unicos = 0;

    for (int i = 0; i < v->tamanho; i++){
        valores_unicos += inserir_hash(tabela, v->data[i]);
    }

    int total_valores_repetidos = v->tamanho - valores_unicos;
    
    liberar_tabela(tabela);

    return total_valores_repetidos;
}

double densidade_duplicatas(Vector *v){
    if (v == NULL){
        return 0;
    }

    double densidade = (double)numero_duplicatas(v)/v->tamanho;

    return densidade;
}

int numero_runs(Vector *v){
    if (v == NULL){
        return 0;
    }
    
    int runs = 1;

    for(int i = 0; i < v->tamanho; i++){
        if(v->data[i] < v->data[i-1]){
            runs++;
        }
    }

    return runs;
}


CaracteristicasEntrada analisar_propriedades(Vector *v){
    CaracteristicasEntrada controle = {0};

    if (v == NULL){
        return controle;
    }

    controle.tamanho = v->tamanho;
    controle.amplitude = amplitude(v);
    controle.percentual_desordem = percentual_desordem(v);

    if(controle.percentual_desordem <= 5.0){
        controle.quase_ordenado = 1;
    }else{
        controle.quase_ordenado = 0;
    }

    if(controle.percentual_desordem >= 95.0){
        controle.quase_inverso = 1;
    }else{
        controle.quase_inverso = 0;
    }

    controle.numero_duplicatas = numero_duplicatas(v);
    controle.densidade_duplicatas = densidade_duplicatas(v);
    controle.runs = numero_runs(v);

    printf("=============== Caracteristicas do vetor: ==============\n");
        printf("Tamanho: %d\n", controle.tamanho);
        printf("Amplitude: %d\n", controle.amplitude);
        printf("Desvio Padrao: %.2f%%\n", controle.desvio_padrao);
        printf("Percentual de Desordem: %.2f%%\n", controle.percentual_desordem);
        printf("Quase Ordenado: %s\n", controle.quase_ordenado ? "Sim" : "Nao");
        printf("Quase Inverso: %s\n", controle.quase_inverso ? "Sim" : "Nao");
        printf("Numero de Duplicatas: %d\n", controle.numero_duplicatas);
        printf("Densidade de Duplicatas: %.2f%%\n", controle.densidade_duplicatas * 100);
        printf("Numero de runs: %d", controle.runs = numero_runs(v));

    return controle;
}

int arvore_decisao(CaracteristicasEntrada props){

    // 1. PRIORIDADE MÁXIMA: Vetores lineares ou quase prontos
    // O Bubble Sort Aprimorado faz apenas N-1 comparações se o vetor estiver ordenado.
    if (props.quase_ordenado == 1) {
        return 1; // Case 1: Bubble Sort
    }

    if (props.tamanho <= 1000) {
        return 0; // Case 0: Selection Sort
    }

    if (props.quase_inverso == 1) {
        return 3; // Case 3: Heap Sort
    }

    if (props.densidade_duplicatas >= 0.70) {
        return 3; // Case 3: Heap Sort
    }

    if (props.percentual_desordem <= 15.0) {
        return 2; // Case 2: Merge Sort
    }

    if (props.tamanho > 5000 && props.amplitude > 0 && props.amplitude < (props.tamanho * 5)) {
        return 4; // Case 4: Radix Sort LSD
    }

    return 2; // Case 2: Merge Sort
}

