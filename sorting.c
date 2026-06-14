#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "vetor.h"

const char *nome_algoritmo(int algoritmo){
    switch(algoritmo){
        case 0: return "Selection Sort"; break;
        case 1: return "Bubble Sort"; break;
        case 2: return "Merge Sort"; break;
        case 3: return "Heap Sort"; break;
        case 4: return "Radix Sort"; break;
        default: return "Desconhecido"; break;
    }
}


//radix-sort versão LSD com counting-sort
void lsd_radix_sort(Vector *v) {
    
    //Verificação básica de existência do vetor
    if(v == NULL){
        printf("Erro ao ordenar o vetor. Vetor não existe ou é inválido");
        return;
    }

    int menor = v->data[0];
    int maior = v->data[0];
    for(int i = 1; i < v->size; i++){
        if(v->data[i] > maior){
            maior = v->data[i];
        }
    }

    //O objetivo da variavel largura é determinar o maior tamanho de digitos entre as variaveis 
    //para formatar todas elas com este tamanho e assim conseguir utilizar o counting sort
    int largura = 1;
    while (maior >= 10) {
        maior /= 10;
        largura++;
    } 

    //for para as iterações com cada digito indo do menos para o mais significativo
    Vector *vetor_aux = vector_create(10); //vetor auxiliar de 0 a 9
    Vector *vetor_ordenado = vector_create(v->size);
    //Teoricamente esse vetor auxiliar poderia ser entre o maior e o menor digito, porém para
    //teria que percorrer o vetor mais um vez, então no trade-off de espaço e tempo eu achei
    //mais interessante armazenar um pouco mais de memoria ao ínves de percorrer n.
    int valor_do_digito = 0;
    int exponencial = 10;//para conseguir o digito de cada valor eu estou um combinação da função modulo e divisão, porém estava fazendo isso com a função pow para conseguir as potencias de 10,
    //como isso poderia gerar um problema de processamento e prejudicar o tempo de execução criei essa variavel de exponencial para ir sendo multiplicada ou divida em cada interação
    //e assim conseguir resgatar o digito dos valores
    for(int digito = (largura-1); digito>=0; digito--) {
        
        //parte do counting sort
        for(int contagem_auxiliar = 0; contagem_auxiliar < v->size; contagem_auxiliar++) {
            valor_do_digito = (int)((vector_get(v, contagem_auxiliar)%exponencial)/(exponencial/10));
            for(int acumulo_somas = valor_do_digito; acumulo_somas < 10; acumulo_somas++) {
                vector_insert(vetor_aux, vector_get(vetor_aux, acumulo_somas)+1, acumulo_somas);
            }
        }

        
        //for da contagem de tras para frente para colocar os valores no indice ordenado
        for(int contagem_reversa = ((v->size)-1); contagem_reversa>=0; contagem_reversa--) {
            valor_do_digito = (int)((vector_get(v, contagem_reversa)%exponencial)/(exponencial/10));
            vector_insert(vetor_ordenado, vector_get(v, contagem_reversa), (vector_get(vetor_aux, valor_do_digito)-1));
            v->movimentacoes++;
            vector_insert(vetor_aux, vector_get(vetor_aux, valor_do_digito)-1, valor_do_digito);
            //Eu não passei subtraindo 1 de cada posição, mas sim subtraindo 1 do indice ao colocar no vetor ordenado
            
            //printando o vetor para verificação
            /* for(int j = 0; j<10; j++) {
                printf("%d", vector_get(vetor_aux, j));
            }
            printf("\n");*/
        }
        
        for (int p = 0; p<v->size; p++) {
            vector_insert(v, vector_get(vetor_ordenado, p), p);
            v->movimentacoes++;
            vector_insert(vetor_ordenado, 0, p);
        }
        
        for(int k= 0; k<10; k++) {
            vector_insert(vetor_aux, 0, k);
        }
        

        //atualização daa variavel de exponenciação
        exponencial *= 10;
    
    }

    vector_destroy(vetor_aux);
    vector_destroy(vetor_ordenado);
    
}

void selection_sort(Vector *v)
{

    if(v==NULL){
        printf("Erro ao ordenar o vetor. Vetor não existe ou é inválido");
        return;
    }

    int i,a;

    int valor_inicial = 0;
    int min_value,min_value_index;
    unsigned int size_vector = v->size;

    for(i=0;i<size_vector;i++){
        
        min_value_index = valor_inicial;
        
        for(a= valor_inicial + 1; a<size_vector; a++)
        {
            v->comparacoes++;

            if(vector_get(v,a) <  vector_get(v, min_value_index))min_value_index = a;

        }
        
        if(min_value_index != valor_inicial){

            vector_swap(v, min_value_index, valor_inicial);
        }

        valor_inicial++;
    }

}

void bubble_sort(Vector *v)
{
    
    if(v == NULL){
        printf("Erro ao ordenar o vetor. Vetor não existe ou é inválido");
        return;
    }

    int size_vector = v->size;
    int max_value = size_vector;
    int i,a,temp1,temp2;

    for(i=0;i<size_vector;i++){

        int swap = 0;

        for(a=0; a<max_value -1; a++){

            v->comparacoes++;

            if(vector_get(v, a + 1) < vector_get(v, a)){
                swap = 1;
                vector_swap(v, a, a+1);
            }
        }

        if(swap == 0)break;
        max_value--;
    }
}

void merge(Vector *v, Vector *u, int left, int mid, int right)
{
    int i = left;       // esquerda
    int j = mid + 1;    // direita
    int k = left;       // auxiliar

    // enquanto tiver elementos nos dois lados
    while (i <= mid && j <= right)
    {
        v->comparacoes++;

        if (vector_get(v, i) <= vector_get(v, j))
        {
           vector_insert(u, vector_get(v,i), k);
           v->movimentacoes++;
            i++;
        }
        else
        {
            vector_insert(u, vector_get(v, j), k);
            v->movimentacoes++;
            j++;
        }
        k++;
    }

    // sobra da esquerda
    while (i <= mid)
    {
        vector_insert(u, vector_get(v, i), k);
        v->movimentacoes++;
        i++;
        k++;
    }

    // sobra da direita
    while (j <= right)
    {
        vector_insert(u, vector_get(v, j), k);
        v->movimentacoes++;
        j++;
        k++;
    }

    // copia de volta
    for (i = left; i <= right; i++)
    {
        vector_insert(v, vector_get(u, i), i);
        v->movimentacoes++;
    }
}

void merge_sort(Vector *v)
{

    if(v == NULL)
    {
        printf("Não foi possivel ordenar o vetor. Vetor não existe ou é inválido.");
        return;
    }

    int tamanho = v->size;

    //vetor auxiliar
    Vector *u = vector_create(tamanho);

    for(int size = 1; size <tamanho; size *= 2)
    {
        for(int left = 0;left<tamanho -1; left += 2* size)
        {
            int mid = left + size - 1;
            int right = left + 2*size - 1;

            if (mid >= tamanho)continue;

            if (right >= tamanho)right = tamanho -1;

            merge(v,u,left,mid,right);

        }
  
    }

    vector_destroy(u);
}


//Funcao auxiliar ao heapsort
void heapify(Vector *v, int n, int i, int profundidade_atual){

    if(profundidade_atual > v->profundidade_recursao){
        v->profundidade_recursao = profundidade_atual;
    }

    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    //Se o filho esquerdo for maior que a raiz
    if (esq < n){
        v->comparacoes++;
        if(vector_get(v, esq) > vector_get(v, maior)){
           maior = esq;
       }

    }

    //Se o filho direito for maior que a raiz
    if (dir < n){
        v->comparacoes++;
        if (vector_get(v, dir) > vector_get(v, maior)){
            maior = dir;
        }

    }

    //Se o maior não for a raiz, faz a troca e continua descendo
    if (maior != i){
        vector_swap(v, i, maior);
        heapify(v, n, maior, profundidade_atual + 1);
    }

    return;
}

void heap_sort(Vector *v){

    if (v == NULL){ 
        printf("Não foi possível ordenar o vetor. Vetor não existe ou é inválido");
        return; 
    }

    int n = v->size;
    
    for (int i = (n/2)-1; i >= 0; i--){
        heapify(v, n, i, 1);
    }

    for(int i = n-1; i > 0; i--){
        vector_swap(v, i, 0);

        heapify(v, i , 0, 1);
    }

    return;
}


