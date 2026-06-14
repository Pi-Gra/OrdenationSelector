# Sistema Adaptativo de Ordenação

Trabalho Prático da disciplina de Estruturas de Dados II (SCC0606) do Instituto de Ciências Matemáticas e de Computação (ICMC) da Universidade de São Paulo (USP), Campus de São Carlos.

## 📋 Descrição
O objetivo deste projeto é implementar um sistema adaptativo capaz de analisar as propriedades de um vetor de entrada (tamanho, desordem, duplicatas, etc.) e selecionar automaticamente o algoritmo de ordenação mais eficiente para aquele cenário específico.

## 📂 Estrutura do Projeto
- `main.c`: Ponto de entrada, manipulação de argumentos (CLI) e execução do Duelo de Performance.
- `analise.c` / `analise.h`: Funções de extração de métricas e Árvore de Decisão (Heurística).
- `sorting.c` / `sorting.h`: Implementação dos 5 algoritmos de ordenação (Selection, Bubble, Merge, Heap, Radix).
- `tratamento_entradas.c` / `tratamento_entradas.h`: Geração e análise de vetores (aleatórios, ordenados, inversos, adversariais) e leitura de arquivos.
- `vetor.c` / `vetor.h`: Estrutura de dados principal e funções de manipulação e rastreio de métricas.
- `tempo.c` / `tempo.h`: Funções para marcação de tempo de execução (relógio de alta precisão).

## ⚙️ Compilação
Para compilar o código-fonte manualmente via terminal (Linux/macOS ou Windows com MinGW), utilize o compilador `gcc` linkando a biblioteca matemática (`-lm`):

```bash
gcc -o programa *.c -lm