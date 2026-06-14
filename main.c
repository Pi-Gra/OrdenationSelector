#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "analise.h"
#include "sorting.h"
#include "tempo.h"
#include "tratamento_entradas.h"
#include <time.h>

#define ALGORITMO_PADRAO 3
#define DEBUG 0


int main(int argc,char *argv[])
{
    srand(time(NULL));

    if (argc < 2) {
        printf("modos de uso disponiveis:\n");
        printf("  1. arquivo:  %s <algoritmo|adaptativo> <arquivo.txt>\n", argv[0]);
        printf("  2. linha de comando:  %s <algoritmo|adaptativo> -vetor <num1> <num2> ... <numN>\n", argv[0]);
        printf("  3. linha de comando:  %s <algoritmo|adaptativo> -aleatorio/-ordenado/-inverso -tamanho X(inteiro)", argv[0]);
        return 0;
        }

    int tamanho = 0;
    int adaptativo = 0;
    int algoritmo = ALGORITMO_PADRAO; //0 = Selection Sort, 1 = Bubble Sort, 2  = Merge Sort (default), 3 = HeapSort, 4 = Radix
    int gerar_aleatorio = 0;
    int gerar_ordenado = 0;
    int gerar_inverso = 0;
    char *nome_arquivo = NULL;

    int indice_inicio_vetor_cmd = 0; //guarda o indice do argv[] em que o vetor se inicia (caso tenha)


    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-tamanho") == 0 && i + 1 < argc){
            tamanho = atoi(argv[i+1]);
            i++;
        }
        else if (strcmp(argv[i], "-vetor") == 0){
            indice_inicio_vetor_cmd = i + 1;
            tamanho = argc - indice_inicio_vetor_cmd;
            break;
        }
        else if (strcmp(argv[i], "-aleatorio") == 0){gerar_aleatorio = 1;}
        else if (strcmp(argv[i], "-ordenado") == 0){gerar_ordenado = 1;}
        else if (strcmp(argv[i], "-inverso") == 0){gerar_inverso = 1;}
        else if (strcmp(argv[i], "adaptativo") == 0) {adaptativo = 1;}
        else if (strcmp(argv[i], "selection") == 0) {algoritmo = 0;}
        else if (strcmp(argv[i], "bubble") == 0) {algoritmo = 1;}
        else if (strcmp(argv[i], "merge") == 0) {algoritmo = 2;}
        else if (strcmp(argv[i], "heap") == 0) {algoritmo = 3;}
        else if (strcmp(argv[i], "radix") == 0){algoritmo = 4;}
        else if (strstr(argv[i], ".txt") != NULL) {nome_arquivo = argv[i];}
    }
    int quantidade_modos = gerar_aleatorio + gerar_ordenado + gerar_inverso;
    if(quantidade_modos > 1){
        printf("Erro: selecione apenas um modo de geração (aleatorio/ordenado/inverso)\n\n");
    }
        
    if (indice_inicio_vetor_cmd == 0 && tamanho == 0 && nome_arquivo != NULL){
        //logica de descobrir pegar o vetor de dentro do arquivo
    }

    if(tamanho <= 0){
        printf("Erro: vetor sem tamanho\n\n");
        return -1;
    }

    Vector *vetor = vector_create(tamanho);

    if(gerar_aleatorio){
        int *dados = gerar_entradas_aleatorias(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
    }
    else if(gerar_ordenado){
       int *dados = gerar_entradas_ordenadas(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
    }
    else if(gerar_inverso){
       int *dados = gerar_entradas_inversas(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
    }
    else if(indice_inicio_vetor_cmd != 0){
        for (int i = 0; i < tamanho; i++){
            int valor = atoi(argv[i + indice_inicio_vetor_cmd]);
            vector_insert(vetor, valor, i);
        }
    }
    
    Vector *vetor_adaptativo = vector_copy(vetor);

    /* if(DEBUG){
        printf("\n\nVetor inicial: ");
        print_vector(vetor);
        printf("\n\n");
    } */

    //======================== INICIO DA ORDENACAO ALGORITMO PADRAO/ALGORITMO SELECIONADO ===============================
    printf("============================== INICIO ANALISE ALGORITMO PADRAO/SELECIONADO ==============================\n");
    
    printf("Ordenado via %s\n", nome_algoritmo(algoritmo));
    
    double inicio_padrao = obter_tempo(); //inicia o clock da analise padrao

      switch(algoritmo){
        case 0: selection_sort(vetor); break;
        case 1: bubble_sort(vetor); break;
        case 2: merge_sort(vetor); break;
        case 3: heap_sort(vetor); break; 
        case 4: lsd_radix_sort(vetor); break;
   }

    double fim_padrao = obter_tempo(); //fim do clock de analise padrao
    double tempo_padrao = fim_padrao - inicio_padrao; //o tempo total é dado pela diferenca dos clocks (inicial e final)


    if (DEBUG && !adaptativo){ 
        if(tamanho < 50){
            printf("Vetor ordenado: ");
            print_vector(vetor);
            printf("\n");
        }
    }
    printf("Numero de movimentacoes: %ld\n", vetor->movimentacoes);
    printf("Numero de comparacoes: %ld\n", vetor-> comparacoes);
    printf("Profundidade de recursao: %ld\n", vetor->profundidade_recursao);
    printf("Tempo de execucao do algoritmo selecionado: %.7f s\n\n", tempo_padrao);
    printf("Memoria utilizada: %.2f KB", vetor->pico_memoria_algoritmo/1024);

    printf("============================== FIM ANALISE ALGORITMO PADRAO/SELECIONADO ==============================\n\n\n");

    //================================================== FIM ============================================

    if(adaptativo){
        printf("============================== INICIO ANALISE SISTEMA ADAPTATIVO ==============================\n");

        CaracteristicasEntrada caracteristicas_vetor = analisar_propriedades(vetor_adaptativo);
        
        int algoritmo_adaptativo = arvore_decisao(caracteristicas_vetor);
        
        printf("=====> ALGORITMO SELECIONADO: %s\n\n", nome_algoritmo(algoritmo_adaptativo));
        
        double inicio_adaptativo = obter_tempo(); 
        
        switch(algoritmo_adaptativo){
            case 0: selection_sort(vetor_adaptativo); break;
            case 1: bubble_sort(vetor_adaptativo); break;
            case 2: merge_sort(vetor_adaptativo); break;
            case 3: heap_sort(vetor_adaptativo); break;
            case 4: lsd_radix_sort(vetor_adaptativo); break;
        }
        
        double fim_adaptativo = obter_tempo();
        double tempo_adaptativo = fim_adaptativo - inicio_adaptativo;
        
        if(DEBUG){
            printf("Vetor ordenado: ");
            print_vector(vetor_adaptativo);
            printf("\n");
            printf("Numero de movimentacoes: %ld\n", vetor_adaptativo->movimentacoes);
            printf("Tempo de execucao do algoritmo selecionado: %.10f s\n\n", tempo_adaptativo);
             printf("Profundidade de recursao: %ld\n", vetor->profundidade_recursao);
            printf("Tempo de execucao do algoritmo selecionado: %.7f s\n\n", tempo_adaptativo);
            printf("Memoria utilizada: %.2f KB", vetor_adaptativo->pico_memoria_algoritmo/1024);
        }

        printf("============================== FIM ANALISE SISTEMA ADAPTATIVO ==============================\n\n\n");

        printf("\n================ DUELO DE PERFORMANCE ================\n");
        printf("METRICA             | MODO ADAPTATIVO       | MODO PADRAO \n");
        printf("------------------------------------------------------\n");
        printf("Algoritmo Usado     | %s            | %s\n", nome_algoritmo(algoritmo_adaptativo), nome_algoritmo(algoritmo));
        printf("Tempo de Execucao   | %.7f seg            | %.7f seg\n", tempo_adaptativo, tempo_padrao);
        printf("Movimentacoes       | %lld                 | %lld\n", vetor_adaptativo->movimentacoes, vetor->movimentacoes);
        printf("Comparacoes         | %lld                 |  %lld\n", vetor_adaptativo->comparacoes, vetor->comparacoes);
        printf("Pico da Pilha (Recursao) | %d niveis             | %d niveis\n", vetor_adaptativo->profundidade_recursao, vetor->profundidade_recursao);
        printf("Pico de Memoria RAM | %.2f KB            | %.2f KB\n", vetor_adaptativo->pico_memoria_algoritmo / 1024.0, vetor->pico_memoria_algoritmo / 1024.0);
        printf("======================================================\n\n");
    }


    vector_destroy(vetor);
    vector_destroy(vetor_adaptativo);

    return 0;
}