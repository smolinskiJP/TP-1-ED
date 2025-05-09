#include "universalsort.h"

void swap(int* a, int* b, Custo* c){

    increaseMoves(c);
    int temp = *a;

    increaseMoves(c);
    *a = *b;

    increaseMoves(c);
    *b = temp;
}


void quickSort3Ins(int * A, int l, int r, Custo* custo){
    if (l >= r) return;
    if(r - l <= 50) {
        insertionSort(A, l, r, custo);
        return;
    }
    increaseCalls(custo);
    //passo recursivo
    int i, j;
    partition3(A, l, r, &i, &j, custo);
    quickSort3Ins(A, l, j, custo);
    quickSort3Ins(A, i, r, custo);
}

void partition3(int * A, int l, int r, int *i, int *j, Custo* custo){
    increaseCalls(custo);
    
    (*i) = l;
    (*j) = r;
    int pivot = median(A[(*i)], A[(*j)], A[(*i + *j) / 2]);
    
    do{
        increaseCompare(custo);
        while(pivot > A[*i]){
            increaseCompare(custo);
            (*i)++;
        }
        
        increaseCompare(custo);
        while(pivot < A[*j]){
            increaseCompare(custo);
            (*j)--;
        } 

      if(*i <= *j){
        swap(&A[*i], &A[*j], custo);
        (*i)++;
        (*j)--;
      }

    }while(*i <= *j);
}

void insertionSort(int v[], int l, int r, Custo* custo){
    increaseCalls(custo);

    l++;
    int aux, j;
    for(; l <= r; l++){

        aux = v[l];
        increaseMoves(custo);

        j = l - 1;

        increaseCompare(custo);
        while((j >= 0) && aux < v[j]){
            increaseCompare(custo);

            v[j + 1] = v[j];
            increaseMoves(custo);

            j--;
        }

        v[j + 1] = aux;
        increaseMoves(custo);
    }
}

int median(int a, int b, int c){
    if(b <= a){
        if(c <= b) return b;
        if(c <= a) return c;
        return a;
    }
    if(c <= a) return a;
    if(c <= b) return c;
    return b;
}

/*void universalSort(int * A, int tam, int minSizePartition, int breakMax){
    int breakCount = countBreak(A, tam);
    if(breakCount < breakMax) insertionSort(A, 0, tam - 1);
    else if(tam > minSizePartition) quickSort3Ins(A, 0, tam - 1);
    else insertionSort(A, 0, tam - 1);
}*/

int countBreak(int * A, int tam){
    int count = 0;
    for(int i = 0; i < tam - 1; i++) if(A[i] > A[i + 1]) count++;
    return count;
}

void OrdenadorUniversalOptimizer(int * A, int tam, int minSizePartition, int breakMax, Custo* custo){
    //copiar array (para ter um array reserva depois que ordenar o "atual")
    int* B = (int*)malloc(tam * sizeof(int));
    for(int i = 0; i < tam; i++) B[i] = A[i];

    int breakCount = countBreak(B, tam);
    if(breakCount < breakMax) insertionSort(B, 0, tam - 1, custo);
    else if(tam > minSizePartition) quickSort3Ins(B, 0, tam - 1, custo);
    else insertionSort(B, 0, tam - 1, custo);

    //desalocar array ordenado
    free(B);
}