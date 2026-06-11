#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "sorting.h"
#include "analise.h"
#define BUFFER 10


char buffer[BUFFER];
int tamanho,i,a;

int main()
{

    printf("Teste Vetor\n");
    printf("Insira o tamanho: ");

    tamanho = 0;
    fflush(stdin);
    fgets(buffer,sizeof(buffer),stdin);
    for(i=0;buffer[i]!='\0';i++)if(buffer[i]<32)buffer[i]='\0';
    tamanho = atoi(buffer);

    Vector *vetor = vector_create(tamanho);

    for(i=0;i<tamanho;i++)
    {
        printf("\n");
        printf("insira os digítos: ");
        fflush(stdin);
        fgets(buffer,sizeof(buffer),stdin);
        for(a=0;buffer[a]!='\0';a++)if(buffer[a]<32)buffer[a]='\0';
        vetor->data[i] = atoi(buffer);
    }

    for(i=0;i<tamanho;i++){
        printf("%d ", vector_get(vetor, i));
    }

    printf("\n");

    CaracteristicasEntrada controle = analisar_propriedades(vetor);
    printf("\nTamanho: %d\n", controle.tamanho);
    printf("Amplitude: %d\n", controle.amplitude);
    printf("Desvio Padrao: %.2f\n", controle.desvio_padrao);
    printf("Percentual de Desordem: %.2f%%\n", controle.percentual_desordem);

    if (controle.quase_ordenado == 1){
        printf("Quase ordenado?: SIM");
    }else{
        printf("Quase ordenado?: NAO");
    }

    if (controle.quase_inverso == 1){
        printf("Quase inverso?: SIM");
    }else{
        printf("Quase inverso?: NAO");
    }

    printf("Numero de Duplicatas: %d\n", controle.numero_duplicatas);
    printf("Densidade de Duplicatas: %.2f%%\n", controle.densidade_duplicatas * 100);

    heap_sort(vetor);

    for(i=0;i<tamanho;i++){
        printf("%d ", vector_get(vetor, i));
    }

    system("pause");

    vector_destroy(vetor);

    system("pause");

    return 0;
}