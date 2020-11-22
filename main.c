#include "stdio.h"
#include "stdlib.h"
#include "time.h"


void troca(int *num1, int *num2){ // função que auxliará a troca de elementos do vetor
    int aux;
    aux=*num1;
    *num1=*num2;
    *num2=aux;

}

void bolha(int *vetor, int N){
    int i, continua, aux, fim = N;
    do{
        continua = 0;
        for(i = 0; i<fim-1;i++){
            if(vetor[i]>vetor[i+1]){
                aux=vetor[i];
                vetor[i]=vetor[i+1];
                vetor[i+1]=aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}

void selection(int *vetor, int tamanho){
    int menor, troca;
    for(int i = 0; i < tamanho - 1; i++){
        menor = i;
        for(int j = i + 1; j < tamanho; j++){
            if(vetor[j] < vetor[menor]){
                menor = j;
            }
        }
        if(i!=menor){
            troca = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = troca;
        }
    }
}

void merge( int *vetor, int inicio,int meio, int fim){
    int *temp, p1, p2, tamanho, i , j, k,aux;
    int fim1 = 0, fim2=0;
    tamanho = fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp=malloc(tamanho*sizeof(int));

    if( temp != NULL)
    {
        for(i=0;i<tamanho;i++){
            if(!fim1 && !fim2){              
                if(vetor[p1]<vetor[p2]){ // combinando ordenado
                    temp[i]=vetor[p1++];
                    
                }else{
                    temp[i]=vetor[p2++];
                }              
                if(p1>meio) fim1=1; // vetor 1 acabou?
                if(p2>fim) fim2=1; // vetor2 acabou?
            }else{
                if(!fim1)
                    temp[i]=vetor[p1++];
                else
                    temp[i]=vetor[p2++];               
            }
        }
        for(j=0, k=inicio; j<tamanho; j++,k++)
            vetor[k]=temp[j];
    }
    free(temp);
}
void mergeSort( int *vetor, int inicio, int fim){
    if(inicio<fim)
    {
        int meio = (fim+inicio)/2;
        mergeSort(vetor, inicio, meio); // chama a função para primeira metade
        mergeSort(vetor,meio+1,fim);  // chama a função para segunda metade
        merge(vetor,inicio,meio,fim); // combina as duas metades de forma ordenada 
    }
}

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}


void criarHeap(int *vetor, int inicio, int fim){
    int aux=vetor[inicio]; //pai
    int j=inicio*2+1;
    while(j<=fim){ // filho menor que o vetor?
        if(j<fim){
             
            if(vetor[j]<vetor[j+1]){ // quem dos filhos é o maior?
                j=j+1;
            }
        }
        if(aux<vetor[j]){ // o pai é menor que o filho?

            vetor[inicio]=vetor[j]; // filho se torna pai
            inicio=j;
            j=inicio*2+1;
        }else{
            j=fim+1;
        }
    }
    vetor[inicio]=aux; // antigo pai ocupa o lugar do ultimo filho
}

void heapSort(int *vetor, int N){
    int i;
    for(i=(N-1)/2;i>=0;i--){ // criar heap a partir de dois dados
        criarHeap(vetor,i,N-1);
    }
    for(i=N-1;i>=1;i--){
        troca(&vetor[0],&vetor[i]); // pega o maior elemento da heap e coloca na sua posição correspondente no vetor
        criarHeap(vetor,0,i-1); // reconstruir a heap
    }
}



void imprimir(int *vetor, int tamanho){
    for(int i = 0;i < tamanho; i++){
        printf("%d ",vetor[i]);
    }
}

int main(){
    srand(time(NULL));

    int tamanho;
    printf("Digite o tamanho do vetor: ");
    scanf("%d",&tamanho);

    int *vetor_bolha=malloc(tamanho*sizeof(int));
    int *vetor_selection=malloc(tamanho*sizeof(int));
    int *vetor_merge=malloc(tamanho*sizeof(int));
    int *vetor_quick=malloc(tamanho*sizeof(int));
    int *vetor_heap=malloc(tamanho*sizeof(int));

    for(int i = 0; i < tamanho; i++){
        vetor_bolha[i] = rand() % 99999;
        vetor_selection[i] = vetor_bolha[i];
        vetor_merge[i] = vetor_bolha[i];
        vetor_quick[i] = vetor_bolha[i];
        vetor_heap[i] = vetor_bolha[i]; 
    }

    clock_t tempoExec_bolha;

    tempoExec_bolha=clock();
    bolha(vetor_bolha,tamanho);
    tempoExec_bolha=clock()-tempoExec_bolha;
    printf("Tempo de execucao do metodo bolha: %0.4lf\n",((double)tempoExec_bolha/((CLOCKS_PER_SEC/1000))));
    
    clock_t tempoExec_selection;

    tempoExec_selection = clock();
    selection(vetor_selection,tamanho);    
    tempoExec_selection = clock() - tempoExec_selection;
    printf("Tempo de execucao do metodo selection: %0.4lf\n",((double)tempoExec_selection/((CLOCKS_PER_SEC/1000))));
    
    clock_t tempoExec_merge;
    tempoExec_merge=clock();
    mergeSort(vetor_merge,0,tamanho-1);
    tempoExec_merge=clock() - tempoExec_merge;
    printf("Tempo de execucao do metodo Merge: %0.4lf\n",((double)tempoExec_merge/((CLOCKS_PER_SEC/1000))));
    
    clock_t tempoExec_quick;
    tempoExec_quick=clock();
    quick_sort(vetor_quick,0,tamanho-1);
    tempoExec_quick=clock()-tempoExec_quick;
    printf("Tempo de execucao do metodo quick: %0.4lf\n",((double)tempoExec_quick/((CLOCKS_PER_SEC/1000))));

    clock_t tempoExec_heap;
    tempoExec_heap=clock();
    heapSort(vetor_heap,tamanho-1);
    tempoExec_heap=clock()-tempoExec_heap;
    printf("Tempo de execucao do metodo heap: %0.4lf\n",((double)tempoExec_heap/((CLOCKS_PER_SEC/1000))));
}