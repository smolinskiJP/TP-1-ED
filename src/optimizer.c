#include "optimizer.h"

int definePartitionSize(int * A, int tam, ArrayParameters* ap){
    int minMPS = 2, maxMPS = tam;
    int stepMPS = (maxMPS - minMPS) / 5;
    int limParticao, numMPS;
    float diffCusto;
    float * custos = (float*)malloc(tam * sizeof(float));
    Custo* custo = newCusto();
    int iter = 0;
    
    do{
        printf("iter %d\n", iter);
        numMPS = 0;
        for(int t = minMPS; t <= maxMPS; t += stepMPS){
            OrdenadorUniversalOptimizer(A, tam, t, tam, custo);
            registraEstatisticas(custos, numMPS, custo, ap);
            printf("mps %d cost %f cmp %d move %d calls %d\n", t, custos[numMPS], custo->compare, custo->moves, custo->calls);
            numMPS++;
            resetCusto(custo);
        }

        limParticao = menorCusto(custos, numMPS);
        calculaNovaFaixa(limParticao, &minMPS, &maxMPS, numMPS, &stepMPS);
        diffCusto = fabs(custos[minMPS] - custos[maxMPS]);

        printf("nummps %d limParticao %d mpsdiff %f", numMPS, limParticao, diffCusto);

        iter++;
    }while((diffCusto > ap->limiarCusto) && (numMPS >= 5));

    free(custos);
    deleteCusto(custo);
    return limParticao;
}

void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS){
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
    (*minMPS) = getMPS(newMin, minMPS, stepMPS);
    (*maxMPS) = getMPS(newMax, minMPS, stepMPS);
    (*stepMPS) = (int)(maxMPS - minMPS) / 5;
    if((*stepMPS) == 0) (*stepMPS)++;
}

int getMPS(int index, int start, int step){
    return start + index * step;
}

void registraEstatisticas(float* A, int index, Custo* custo, ArrayParameters* ap){
    float value = (custo->compare * ap->a) + (custo->moves * ap->b) + (custo->calls * ap->c);
    A[index] = value;
}

int menorCusto(float* A, int size){
    int min = 0;
    for(int i = 1; i < size; i++) if(A[min] > A[i]) min = i;
    return min;
}