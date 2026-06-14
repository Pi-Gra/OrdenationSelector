#!/bin/bash

# Define o nome do arquivo de saida
ARQUIVO_LOG="resultados_experimentos.txt"

echo "=================================================="
echo " Iniciando Automação dos Experimentos"
echo "=================================================="

# 1. Compilação
echo "[1/3] Compilando o projeto..."
gcc -o build/main *.c -lm

# Verifica se a compilação falhou
if [ $? -ne 0 ]; then
    echo "Erro na compilação! Abortando os testes."
    exit 1
fi
echo "Compilação concluída com sucesso."

# 2. Preparação do arquivo de log
echo "[2/3] Preparando o log de resultados..."
echo "RESULTADOS DOS EXPERIMENTOS - ESTRUTURAS DE DADOS II" > $ARQUIVO_LOG
echo "====================================================" >> $ARQUIVO_LOG

# 3. Execução da Bateria de Testes
echo "[3/3] Executando testes e gravando no log..."

# Lista dos arquivos de entrada gerados anteriormente
TESTES=(
    "inputs/aleatorio_1k.txt"
    "inputs/aleatorio_10k.txt"
    "inputs/aleatorio_100k.txt"
    "inputs/aleatorio_1000k.txt"
    "inputs/aleatorio_10000k.txt"
    "inputs/inverso_100k.txt"
    "inputs/quase-ordenado_100k.txt"
    "inputs/repetidos_100k.txt"
    "inputs/adversarial_bubble.txt"
    "inputs/adversarial_radix.txt"
)

# Roda o programa no modo adaptativo para cada arquivo da lista
for TESTE in "${TESTES[@]}"; do
    echo " -> Testando: $TESTE"
    echo -e "\n\n>>> EXPERIMENTO: $TESTE <<<" >> $ARQUIVO_LOG
    ./main adaptativo "$TESTE" >> $ARQUIVO_LOG
done

echo "=================================================="
echo " Testes finalizados! Resultados salvos em: $ARQUIVO_LOG"
echo "=================================================="
