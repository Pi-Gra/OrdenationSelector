#ifndef TRATAMENTOENTRATAS_H
#define TRATAMENTOENTRADAS_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int *gerar_entradas_aleatorias(unsigned int tamanho);
int *gerar_entradas_ordenadas(unsigned int tamanho);
int *gerar_entradas_inversas(unsigned int tamanho);
int tamanho_arquivo(const char *nome_arquivo);
int *leitura_arquivos(const char *nome_arquivo, int tamanho_arq);

 

#endif