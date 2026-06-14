#include <stdio.h>
#include <stdlib.h>
#include "analise.h"
#include "vetor.h"
#include <math.h>

//===================== estruturas e funcoes auxiliares da tabela hash utilizada para contar duplicatas =====================

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


//contar quantas vezes v[i] > v[i+1] (inversao)
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


double percentual_desordem(Vector *v){
    if (v == NULL){
        return -1.0;
    }

    int runs = numero_runs(v);

    double percentual_desordem = ((double)(runs - 1)/(v->tamanho - 1)) * 100.0;

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
        printf("Numero de runs: %d\n", controle.runs = numero_runs(v));
        printf("Percentual de Desordem: %.2f%%\n", controle.percentual_desordem);
        printf("Quase Ordenado: %s\n", controle.quase_ordenado ? "Sim" : "Nao");
        printf("Quase Inverso: %s\n", controle.quase_inverso ? "Sim" : "Nao");
        printf("Numero de Duplicatas: %d\n", controle.numero_duplicatas);
        printf("Densidade de Duplicatas: %.2f%%\n", controle.densidade_duplicatas * 100);

    return controle;
}

int arvore_decisao(CaracteristicasEntrada props){
    // Vetores muito pequenos
    if (props.tamanho <= 30)
        return 0;

    // Vetores quase ordenados
    if (props.quase_ordenado)
        return 1;

    // Cenário extremamente favorável ao Radix
    if (props.tamanho >= 5000 &&
        props.amplitude > 0 &&
        props.amplitude < props.tamanho * 5)
    {
        return 4;
    }

    // Muitas duplicatas + baixa amplitude
    if (props.densidade_duplicatas >= 0.80 &&
        props.amplitude < props.tamanho * 10)
    {
        return 4;
    }

    // Vetor muito bagunçado
    if (props.runs > props.tamanho * 0.45 &&
        props.percentual_desordem > 40.0)
    {
        return 3;
    }

    // Vetor quase inverso
    if (props.quase_inverso)
    {
        return 2;
    }

    // Vetor com poucas runs
    if (props.runs < props.tamanho * 0.15)
    {
        return 2;
    }

    // estratégia de fallback
    return 2;
}

