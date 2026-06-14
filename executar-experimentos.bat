@echo off
setlocal enabledelayedexpansion

:: Define o nome do arquivo de saida
set ARQUIVO_LOG=resultados_experimentos.txt

echo ==================================================
echo  Iniciando Automacao dos Experimentos
echo ==================================================

:: 1. Compilacao
echo [1/3] Compilando o projeto...
gcc -o main.exe *.c -lm

:: Verifica se a compilacao falhou
if %ERRORLEVEL% NEQ 0 (
    echo Erro na compilacao! Abortando os testes.
    exit /b 1
)
echo Compilacao concluida com sucesso.

:: 2. Preparacao do arquivo de log
echo [2/3] Preparando o log de resultados...
echo RESULTADOS DOS EXPERIMENTOS - ESTRUTURAS DE DADOS II > %ARQUIVO_LOG%
echo ==================================================== >> %ARQUIVO_LOG%

:: 3. Execucao da Bateria de Testes
echo [3/3] Executando testes e gravando no log...

:: Array simulado com os arquivos de teste
set TESTES=inputs\aleatorio_1k.txt inputs\aleatorio_10k.txt inputs\aleatorio_100k.txt inputs\aleatorio_1000k.txt inputs\aleatorio_10000k.txt inputs\inverso_100k.txt inputs\quase-ordenado_100k.txt inputs\repetidos_100k.txt inputs\adversarial_bubble.txt inputs\adversarial_radix.txt

:: Roda o programa no modo adaptativo para cada arquivo
for %%T in (%TESTES%) do (
    echo  -^> Testando: %%T
    echo. >> %ARQUIVO_LOG%
    echo ^>^>^> EXPERIMENTO: %%T ^<^<^< >> %ARQUIVO_LOG%
    main.exe adaptativo %%T >> %ARQUIVO_LOG%
)

echo ==================================================
echo  Testes finalizados! Resultados salvos em: %ARQUIVO_LOG%
echo ==================================================
pause
