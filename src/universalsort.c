#include "universalsort.h"

void swap(int* a, int* b, Custo* c){

    increaseMoves(c);
    int temp = *a;

    increaseMoves(c);
    *a = *b;

    increaseMoves(c);
    *b = temp;
}

void quickSort3Ins(int * A, int l, int r, Custo* custo, int minSizePartition){
    if (l >= r) return;
    if(r - l < minSizePartition) {
        insertionSort(A, l, r, custo);
        return;
    }
    increaseCalls(custo);
    //passo recursivo
    int i, j;
    partition3(A, l, r, &i, &j, custo);
    quickSort3Ins(A, l, j, custo, minSizePartition);
    quickSort3Ins(A, i, r, custo, minSizePartition);
}

void partition3(int * A, int l, int r, int *i, int *j, Custo* custo){
    increaseCalls(custo);
    //printf("p: %d %d\n", l, r);
    
    (*i) = l;
    (*j) = r;
    int pivot = median(A[l], A[r], A[(l + r) / 2]);
    
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

      if((*i) <= (*j)){
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
    if(b <= a){ // _ b _ a _
        if(c <= b) return b; // c b a
        if(c <= a) return c; // b c a
        return a; // b a c
    } // _ a _ b _
    if(c <= a) return a; // c a b
    if(c <= b) return c; // a c b
    return b; // a b c
}

/*void universalSort(int * A, int tam, int minSizePartition, int breakMax){
    int breakCount = countBreak(A, tam);
    if(breakCount < breakMax) insertionSort(A, 0, tam - 1);
    else if(tam > minSizePartition) quickSort3Ins(A, 0, tam - 1);
    else insertionSort(A, 0, tam - 1);
}*/

int countBreak(int * A, int l, int tam){
    int count = 0;
    for(int i = l; i < tam - 1; i++) if(A[i] > A[i + 1]) count++;
    return count;
}

void OrdenadorUniversalPartitionOptimizer(int * A, int tam, int minSizePartition, Custo* custo){
    //copiar array (para ter um array reserva depois que ordenar o "atual")
    int* B = (int*)malloc(tam * sizeof(int));
    arrayCopy(A, B, tam);

    //como queremos testar a otimização de partition, ignoraremos a condição de break

    if(tam > minSizePartition) quickSort3Ins(B, 0, tam - 1, custo, minSizePartition);
    else insertionSort(B, 0, tam - 1, custo);

    //printf("break: %d", countBreak(B, 0, tam));

    //desalocar array ordenado
    free(B);
}

void OrdenadorUniversalBreakOptimizer(int* A, int tam, int breakMax, Custo* custoQuick, Custo* custoInsertion){
    int* B = (int*)malloc(tam * sizeof(int));
    int* C = (int*)malloc(tam * sizeof(int));

    arrayCopy(A, B, tam);

    quickSort3Ins(B, 0, tam - 1, custoQuick, 0);
    resetCusto(custoQuick);

    arrayShuffler(B, tam, breakMax);
    arrayCopy(B, C, tam);

    //imprime(B, tam);

    insertionSort(B, 0, tam - 1, custoInsertion);
    quickSort3Ins(C, 0, tam - 1, custoQuick, 0);
    //quickSortOptimizer(B, tam, 0, tam - 1, breakMax, custoQuick, custoInsertion);

    free(C);
    free(B);
}

void imprime(int* A, int tam){
    for(int i = 0; i < tam/10; i++) printf("%d ", A[i]);
    printf("\n");
}

void arrayShuffler(int* A, int tam, int totalBreaks){
    for(int i = 0; i < totalBreaks; i++){
        int i1 = 0, i2 = 0;
        while(i1 == i2){
            i1 = (rand() % tam);
            i2 = (rand() % tam);
            //i1 = (int)(drand48() * (tam - 1));
            //i2 = (int)(drand48() * (tam - 1));
        }

        int temp = A[i1];
        A[i1] = A[i2];
        A[i2] = temp;
    }
}

void arrayCopy(int* A, int* B, int tam){
    for(int i = 0; i < tam; i++) B[i] = A[i];
}