#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "universalsort.h"
#include "arrayparameters.h"
#include "custo.h"

int definePartitionSize(int * A, int tam, ArrayParameters* ap);
void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS);
int getMPS(int index, int start, int step);
void registraEstatisticas(double* A, int index, Custo* custo, ArrayParameters* ap);
int menorCusto(double* A, int size);

#endif