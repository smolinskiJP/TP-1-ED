#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <stdlib.h>
#include "universalsort.h"
#include "arrayparameters.h"
#include "custo.h"

int definePartitionSize(int * A, int tam, ArrayParameters* ap);
void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS);

#endif