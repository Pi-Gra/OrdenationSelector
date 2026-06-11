#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "sorting.h"



int main(int argc,char *argv[])
{

    if(argc < 2)
    {
        return 0;
    }

    int tamanho = 0;
    int adaptativo = 0;
    int algoritmo;//0 = Selection Sort, 1 = Bubble Sort, 2  = Merge Sort, 3 = HeapSort


    //Aqui o tamanho ja é informado via linha de comando
   if(argc >= 3 && strcmp(argv[argc-2], "-tamanho") == 0)tamanho = atoi(argv[argc - 1]);
   //Aqui o tamanho não é informado e o programa precisa encontrar
   else
   {

   }

   if(tamanho == 0)
   {
    printf("Erro vetor com tamanho nulo.");
    system("pause");
    return -1;
   }

   //checa se o método adaptativo foi selecionado

   if(strcmp(argv[1], "adaptativo") == 0 || strcmp(argv[1], "dados.txt") == 0 )adaptativo = 1;

   //Seleciona o algoritmo de ordenação pelo modo adapativo
   if(adaptativo == 1){

   }

   else
   {

    if(strcmp(argv[1],"selection") == 0)algoritmo = 0;
    else if(strcmp(argv[1], "bubble") == 0)algoritmo = 1;
    else if(strcmp(argv[1], "merge") == 0)algoritmo = 2;
    else if(strcmp(argv[1], "heap") == 0)algoritmo = 3;

   }

   Vector *vetor = vector_create(tamanho);


   switch(algoritmo){
    case 0:
    selection_sort(vetor);
    break;
    case 1:
    bubble_sort(vetor);
    break;
    case 2:
    merge_sort(vetor);
    break;
    case 3:
    heap_sort(vetor);
    break;
    default:
    merge_sort(vetor);
    break;
   }
   
   vector_destroy(vetor);




   return 0;


}