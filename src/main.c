#include <stdio.h>
#include <stdlib.h>
#include "arrayparameters.h"
#include "optimizer.h"
#define SUCESSO 0
#define IN_ERROR -10
#define MEMORY_ERROR -1

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
    if(!ap) {
        printf("Erro ao alocar memoria");
        return MEMORY_ERROR;
    }

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
        if(!Array) {
            printf("Erro ao alocar memoria");
            deleteArrayParameters(ap);
            return MEMORY_ERROR;
        }
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
        if(!Array) {
            printf("Erro ao alocar memoria");
            deleteArrayParameters(ap);
            return MEMORY_ERROR;
        }
        int i = 0;
        for(; i < n; i++) {
            if(feof(inFile)) break; //Se chegou ao fim do arquivo quebra a leitura
            fscanf(inFile, " %d", &(Array[i]));
        }

        //Encerra o programa caso nao tenha lido todos os valores esperados
        if (i != n) {
            printf("O arquivo nao esta de acordo com o esperado");
            deleteArrayParameters(ap);
            free(Array);
            return IN_ERROR;
        }

        fclose(inFile);
    }

    //imprimeTUDO(Array, n, ap);

    //Imprimimos a primeira linha padrão da saída, que conta com o tamanho do vetor, a seed usada e o número de quebras no vetor
    printf("size %d seed %d breaks %d\n", n, ap->seed, countBreak(Array, 0, n));

    //Calculamos o tamanho otimizado de partição
    int partitionSize = definePartitionSize(Array, n, ap);
    //"Catch" de erros na funcao
    if(partitionSize < 0) {
        deleteArrayParameters(ap);
        free(Array);
        return partitionSize;
    }

    //Calculamos o número otimizado de quebras
    int breakMax = defineBreakLimit(Array, n, ap, partitionSize);
    //"Catch" de erros na funcao
    if(breakMax < 0) {
        deleteArrayParameters(ap);
        free(Array);
        return breakMax;
    }

    //printf("\nO limite otimizado de quebra eh: %d", breakMax);
    //printf("\nO tamanho otimizado de particao eh: %d\n", partitionSize);
    
    //Liberamos toda memória alocada
    deleteArrayParameters(ap);
    free(Array);
    return SUCESSO;
}