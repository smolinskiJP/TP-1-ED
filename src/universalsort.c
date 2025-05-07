#include "universalsort.h"

void quickSort3Ins(int * A, int l, int r){
    //passo base - change to insertion
    if(r - l <= 50) {
        insertionSort(A, l, r);
        return;
    }
    //passo recursivo
    int i, j;
    partition3(A, l, r, &i, &j);
    quickSort3Ins(A, l, j);
    quickSort3Ins(A, i, r);
}

void partition3(int * A, int l, int r, int *i, int *j){
    
    (*i) = l;
    (*j) = r;
    int pivot = median(A[(*i)], A[(*j)], A[(*i + *j) / 2]);
    
    do{
      while(pivot > A[*i]){
        (*i)++;
      }

      while(pivot < A[*j]){
        (*j)--;
      } 

      if(*i <= *j){
        swap(&A[*i], &A[*j]);
        (*i)++;
        (*j)--;
      }

    }while(*i <= *j);
}

void insertionSort(int v[], int l, int r){
    l++;
    int aux, j;
    for(; l <= r; l++){
        aux = v[l];
        j = l - 1;

        while((j >= 0) && aux < v[j]){
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = aux;
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

void universalSort(int * A, int tam, int minSizePartition, int breakMax){
    int breakCount = countBreak(A, tam);
    if(breakCount < breakMax) insertionSort(A, 0, tam - 1);
    else if(tam > minSizePartition) quickSort3Ins(A, 0, tam - 1);
    else insertionSort(A, 0, tam - 1);
}

int countBreak(int * A, int tam){
    int count = 0;
    for(int i = 0; i < tam - 1; i++) if(A[i] < A[i + 1]) count++;
    return count;
}