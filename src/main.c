#include <stdio.h>
#include <stdlib.h>
#include "arrayparameters.h"
#include "optimizer.h"
#define SUCESSO 0

void imprimeTUDO(int* A, int tam, ArrayParameters* ap) {
    printf("LimiarCusto: %d\n", ap->limiarCusto);
    printf("a: %lf\n", ap->a);
    printf("b: %lf\n", ap->b);
    printf("c: %lf\n", ap->c);
    printf("Tamanho: %d\n", tam);
    for (int i = 0; i < tam; i++) printf("%d ", A[i]);
    printf("\n\n");
}

int main(int argc, char** argv) {
    int n;
    int* Array = NULL;
    ArrayParameters* ap = newArrayParameters();

    FILE* inFile = fopen("in.txt", "r");
    if(inFile == NULL){

        int limiarCusto;
        double a, b, c;
        scanf(" %d %lf %lf %lf", &limiarCusto, &a, &b, &c);
        ap = setArrayParameters(a, b, c, limiarCusto, ap);  

        scanf(" %d", &n);
        Array = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) scanf(" %d", &(Array[i]));

    }else{

        int limiarCusto;
        double a, b, c;
        fscanf(inFile, " %d %lf %lf %lf", &limiarCusto, &a, &b, &c);
        ap = setArrayParameters(a, b, c, limiarCusto, ap);  

        fscanf(inFile, " %d", &n);
        Array = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) fscanf(inFile, " %d", &(Array[i]));

    }

    fclose(inFile);

    imprimeTUDO(Array, n, ap);

    int partitionSize = definePartitionSize(Array, n, ap);
    int breakMax = defineBreakLimit(Array, n, ap);

    printf("\nO limite otimizado de quebra eh: %d", breakMax);
    printf("\nO tamanho otimizado de particao eh: %d\n", partitionSize);
    
    deleteArrayParameters(ap);
    free(Array);
    return SUCESSO;
}