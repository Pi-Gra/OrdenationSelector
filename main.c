#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "analise.h"
#include "sorting.h"



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
    int algoritmo = 2;//0 = Selection Sort, 1 = Bubble Sort, 2  = Merge Sort (algoritmo por default), 3 = HeapSort
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
        else if (strcmp(argv[i], "adaptativo") == 0){
            adaptativo = 1;
        }
        else if (strcmp(argv[i], "selection") == 0){
            algoritmo = 0;
        }
        else if (strcmp(argv[i], "bubble") == 0){
            algoritmo = 1;
        }
        else if (strcmp(argv[i], "merge") == 0){
            algoritmo = 2;
        }
        else if (strcmp(argv[i], "heap") == 0){
            algoritmo = 3;
        }
        else if (strstr(argv[i], ".txt") != NULL){
            nome_arquivo = argv[i];
        }
    }
        
    if (indice_inicio_vetor_cmd == 0 && tamanho == 0 && nome_arquivo != NULL){
        //aqui entra a logica de descobrir o tamanho do vetor dentro do arquivo
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

    printf("Vetor inicial: ");
    print_vector(vetor);
    printf("\n");

    if(adaptativo){
        //logica do sistema adaptativo
    }

    
    switch(algoritmo){
        case 0:
            selection_sort(vetor);
            printf("Ordenado via Selection Sort\n");
            break;
        case 1:
            bubble_sort(vetor);
            printf("Ordenado via Bubble Sort\n");
            break;
        case 2:
            merge_sort(vetor);
            printf("Ordenado via Merge Sort\n");
            break;
        case 3:
            heap_sort(vetor);
            printf("Ordenado via Heap Sort\n");
            break;
        default:
            merge_sort(vetor);
            printf("Ordenado via Merge Sort\n");
            break;
   }

   printf("Vetor ordenado: ");
   print_vector(vetor);
   printf("\n");
   printf("Numero de trocas: %ld", vetor->trocas);


   vector_destroy(vetor);

   return 0;
}