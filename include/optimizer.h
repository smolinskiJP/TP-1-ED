#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <stdlib.h>
#include <stdio.h>
#include "universalsort.h"
#include "arrayparameters.h"
#include "custo.h"

int defineBreakLimit(int* A, int tam, ArrayParameters* ap, int MPS);
int definePartitionSize(int * A, int tam, ArrayParameters* ap);
void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS);
int getValueByStep(int index, int start, int step);
int menorCusto(double* A, int size);
int menorCustoDiff(double* A, double* B, int size);
float absolute(double d);

#endif