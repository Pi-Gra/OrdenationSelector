# 📊 OrdenationSelector - Sistema Adaptativo de Ordenação

Trabalho Prático da disciplina **SCC0606 - Estruturas de Dados II**.  
*Instituto de Ciências Matemáticas e de Computação (ICMC) - Universidade de São Paulo (USP), São Carlos.*

---

## 📋 Descrição do Projeto
O **OrdenationSelector** é um sistema adaptativo heurístico desenvolvido para otimizar o processo de ordenação de dados. A escolha do algoritmo ideal não depende apenas do tamanho da entrada, mas das propriedades estruturais do vetor. 

Este projeto analisa estatisticamente a entrada (grau de desordem, densidade de duplicatas, quantidade de subvetores já ordenados e amplitude) e utiliza uma **Árvore de Decisão** para acionar automaticamente o algoritmo mais eficiente para o cenário específico, mitigando piores casos e otimizando o consumo de tempo e memória.

Os algoritmos implementados cobrem diferentes classes de complexidade:
* **O(n²):** Selection Sort, Bubble Sort (Otimizado com *early exit*).
* **O(n log n):** Merge Sort, Heap Sort.
* **Não-comparativo:** Radix Sort LSD.

---

## 🏗 Estrutura e Arquitetura
O sistema foi construído de forma modularizada em **C**, garantindo alta coesão e baixo acoplamento:

* 🧠 **`analise.c` / `.h`**: Extrai métricas estruturais (desvio padrão, runs, amplitude) e abriga a Árvore de Decisão que mapeia as propriedades da entrada para o algoritmo ideal.
* ⚙️ **`sorting.c` / `.h`**: Contém as implementações puras dos cinco métodos de ordenação abordados.
* 📦 **`vetor.c` / `.h`**: Gerencia a alocação e realiza a telemetria em tempo real (contagem de comparações, movimentações, pico de memória RAM e profundidade de recursão).
* 🎲 **`tratamento_entradas.c` / `.h`**: Capaz de realizar parsing de arquivos externos ou gerar em tempo de execução vetores aleatórios, ordenados e reversamente ordenados.
* ⏱️ **`tempo.c` / `.h`**: Utilitário de benchmarking de alta precisão utilizando a biblioteca `clock_gettime`.
* 🖥️ **`main.c`**: Processa os argumentos via CLI, coordena a análise adaptativa e renderiza o "Duelo de Performance" comparativo.
* 🛠️ **`gerador_entradas.c`**: Script auxiliar independente para a geração em lote das entradas físicas `.txt` (incluindo casos adversariais).

---

## ⚙️ Instruções de Compilação
O projeto foi desenvolvido garantindo compatibilidade com o padrão C99 e compilação nativa via GCC. Como há uso de funções matemáticas que não estão nas operações matemáticas básicas do C (`math.h`), a lincagem da biblioteca matemática é obrigatória.

No terminal de sua preferência, execute:
```bash
gcc -o main *.c -lm
```

## 🚀 Parâmetros Aceitos (CLI)
A interface de linha de comando (CLI) foi projetada para permitir testes isolados e auditoria dos algoritmos de forma prática.

**1. Seleção de Modo (Obrigatório escolher 1):**
* `adaptativo`: Delega a escolha ao sistema inteligente.
* `selection`, `bubble`, `merge`, `heap`, `radix`: Força a execução de um algoritmo de ordenação estático para fins de *baseline*.

**2. Origem dos Dados (Obrigatório escolher 1):**
* `-aleatorio`, `-ordenado`, `-inverso`: Utiliza geradores de dados alocados diretamente em memória.
* `-vetor N1 N2 ... N`: Inserção manual de uma sequência de inteiros diretamente no terminal.
* `arquivo.txt`: Realiza a leitura e instanciação a partir de um arquivo de texto local.

**3. Configuração de Tamanho:**
* `-tamanho X`: Define a dimensão da entrada (obrigatório caso opte por usar os geradores `-aleatorio`, `-ordenado` ou `-inverso`).

## 💡 Exemplos de Uso e Execução

**1. Testar o Sistema Adaptativo com Vetor Aleatório:**
```bash
./main adaptativo -aleatorio -tamanho 10000 # Linux
main adaptativo -aleatorio -tamanho 10000 # Windows
```

**2. Forçar a Ordenação com Heap Sort em um Vetor Inverso:**
```bash
./main heap -inverso -tamanho 50000 # Windows
./main heap -inverso -tamanho 50000 # Linux
```

**3. Testar a Heurística com Dados de um Arquivo `.txt`:**
```bash
./main adaptativo /inputs/nome-do-arquivo.txt # Windows
./main adaptativo /inputs/nome-do-arquivo.txt # Linux
```

**4. Passar um Vetor Manualmente via Terminal com Radix Sort:**
```bash
./main radix -vetor 9 3 12 5 8 1 # Windows
./main radix -vetor 9 3 12 5 8 1 # Linux
```

## 🧪 Reprodução dos Experimentos
A auditoria e reprodutibilidade científica dos dados apresentados no relatório são garantidas por meio de automação. Foram criados scripts que compilam o código, executam uma bateria de testes exaustiva (incluindo quebra de heurística via **Entradas Adversariais**) e extraem os resultados para um log tabelado.

**Ambientes Linux / macOS / WSL:**
1. Navegue até a raiz do projeto no terminal.
2. Conceda permissão de execução: `chmod +x executar_experimentos.sh`
3. Acione a bateria: `./executar_experimentos.sh`

**Ambientes Windows (Prompt de Comando / PowerShell):**
1. Navegue até a raiz do projeto no terminal.
2. Acione o lote de comandos: `.\executar_experimentos.bat`

Todos os painéis analíticos, tempos de execução e métricas de consumo (movimentações, pico de recursão, uso de RAM) de todas as execções serão consolidados de forma legível no arquivo gerado `resultados_experimentos.txt`.
