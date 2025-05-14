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
int getMPS(int index, int start, int step);
int getBreak(int index, int start, int step);
void registraEstatisticas(double* A, int index, Custo* custo, ArrayParameters* ap);
int menorCusto(double* A, int size);
int menorCustoDiff(double* A, double* B, int size);
double absolute(double d);
double truncate(double value);

#endif