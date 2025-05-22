#include <stdio.h>
#include <stdlib.h>
#include "arrayparameters.h"
#include "optimizer.h"
#define SUCESSO 0

//Função criada durante a implementação do trabalho para verificar as entradas obtidas no arquivo. Não é usada na versão final
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

    //Por default, tenta abrir o arquivo passado como segundo parâmetro na execução do programa
    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL){
        //Caso falhe em abrir o arquivo, pegaremos as entradas da entrada padrão, o terminal.
        unsigned int seed;
        double limiarCusto;
        double a, b, c;
        scanf("%d %lf %lf %lf %lf", &seed, &limiarCusto, &a, &b, &c);
        ap = setArrayParameters(seed, a, b, c, limiarCusto, ap);  

        scanf(" %d", &n);
        Array = (int*)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++) scanf(" %d", &(Array[i]));

    }else{
        //Caso abra o arquivo, lemos as entradas a partir dele
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

    //Imprimimos a primeira linha padrão da saída, que conta com o tamanho do vetor, a seed usada e o número de quebras no vetor
    printf("size %d seed %d breaks %d\n", n, ap->seed, countBreak(Array, 0, n));

    //Calculamos o tamanho otimizado de partição
    int partitionSize = definePartitionSize(Array, n, ap);

    //Calculamos o número otimizado de quebras
    int breakMax = defineBreakLimit(Array, n, ap, partitionSize);

    //printf("\nO limite otimizado de quebra eh: %d", breakMax);
    //printf("\nO tamanho otimizado de particao eh: %d\n", partitionSize);
    

    //Liberamos toda memória alocada
    deleteArrayParameters(ap);
    free(Array);
    return SUCESSO;
}