#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "analise.h"
#include "sorting.h"
#include "memoria.h"
#include <time.h>

#define ALGORITMO_PADRAO 2


int main(int argc,char *argv[])
{


    if (argc < 2) {
        printf("modos de uso disponiveis:\n");
        printf("  1. arquivo:  %s <algoritmo|adaptativo> <arquivo.txt>\n", argv[0]);
        printf("  2. arquivo com tamanho fixo: %s <algoritmo|adaptativo> -tamanho <N> <arquivo.txt>\n", argv[0]);
        printf("  3. linha de comando:  %s <algoritmo|adaptativo> -vetor <num1> <num2> ... <numN>\n", argv[0]);
        return 0;
        }

    int tamanho = 0;
    int adaptativo = 0;
    int algoritmo = ALGORITMO_PADRAO;//0 = Selection Sort, 1 = Bubble Sort, 2  = Merge Sort (algoritmo por default), 3 = HeapSort
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
        else if (strcmp(argv[i], "adaptativo") == 0) {adaptativo = 1;}
        else if (strcmp(argv[i], "selection") == 0) {algoritmo = 0;}
        else if (strcmp(argv[i], "bubble") == 0) {algoritmo = 1;}
        else if (strcmp(argv[i], "merge") == 0) {algoritmo = 2;}
        else if (strcmp(argv[i], "heap") == 0) {algoritmo = 3;}
        else if (strstr(argv[i], ".txt") != NULL) {nome_arquivo = argv[i];}
    }
        
    if (indice_inicio_vetor_cmd == 0 && tamanho == 0 && nome_arquivo != NULL){
        //logica de descobrir o tamanho do vetor dentro do arquivo
    }

    if(tamanho <= 0){
        printf("Erro: vetor sem tamanho");
        return -1;
    }


    Vector *vetor = vector_create(tamanho);
    
    if (indice_inicio_vetor_cmd != 0){
        for (int i = 0; i < tamanho; i++){
            int valor = atoi(argv[i + indice_inicio_vetor_cmd]);
            vector_insert(vetor, valor, i);
        }
    }else if (nome_arquivo != NULL){
        //logica de carregar os dados de dentro do arquivo
    }
    
    Vector *vetor_adaptativo = vector_copy(vetor);

    printf("\n\nVetor inicial: ");
    print_vector(vetor);
    printf("\n\n");

    //======================== INICIO DA ORDENACAO ALGORITMO PADRAO/ALGORITMO SELECIONADO ===============================
    printf("============================== INICIO ANALISE ALGORITMO PADRAO/SELECIONADO ==============================\n\n\n");
    clock_t inicio_padrao = clock();
    size_t memoria_pico_padrao = 0;

    switch(algoritmo){
        case 0: selection_sort(vetor); printf("Ordenado via Selection Sort\n"); break;
        case 1: bubble_sort(vetor); printf("Ordenado via Bubble Sort\n"); break;
        case 2: merge_sort(vetor); printf("Ordenado via Merge Sort\n"); break;
        case 3: heap_sort(vetor); printf("Ordenado via Heap Sort\n"); break;
        default: merge_sort(vetor); printf("Ordenado via Merge Sort\n"); break;
   }
    clock_t fim_padrao = clock();
    double tempo_padrao = ((double)(fim_padrao - inicio_padrao))/CLOCKS_PER_SEC;
    memoria_pico_padrao = obter_pico_memoria();


    printf("Vetor ordenado: ");
    print_vector(vetor);
    printf("\n");
    printf("Numero de trocas: %ld\n", vetor->trocas);
    printf("Numero de trocas: %ld\n", vetor->trocas);
    printf("Tempo de execucao do algoritmo selecionado: %.06f s\n\n", tempo_padrao);

    printf("============================== FIM ANALISE ALGORITMO PADRAO/SELECIONADO ==============================\n\n\n");

    //================================================== FIM ============================================

    if(adaptativo){
        printf("============================== INICIO ANALISE SISTEMA ADAPTATIVO ==============================\n\n\n");
        clock_t inicio_adaptativo = clock(); 
        size_t memoria_pico_adaptativo = 0;
        size_t memoria_antes_adaptativo = obter_pico_memoria();

        CaracteristicasEntrada  caracteristicas_vetor = analisar_propriedades(vetor_adaptativo);

        int algoritmo_adaptativo = arvore_decisao(caracteristicas_vetor);

        switch(algoritmo_adaptativo){
        case 0: selection_sort(vetor_adaptativo); printf("Ordenado via Selection Sort\n"); break;
        case 1: bubble_sort(vetor_adaptativo); printf("Ordenado via Bubble Sort\n"); break;
        case 2: merge_sort(vetor_adaptativo); printf("Ordenado via Merge Sort\n"); break;
        case 3: heap_sort(vetor_adaptativo); printf("Ordenado via Heap Sort\n"); break;
        default: merge_sort(vetor_adaptativo); printf("Ordenado via Merge Sort\n"); break;
        }

        clock_t fim_adaptativo = clock();
        double tempo_adaptativo = ((double)(fim_adaptativo - inicio_adaptativo))/CLOCKS_PER_SEC;

        size_t memoria_depois_adaptativo = obter_pico_memoria();

        memoria_pico_adaptativo = (memoria_depois_adaptativo > memoria_antes_adaptativo) ? 
                        (memoria_depois_adaptativo - memoria_antes_adaptativo) : (memoria_antes_adaptativo - memoria_depois_adaptativo); 


        printf("Vetor ordenado: ");
        print_vector(vetor_adaptativo);
        printf("\n");
        printf("Numero de trocas: %ld\n", vetor_adaptativo->trocas);
        printf("Tempo de execucao do algoritmo selecionado: %.06f s\n\n", tempo_adaptativo);

        printf("============================== FIM ANALISE SISTEMA ADAPTATIVO ==============================\n\n\n");

        printf("\n================ DUELO DE PERFORMANCE ================\n");
        printf("METRICA             | MODO ADAPTATIVO       | MODO PADRAO (Merge)\n");
        printf("------------------------------------------------------\n");
        printf("Algoritmo Usado     | Case %d               | Case %d\n", algoritmo_adaptativo, algoritmo);
        printf("Tempo de Execuçao   | %.6f seg           | %.6f seg\n", tempo_adaptativo, tempo_padrao);
        printf("Movimentacoes (TAD) | %lld                  | %lld\n", vetor_adaptativo->trocas, vetor->trocas);
        printf("Pico de Memoria RAM | %.2f KB             | %.2f KB\n", 
           (double)memoria_pico_adaptativo / 1024.0, (double)memoria_pico_padrao / 1024.0);
        printf("======================================================\n\n");
    }


    vector_destroy(vetor);
    vector_destroy(vetor_adaptativo);

    return 0;
}