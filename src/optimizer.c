#include "optimizer.h"

int definePartitionSize(int* A, int tam, ArrayParameters* ap) {

    printf("size %d seed ? breaks %d\n", tam, countBreak(A, tam));

    int minMPS = 2, maxMPS = tam;
    int stepMPS = (maxMPS - minMPS) / 5;
    int limParticao, numMPS;
    double diffCusto;
    double* custos = (double*)malloc(tam * sizeof(double));
    Custo* custo = newCusto();
    int iter = 0;

    do {
        printf("\niter %d\n", iter);
        numMPS = 0;
        for (int t = minMPS; t <= maxMPS; t += stepMPS) {
            //for(int i  = 0; i < tam; i++) printf("%d ", A[i]);
            //printf("\n");
            OrdenadorUniversalOptimizer(A, tam, t, 0, custo);
            registraEstatisticas(custos, numMPS, custo, ap);
            printf("mps %d cost %lf cmp %d move %d calls %d\n", t, custos[numMPS], custo->compare, custo->moves, custo->calls);
            numMPS++;
            resetCusto(custo);
        }

        int minIndex = menorCusto(custos, numMPS);
        limParticao = getMPS(minIndex, minMPS, stepMPS);

        int maxLim = minIndex + 1;
        if(minIndex == 0) maxLim = minIndex + 2;
        else if(minIndex == numMPS - 1) maxLim = minIndex;

        calculaNovaFaixa(minIndex, &minMPS, &maxMPS, numMPS, &stepMPS);
        diffCusto = fabs(custos[maxLim - 2] - custos[maxLim]);

        printf("customin %lf min %d customax %lf max %d nummps %d limParticao %d mpsdiff %lf\n", custos[maxLim - 2], minMPS, custos[maxLim], maxMPS, numMPS, limParticao, diffCusto);

        iter++;
    } while ((diffCusto > ap->limiarCusto) && (numMPS >= 5));

    free(custos);
    deleteCusto(custo);
    return limParticao;
}

void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS) {
    int newMin, newMax;
    if (limParticao == 0) {
        newMin = 0;
        newMax = 2;
    }
    else if (limParticao == numMPS - 1) {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    }
    else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }
    (*maxMPS) = getMPS(newMax, *minMPS, *stepMPS);
    (*minMPS) = getMPS(newMin, *minMPS, *stepMPS);
    (*stepMPS) = (int)(*maxMPS - *minMPS) / 5;
    if ((*stepMPS) == 0) (*stepMPS)++;
}

int getMPS(int index, int start, int step) {
    return start + index * step;
}

void registraEstatisticas(double* A, int index, Custo* custo, ArrayParameters* ap) {
    double value = (custo->compare * ap->a) + (custo->moves * ap->b) + (custo->calls * ap->c);
    A[index] = value;
}

int menorCusto(double* A, int size) {
    int min = 0;
    for (int i = 1; i < size; i++) if (A[min] > A[i]) min = i;
    return min;
}