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

/* Função auxiliar para padronizar e estruturar as métricas em formato de tabela ASCII */
void imprimir_relatorio_execucao(const char* titulo, const char* algoritmo, double tempo, Vector* v) {
    printf("\n+------------------------------------------------------+\n");
    printf("| %-52s |\n", titulo);
    printf("+------------------------------------------------------+\n");
    printf("| Algoritmo Executado    : %-27s |\n", algoritmo);
    printf("| Tempo de Execucao (s)  : %-27.7f |\n", tempo);
    printf("| Numero de Movimentacoes: %-27lld |\n", v->movimentacoes);
    printf("| Numero de Comparacoes  : %-27lld |\n", v->comparacoes);
    printf("| Profundidade Recursao  : %-27lld |\n", v->profundidade_recursao);
    printf("| Pico de Memoria RAM    : %-24.2f KB |\n", v->pico_memoria_algoritmo / 1024.0);
    printf("+------------------------------------------------------+\n");
}

int main(int argc, char *argv[])
{
    /* Inicializa a semente do rand para geradores aleatórios */
    srand(time(NULL));

    /* Validação simples de argumentos via linha de comando */
    if (argc < 2) {
        printf("modos de uso disponiveis:\n");
        printf("  1. arquivo:  %s <algoritmo|adaptativo> <arquivo.txt>\n", argv[0]);
        printf("  2. linha de comando:  %s <algoritmo|adaptativo> -vetor <num1> <num2> ... <numN>\n", argv[0]);
        printf("  3. linha de comando:  %s <algoritmo|adaptativo> -aleatorio/-ordenado/-inverso -tamanho X(inteiro)\n", argv[0]);
        return 0;
    }

    int tamanho = 0;
    int adaptativo = 0;
    int algoritmo = ALGORITMO_PADRAO; 
    int gerar_aleatorio = 0;
    int gerar_ordenado = 0;
    int gerar_inverso = 0;
    char *nome_arquivo = NULL;
    int indice_inicio_vetor_cmd = 0; 

    /* Parsing dos parâmetros passados por linha de comando */
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

    /* Validação de exclusividade dos modos de geração de dados */
    int quantidade_modos = gerar_aleatorio + gerar_ordenado + gerar_inverso;
    if(quantidade_modos > 1){
        printf("Erro: selecione apenas um modo de geração (aleatorio/ordenado/inverso)\n\n");
        return -1;
    }

    /* Resgata tamanho do vetor caso a entrada venha de arquivos */
    if (indice_inicio_vetor_cmd == 0 && tamanho == 0 && nome_arquivo != NULL){
        tamanho = tamanho_arquivo(nome_arquivo);
    }

    if(tamanho <= 0){
        printf("Erro: vetor sem tamanho\n\n");
        return -1;
    }

    /* Criação e população do vetor principal baseado nas flags ativadas */
    Vector *vetor = vector_create(tamanho);

    if(indice_inicio_vetor_cmd == 0 && nome_arquivo != NULL) {
        int *dados = leitura_arquivos(nome_arquivo, tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
        free(dados);
    }

    if(gerar_aleatorio){
        int *dados = gerar_entradas_aleatorias(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
        free(dados);
    }
    else if(gerar_ordenado){
       int *dados = gerar_entradas_ordenadas(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
        free(dados);
    }
    else if(gerar_inverso){
       int *dados = gerar_entradas_inversas(tamanho);
        for (int i = 0; i < tamanho; i++){
            vector_insert(vetor, dados[i], i);
        }
        free(dados);
    }
    else if(indice_inicio_vetor_cmd != 0){
        for (int i = 0; i < tamanho; i++){
            int valor = atoi(argv[i + indice_inicio_vetor_cmd]);
            vector_insert(vetor, valor, i);
        }
    }
    
    /* Duplica o vetor original para manter dados idênticos no teste do comparativo adaptativo */
    Vector *vetor_adaptativo = vector_copy(vetor);

    if(DEBUG && vetor_adaptativo->tamanho < 50){
        printf("\n\nVetor inicial: ");
        print_vector(vetor);
        printf("\n\n");
    }

    //======================== EXECUÇÃO DO ALGORITMO PADRÃO / SELECIONADO ===============================
    
    double inicio_padrao = obter_tempo(); 

    switch(algoritmo){
        case 0: selection_sort(vetor); break;
        case 1: bubble_sort(vetor); break;
        case 2: merge_sort(vetor); break;
        case 3: heap_sort(vetor); break; 
        case 4: lsd_radix_sort(vetor); break;
    }

    double fim_padrao = obter_tempo(); 
    double tempo_padrao = fim_padrao - inicio_padrao; 

    /* Exibe tabela estruturada do algoritmo fixo */
    imprimir_relatorio_execucao("ANALISE: ALGORITMO PADRAO / SELECIONADO", nome_algoritmo(algoritmo), tempo_padrao, vetor);

    if (DEBUG && !adaptativo){ 
        if(tamanho < 50){
            printf("Vetor ordenado: ");
            print_vector(vetor);
            printf("\n");
        }
    }

    //================================================== MODO ADAPTATIVO ============================================

    if(adaptativo){
        /* Executa a extração das propriedades do vetor e a tomada de decisão automática */
        CaracteristicasEntrada caracteristicas_vetor = analisar_propriedades(vetor_adaptativo);
        int algoritmo_adaptativo = arvore_decisao(caracteristicas_vetor);
        
        printf("=====> ALGORITMO SELECIONADO PELA HEURISTICA: %s\n\n", nome_algoritmo(algoritmo_adaptativo));
        
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
        
        /* Exibe tabela estruturada do algoritmo adaptativo */
        imprimir_relatorio_execucao("ANALISE: SISTEMA ADAPTATIVO", nome_algoritmo(algoritmo_adaptativo), tempo_adaptativo, vetor_adaptativo);

        if(DEBUG && vetor_adaptativo->tamanho < 50){
            printf("Vetor ordenado: ");
            print_vector(vetor_adaptativo);
            printf("\n");
        }

        /* Tabela unificada comparativa final (Duelo de Performance) */
        printf("\n================ DUELO DE PERFORMANCE ================\n");
        printf("METRICA                  | MODO ADAPTATIVO       | MODO PADRAO \n");
        printf("------------------------------------------------------\n");
        printf("Algoritmo Usado          | %-21s | %-21s\n", nome_algoritmo(algoritmo_adaptativo), nome_algoritmo(algoritmo));
        printf("Tempo de Execucao        | %-17.7f seg | %-17.7f seg\n", tempo_adaptativo, tempo_padrao);
        printf("Movimentacoes            | %-21lld | %-21lld\n", vetor_adaptativo->movimentacoes, vetor->movimentacoes);
        printf("Comparacoes              | %-21lld | %-21lld\n", vetor_adaptativo->comparacoes, vetor->comparacoes);
        printf("Pico da Pilha (Recursao) | %-14lld niveis | %-14lld niveis\n", vetor_adaptativo->profundidade_recursao, vetor->profundidade_recursao);
        printf("Pico de Memoria RAM      | %-18.2f KB | %-18.2f KB\n", vetor_adaptativo->pico_memoria_algoritmo / 1024.0, vetor->pico_memoria_algoritmo / 1024.0);
        printf("======================================================\n\n");
    }

    /* Desalocação e encerramento */
    vector_destroy(vetor);
    vector_destroy(vetor_adaptativo);

    return 0;
}