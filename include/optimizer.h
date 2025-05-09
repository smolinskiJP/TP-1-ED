#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <stdlib.h>
#include "universalsort.h"



int definePartitionSize(int * A, int tam, int limiarCusto);
void calculaNovaFaixa(int limParticao, int* minMPS, int* maxMPS, int numMPS, int* stepMPS);

#endif