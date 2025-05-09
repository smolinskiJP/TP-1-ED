#include "optimizer.h"



int definePartitionSize(int * A, int tam, int limiarCusto){
    int minMPS = 2, maxMPS = tam;
    int stepMPS = (maxMPS - minMPS) / 5;
    int limParticao, numMPS;
    float diffCusto;
    float * custos = (float*)malloc(tam * sizeof(float));
    
    do{
        numMPS = 0;
        for(int t = minMPS; t <= maxMPS; t += stepMPS){
            OrdenadorUniversalOptmizer(A, tam, t, tam);
            registraEstatisticas(custos, numMPS);
            imprimeEstatisticas(custos, numMPS);
            numMPS++;
        }
        limParticao = menorCusto();
        calculaNovaFaixa(limParticao, &minMPS, &maxMPS, numMPS, &stepMPS);
        diffCusto = fabs(custos[minMPS] - custos[maxMPS]);
    }while((diffCusto > limiarCusto) && (numMPS >= 5));

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
    (*minMPS) = getMPS(newMin);
    (*maxMPS) = getMPS(newMax);
    (*stepMPS) = (int)(maxMPS - minMPS) / 5;
    if((*stepMPS) == 0) (*stepMPS)++;
}
