#include <stdio.h>
#include <stdlib.h>
#include "arrayparameters.h"
#include "optimizer.h"
#define SUCESSO 0

void getParametros(ArrayParameters* ap) {
    int limiarCusto;
    double a, b, c;
    scanf(" %d %lf %lf %lf", &limiarCusto, &a, &b, &c);
    ap = setArrayParameters(a, b, c, limiarCusto, ap);
    printf("LimiarCusto: %d\n", ap->limiarCusto);
    printf("a: %lf\n", ap->a);
    printf("b: %lf\n", ap->b);
    printf("c: %lf\n", ap->c);
}

void imprimeTUDO(int* A, int tam, ArrayParameters* ap) {
    printf("LimiarCusto: %d\n", ap->limiarCusto);
    printf("a: %lf\n", ap->a);
    printf("b: %lf\n", ap->b);
    printf("c: %lf\n", ap->c);
    printf("Tamanho: %d\n", tam);
    for (int i = 0; i < tam; i++) printf("%d ", A[i]);
    printf("\n");
    getchar();
}

int main(int argc, char** argv) {
    int n;
    int* Array = NULL;
    ArrayParameters* ap = newArrayParameters();
    getParametros(ap);

    scanf(" %d", &n);
    Array = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) scanf(" %d", &(Array[i]));

    imprimeTUDO(Array, n, ap);
    int partitionSize = definePartitionSize(Array, n, ap);

    deleteArrayParameters(ap);
    free(Array);
    return SUCESSO;
}