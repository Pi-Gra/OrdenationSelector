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
```

## 🚀 Parâmetros Aceitos (CLI)
O sistema foi projetado para receber comandos de forma flexível pelo terminal. 

**Modos de Operação (Escolha 1):**
* `adaptativo`: O sistema escolhe automaticamente o algoritmo.
* `selection`, `bubble`, `merge`, `heap`, `radix`: Força a execução de um algoritmo específico.

**Formato de Entrada (Escolha 1):**
* `-aleatorio`: Gera dados randômicos.
* `-ordenado`: Gera dados em ordem crescente.
* `-inverso`: Gera dados em ordem decrescente.
* `-vetor N1 N2 ...`: Passa os elementos diretamente no terminal.
* `arquivo.txt`: Lê os dados de um arquivo externo (o arquivo deve conter o tamanho na primeira linha válida).

**Configuração de Tamanho:**
* `-tamanho X`: Define a quantidade de elementos a serem gerados (obrigatório para os geradores internos).

## 💡 Exemplos de Uso e Execução

**1. Testar o Sistema Adaptativo com Vetor Aleatório:**
```bash
./main adaptativo -aleatorio -tamanho 10000
```

**2. Forçar a Ordenação com Heap Sort em um Vetor Inverso:**
```bash
./main heap -inverso -tamanho 50000
```

**3. Testar a Heurística com Dados de um Arquivo `.txt`:**
```bash
./main adaptativo dados.txt
```

**4. Passar um Vetor Manualmente via Terminal com Radix Sort:**
```bash
./main radix -vetor 9 3 12 5 8 1
```