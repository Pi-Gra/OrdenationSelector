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

    for (int i = 0; i < v->size; i++){
        soma_total += v->data[i];
    }

    double media = (double)soma_total/v->size;

    return media;
}

int amplitude(Vector *v){
    if (v == NULL){
        return -1;
    }

    int menor = v->data[0];
    int maior = v->data[0];

    for(int i = 1; i < v->size; i++){
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

    int n = v->size;

    double media = calcula_media(v);
    double soma_quadrados = 0;

    for(int i = 0; i < v->size; i++){
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

    for(int i = 0; i < (v->size - 1); i++){
        if(v->data[i] > v->data[i+1]){
            inversoes++;
        }
    }

    double percentual_desordem = ((double)inversoes/(v->size - 1)) * 100.0;

    return percentual_desordem;
}

int numero_duplicatas(Vector *v){
    if (v == NULL){
        return 0;
    }

    TabelaHash *tabela = criar_tabela(v->size);

    int valores_unicos = 0;

    for (int i = 0; i < v->size; i++){
        valores_unicos += inserir_hash(tabela, v->data[i]);
    }

    int total_valores_repetidos = v->size - valores_unicos;
    
    liberar_tabela(tabela);

    return total_valores_repetidos;
}

double densidade_duplicatas(Vector *v){
    if (v == NULL){
        return 0;
    }

    double densidade = (double)numero_duplicatas(v)/v->size;

    return densidade;
}

int numero_runs(Vector *v){
    if (v == NULL){
        return 0;
    }
    
    int runs = 1;

    for(int i = 0; i < v->size; i++){
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

    controle.tamanho = v->size;
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

        //condicao para vetores pequenos
        if(props.tamanho <= 1000){
            return 0; // --> Selection Sort
        }

        //condicao vetores quase ordenados
        if(props.quase_ordenado == 1){
            return 1; // --> Bubble Sort
        }
        
        //grau de desordem baixo, mas nao chega a ser considerado quase ordenado
        if(props.percentual_desordem <= 15.0){
            return 3; // --> Heap Sort
        }

        // vetor grande, totalmente bagunçado, mas os números não são astronomicamente gigantes
        if(props.tamanho > 5000 && props.amplitude > 0 && props.amplitude < (props.tamanho * 5)){
            return 4;
        }

        //caso base de seguranca: heap por nao consumir memoria ram extra igual o merge
        return 2;// --> Merge Sort
}
