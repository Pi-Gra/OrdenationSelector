#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Funcao auxiliar para gravar o cabecalho padrao */
void escrever_cabecalho(FILE *f, const char *descricao, int n) {
    fprintf(f, "%s\n#\n%d\n", descricao, n);
}

/* Funcao auxiliar para gravar os dados com 20 elementos por linha */
void imprimir_vetor_arquivo(FILE *f, int *vetor, int n) {
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d", vetor[i]);
        if ((i + 1) % 20 == 0) {
            fprintf(f, "\n");
        } else if (i != n - 1) {
            fprintf(f, " ");
        }
    }
    if (n % 20 != 0) fprintf(f, "\n");
}

/* 1. Gerador Aleatorio */
void gerar_aleatorio(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) v[i] = ((rand() << 9) | rand()) & 0x3FFFFFFF; // Gera aleatorios grandes
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

/* 2. Gerador Inverso */
void gerar_inverso(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) v[i] = n - i;
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

/* 3. Gerador Quase Ordenado (5% de desordem) */
void gerar_quase_ordenado(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) v[i] = i + 1;
    
    // Bagunca 5% do vetor realizando trocas aleatorias
    int swaps = n * 0.05;
    for(int i = 0; i < swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = v[idx1];
        v[idx1] = v[idx2];
        v[idx2] = temp;
    }
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

/* 4. Gerador Muitos Repetidos (Alta densidade de duplicatas) */
void gerar_repetidos(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    // Cria um vetor com apenas 10 valores unicos possiveis
    for(int i = 0; i < n; i++) v[i] = (rand() % 10) * 1000;
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

/* 5. Gerador Adversarial: Bubble Sort (Efeito Tartaruga) */
void gerar_adversarial_bubble(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        v[i] = (i == n - 1) ? 0 : (i + 1); // Vetor ordenado, mas o ultimo elemento e 0
    }
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

/* 6. Gerador Adversarial: Radix Sort (Enganando a Amplitude) */
void gerar_adversarial_radix(int n, const char* filepath, const char* desc) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;
    escrever_cabecalho(f, desc, n);
    
    int *v = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        v[i] = (i < (n * 0.8)) ? 2000000000 : 2000000100; // 80% do vetor e igual, 20% muda levemente (limite de 32bits)
    }
    
    imprimir_vetor_arquivo(f, v, n);
    free(v);
    fclose(f);
    printf("-> %s gerado com sucesso!\n", filepath);
}

int main() {
    srand(time(NULL));
    printf("Iniciando geracao de todas as entradas...\n");

    gerar_aleatorio(1000, "inputs/aleatorio_1k.txt", "Aleatorio 1K");
    gerar_aleatorio(100000, "inputs/aleatorio_100k.txt", "Aleatorio 100K");
    gerar_inverso(100000, "inputs/inverso_100k.txt", "Inverso 100K");
    gerar_quase_ordenado(100000, "inputs/quase-ordenado_100k.txt", "Quase Ordenado 100K (5%% baguncado)");
    gerar_repetidos(100000, "inputs/repetidos_100k.txt", "Muitas Duplicatas 100K");
    gerar_adversarial_bubble(100000, "inputs/adversarial_bubble.txt", "Adversarial Bubble Sort 100K");
    gerar_adversarial_radix(100000, "inputs/adversarial_radix.txt", "Adversarial Radix Sort 100K");
    
    printf("Geracao concluida! Pronto para rodar os testes na main.\n");
    return 0;
}