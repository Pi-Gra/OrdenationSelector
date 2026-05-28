#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "sorting.h"
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
        printf("insira primeiro digíto: ");
        fflush(stdin);
        fgets(buffer,sizeof(buffer),stdin);
        for(a=0;buffer[a]!='\0';a++)if(buffer[a]<32)buffer[a]='\0';
        vetor->data[i] = atoi(buffer);

    }

    for(i=0;i<tamanho;i++){
        printf("%d ", vector_get(vetor, i));
    }

    printf("\n");

    selection_sort(vetor);

    for(i=0;i<tamanho;i++){
        printf("%d ", vector_get(vetor, i));
    }

    vector_destroy(vetor);



    system("pause");

    

    


    return 0;

}