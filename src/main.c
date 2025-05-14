#include <stdio.h>
#include <stdlib.h>
#include "arrayparameters.h"
#include "optimizer.h"
#define SUCESSO 0

void imprimeTUDO(int* A, int tam, ArrayParameters* ap) {
    printf("LimiarCusto: %lf\n", ap->limiarCusto);
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

    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL){

        unsigned int seed;
        double limiarCusto;
        double a, b, c;
        scanf("%d %lf %lf %lf %lf", &seed, &limiarCusto, &a, &b, &c);
        ap = setArrayParameters(seed, a, b, c, limiarCusto, ap);  

        scanf(" %d", &n);
        Array = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) scanf(" %d", &(Array[i]));

    }else{

        unsigned int seed;
        double limiarCusto;
        double a, b, c;
        fscanf(inFile, " %d %lf %lf %lf %lf", &seed, &limiarCusto, &a, &b, &c);
        ap = setArrayParameters(seed, a, b, c, limiarCusto, ap);  

        fscanf(inFile, " %d", &n);
        Array = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) fscanf(inFile, " %d", &(Array[i]));

        fclose(inFile);
    }


    //imprimeTUDO(Array, n, ap);
    printf("size %d seed %d breaks %d\n", n, ap->seed, countBreak(Array, 0, n));

    int partitionSize = definePartitionSize(Array, n, ap);
    int breakMax = defineBreakLimit(Array, n, ap);

    //printf("\nO limite otimizado de quebra eh: %d", breakMax);
    //printf("\nO tamanho otimizado de particao eh: %d\n", partitionSize);
    
    deleteArrayParameters(ap);
    free(Array);
    return SUCESSO;
}