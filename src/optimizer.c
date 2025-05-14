#include "optimizer.h"

int defineBreakLimit(int* A, int tam, ArrayParameters* ap, int MPS){
    int minLQ = 1, maxLQ = countBreak(A, 0, tam);
    int stepLQ = (maxLQ - minLQ) / 5;
    int limBreak, numLQ;
    double diffCusto;
    double* custosQ = (double*)malloc(tam * sizeof(double));
    double* custosI = (double*)malloc(tam * sizeof(double));
    Custo* custoQuick = newCusto();
    Custo* custoInsertion = newCusto();
    int iter = 0;

    do{
        printf("\niter %d\n", iter);
        numLQ = 0;
        for(int t = minLQ; t <= maxLQ; t += stepLQ){
            //for(int i  = 0; i < tam; i++) printf("%d ", A[i]);
            //printf("\n");
            //OrdenadorUniversalOptimizer(A, tam, 2, t, custo);
            //registraEstatisticas(custos, numLQ, custo, ap);
            //printf("");
            //numLQ++;
            srand(ap->seed);
            //srand48(ap->seed);

            OrdenadorUniversalBreakOptimizer(A, tam, t, custoQuick, custoInsertion, MPS);

            //quickSort
            registraEstatisticas(custosQ, numLQ, custoQuick, ap);
            printf("qs lq %d cost %.9lf cmp %d move %d calls %d\n", t, custosQ[numLQ], custoQuick->compare, custoQuick->moves, custoQuick->calls);
            resetCusto(custoQuick);

            //insertionSort
            registraEstatisticas(custosI, numLQ, custoInsertion, ap);
            printf("in lq %d cost %.9lf cmp %d move %d calls %d\n", t, custosI[numLQ], custoInsertion->compare, custoInsertion->moves, custoInsertion->calls);
            resetCusto(custoInsertion);

            //OrdenadorUniversalBreakOptimizer(A, tam, t, custoQuick, custoInsertion);
            numLQ++;
        }

        int minIndex = menorCustoDiff(custosI, custosQ, numLQ);
        limBreak = getBreak(minIndex, minLQ, stepLQ);

        int maxLim = minIndex + 1;
        if(minIndex == 0) maxLim = minIndex + 2;
        else if(minIndex == numLQ - 1) maxLim = minIndex;

        calculaNovaFaixa(minIndex, &minLQ, &maxLQ, numLQ, &stepLQ);
        custosI[maxLim - 2] = 1.939425700;
        custosI[maxLim] = 2.243742700;
        diffCusto = absolute(custosI[maxLim - 2] - custosI[maxLim]);

        //printf("%.9lf %.9lf\n", custosI[maxLim - 2], custosI[maxLim]);
        //printf("%lf\n", diffCusto);
        printf("numlq %d limQuebras %d lqdiff %.6lf\n", numLQ, limBreak, truncate(diffCusto));

        iter++;
    }while((diffCusto > ap->limiarCusto) && (numLQ >= 5));

    free(custosQ);
    free(custosI);
    deleteCusto(custoQuick);
    deleteCusto(custoInsertion);
    return limBreak;
}

int definePartitionSize(int* A, int tam, ArrayParameters* ap) {
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
            OrdenadorUniversalPartitionOptimizer(A, tam, t, custo);
            registraEstatisticas(custos, numMPS, custo, ap);
            printf("mps %d cost %.9lf cmp %d move %d calls %d\n", t, custos[numMPS], custo->compare, custo->moves, custo->calls);
            numMPS++;
            resetCusto(custo);
        }

        int minIndex = menorCusto(custos, numMPS);
        limParticao = getMPS(minIndex, minMPS, stepMPS);

        int maxLim = minIndex + 1;
        if(minIndex == 0) maxLim = minIndex + 2;
        else if(minIndex == numMPS - 1) maxLim = minIndex;

        calculaNovaFaixa(minIndex, &minMPS, &maxMPS, numMPS, &stepMPS);
        diffCusto = absolute(custos[maxLim - 2] - custos[maxLim]);
        
        printf("nummps %d limParticao %d mpsdiff %.6lf\n", numMPS, limParticao, truncate(diffCusto));

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

int getBreak(int index, int start, int step){
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

int menorCustoDiff(double* A, double* B, int size){
    int min = 0;
    for (int i = 1; i < size; i ++) if (absolute(A[min] - B[min]) > absolute(A[i] - B[i])) min = i;
    return min;
}

double absolute(double d){
    if(d < 0) return -1.0 * d;
    return d;
}

double truncate(double value){
    double factor = 1e6;
    long int truncated = (long int)(value * factor);
    printf("value %.9lf multiplier %lf truncated %ld\n", value, factor, truncated);
    return (truncated / factor);
}