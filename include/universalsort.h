#ifndef UNIVERSAL_SORT_H
#define UNIVERSAL_SORT_H

#include <stdlib.h>
#include <stdio.h>
#include "custo.h"

void swap(int* a, int* b, Custo* c);
void quickSort3Ins(int * A, int l, int r, Custo* custo, int minSizePartition);
void partition3(int * A, int l, int r, int *i, int *j, Custo* custo);
void insertionSort(int v[], int l, int r, Custo* custo);
int median(int a, int b, int c);
//void universalSort(int * A, int tam, int minSizePartition, int breakMax);
int countBreak(int * A, int l, int tam);
void OrdenadorUniversalPartitionOptimizer(int * A, int tam, int minSizePartition, Custo* custo);
void OrdenadorUniversalBreakOptimizer(int* A, int tam, int breakMax, Custo* custoQuick, Custo* custoInsertion);
int quickSortOptimizer(int* A, int tamanho, int left, int right, int breakMax, Custo* custoQuick, Custo* custoInsertion);
void imprime(int* A, int tam);
void arrayShuffler(int* A, int tam, int totalBreaks);
void arrayCopy(int* A, int* B, int tam);

#endif