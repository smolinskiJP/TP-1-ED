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

int definePartitionSize(int * A, int tam, int limiarCusto){
    int minMPS = 2, maxMPS = tam;
    int stepMPS = (maxMPS - minMPS) / 5;
    int limParticao, diffCusto, numMPS;
    float * custo = (float*)malloc(tam * sizeof(float));
    
    do{
        numMPS = 0;
        for(int t = minMPS; t <= maxMPS; t += stepMPS){
            OrdenadorUniversal(A, tam, t, tam);
            registraEstatisticas(custo, numMPS);
            imprimeEstatisticas(custo, numMPS);
            numMPS++;
        }
        limParticao = menorCusto();
        calculaNovaFaixa(limParticao, minMPS, maxMPS, numMPS);
        diffCusto = fabs(custo[minMPS] - custo[maxMPS]);
    }while((diffCusto > limiarCusto) && (numMPS >= 5 ));

    /*while((diffCusto > limiarCusto) && (numMPS >= 5 )){
        numMPS=0;
        for (int t = minMPS; t <= maxMPS; t += stepMPS){
            OrdenadorUniversal(A, tam, t, tam);
            registraEstatisticas(custo[numMPS]);
            imprimeEstatisticas(custo[numMPS]);
            numMPS++;
        }
        limParticao = menorCusto();
        calculaNovaFaixa(limParticao, minMPS, maxMPS, stepMPS);
        diffCusto = fabs(custo[minMPS]−custo[maxMPS]);
    }*/
    return limParticao;
}

void calculaNovaFaixa(int limParticao, int minMPS, int maxMPS, int numMPS){
    int newMin, newMax;
    if(limParticao == 0){
        newMin = 0;
        newMax = 2;
    } else if(limParticao == numMPS - 1){
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    } else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }
    minMPS = getMPS(newMin);
    maxMPS = getMPS(newMax);
    //stepMPS = (int)(maxMPS - minMPS) / 5;
    //if(stepMPS == 0) stepMPS++;
}
