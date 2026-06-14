#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tratamento_entradas.h"
#define MAX_ELEMENTOS 10000000


int *gerar_entradas_aleatorias(unsigned int tamanho){
    if (tamanho == 0){
        return NULL;
    }

    int *vetor = (int *) calloc(tamanho, sizeof(int));

    if(vetor == NULL){
        return NULL;
    }

    for(int i = 0; i < tamanho; i++){
        vetor[i] = ((rand()<< 9) | rand() & 0x3FFFFFFF);
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

int tamanho_arquivo(const char *nome_arquivo) {
    FILE *arq;
    char line[100];
    unsigned int tamanho;

    arq=fopen(nome_arquivo,"rt");
    if (arq == NULL) {
        printf("# Error: Can not open the file");
        exit(1);
    }

    while(fgets(line, 100, arq) != NULL) {
        //while para pular as linhas de explicação do arquivo
        if (line[0] == '#') {
            break;
        }
    }
    fscanf(arq, "%u", &tamanho);
    fclose(arq);
    tamanho = (int)tamanho;
    return tamanho;
}


int *leitura_arquivos(const char *nome_arquivo, int tamanho) {
    FILE *arq;
    char line[100];
    int num;
    unsigned int indice = 0;


    arq=fopen(nome_arquivo,"rt");
    if (arq == NULL) {
        printf("# Error: Can not open the file");
        exit(1);
    }

    while(fgets(line, 100, arq) != NULL) {
        //while para pular as linhas de explicação do arquivo
        if (line[0] == '#') {
            break;
        }
    }
    fscanf(arq, "%d", &num);
    
    int *vetor = (int *) calloc(tamanho, sizeof(int));

    if (vetor == NULL){
        fclose(arq);
        return NULL;
    }

    while(indice<tamanho && (fscanf(arq, "%d", &num) == 1)) {
        vetor[indice] = (int)num;
        indice++;
    }

    fclose(arq);

    return vetor;
}
